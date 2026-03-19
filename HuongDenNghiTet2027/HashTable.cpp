#include "HashTable.h"
#include <string>

// BUTTON

Button::Button(float x, float y, float width, float height, string text, Color color) {
    this->rect = { x, y, width, height };
    this->text = text;
    this->color = color;
}

void Button::draw() {
    DrawRectangleRec(rect, color);
    DrawRectangleLinesEx(rect, 2, BLACK);

    int textWidth = MeasureText(text.c_str(), 25);
    DrawText(text.c_str(), rect.x + (rect.width - textWidth) / 2, rect.y + (rect.height - 20) / 2, 25, BLACK);
}

bool Button::isPressed(Vector2 mousePos, bool mousePressed) {
    if (CheckCollisionPointRec(mousePos, rect) && mousePressed)
        return true;
    return false;
}

// INPUT TEXT BOX

InputBox::InputBox(float x, float y, float width, float height) {
    rect = { x, y, width, height };
    text[0] = '\0';
    letterCount = 0;
    framesCounter = 0;
    boxPressed = false;
}

void InputBox::Update() {
    if (boxPressed) {
        SetMouseCursor(MOUSE_CURSOR_IBEAM);
        int key = GetCharPressed();

        while (key > 0) {
            if ((key >= 48) && (key <= 57) && (letterCount < 3)) {
                text[letterCount] = (char)key;
                text[letterCount + 1] = '\0';
                letterCount++;
            }
            key = GetCharPressed();
        }

        if (IsKeyPressed(KEY_BACKSPACE)) {
            letterCount--;
            if (letterCount < 0) letterCount = 0;
            text[letterCount] = '\0';
        }
    }
    else {
        SetMouseCursor(MOUSE_CURSOR_DEFAULT);
    }

    if (boxPressed) framesCounter++;
    else framesCounter = 0;
}

void InputBox::Draw() {
    DrawRectangleRec(rect, LIGHTGRAY);
    if (boxPressed) DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, RED);
    else DrawRectangleLines((int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height, DARKGRAY);

    DrawText(text, (int)rect.x + 5, (int)rect.y + 10, 21, MAROON);

    if (boxPressed && letterCount < 5) {
        if (((framesCounter / 20) % 2) == 0) {
            DrawText("_", (int)rect.x + 8 + MeasureText(text, 20), (int)rect.y + 12, 20, MAROON);
        }
    }
}

int InputBox::GetValue() {
    if (letterCount > 0) return std::stoi(text);
    return -1;
}

void InputBox::Clear() {
    text[0] = '\0';
    letterCount = 0;
}

void InputBox::checkPressed(Vector2 mousePos, bool mousePressed) {
    if (mousePressed) {
        if (CheckCollisionPointRec(mousePos, rect))
            boxPressed = true;
        else boxPressed = false; 
    }
}

// HASH TABLE

void doubleHash::__setSieve() {
    isPrime[0] = isPrime[1] = 1;
    for (long long i = 2; i * i < MAX_SIZE; i++)
        if (isPrime[i] == 0)
            for (long long j = i * i; j < MAX_SIZE; j += i)
                isPrime[j] = 1;
}

int doubleHash::hash1(int value) {
    return value % TABLE_SIZE;
}

int doubleHash::hash2(int value) {
    return PRIME - (value % PRIME);
}

bool doubleHash::isFull() {
    return (TABLE_SIZE == keysPresent);
}

doubleHash::doubleHash(int n) {
    __setSieve();
    TABLE_SIZE = n;
    PRIME = TABLE_SIZE - 1;
    while (isPrime[PRIME] == 1) PRIME--;
    keysPresent = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable.push_back(-1);
    }

    isAnimating = false;
    currentProbeIndex = 0;
    animatingValue = -1;
    animationTimer = 0.0f;
    animationDelay = 0.7f;
}

void doubleHash::insert(int value, bool animate) {
    if (value == -1 || value == -2) return;
    if (isFull() || isAnimating) return;

    int probe = hash1(value), offset = hash2(value);

    if (!animate) {
        while (hashTable[probe] != -1) {
            if (hashTable[probe] == -2) break;
            probe = (probe + offset) % TABLE_SIZE;
        }
        hashTable[probe] = value;
        keysPresent++;
        return;
    }

    probePath.clear();
    int initialPos = probe;
    bool firstItr = true;

    while (hashTable[probe] != -1) {
        probePath.push_back(probe);
        if (hashTable[probe] == -2) break;

        if (probe == initialPos && !firstItr) break; 
        probe = (probe + offset) % TABLE_SIZE;
        firstItr = false;
    }
    if (probePath.empty() || probePath.back() != probe)
        probePath.push_back(probe);
    isAnimating = true;
    currentProbeIndex = 0;
    animatingValue = value;
    animationTimer = 0.0f;
}

void doubleHash::updateAnimation(float dt) {
    if (!isAnimating) return;

    animationTimer += dt;
    if (animationTimer >= animationDelay) {
        animationTimer = 0.0f;
        currentProbeIndex++;

        if (currentProbeIndex >= probePath.size()) {
            int finalProbe = probePath.back();
            hashTable[finalProbe] = animatingValue;
            keysPresent++;
            isAnimating = false;
        }
    }
}

void doubleHash::erase(int value) {
    int probe = hash1(value), offset = hash2(value), initialPos = probe;
    bool firstItr = true;

    while (hashTable[probe] != -1) {
        if (hashTable[probe] == value) {
            hashTable[probe] = -2;
            keysPresent--;
            return;
        }
        if (probe == initialPos && !firstItr) break;
        probe = (probe + offset) % TABLE_SIZE;
        firstItr = false;
    }
}

int doubleHash::search(int value) {
    int probe = hash1(value), offset = hash2(value), initialPos = probe;
    bool firstItr = true;
    while (1) {
        if (hashTable[probe] == -1) 
            return -1;
        if (hashTable[probe] == value) 
            return probe;
        if (probe == initialPos && !firstItr) 
            return false;
        probe = ((probe + offset) % TABLE_SIZE);
        firstItr = false;
    }
}

void doubleHash::draw(int screenWidth, int screenHeight) {
    int boxWidth = 60;
    int boxHeight = 60;
    int padding = 10;

    int cols = screenWidth / (boxWidth + padding);
    if (cols == 0) cols = 1;

    int startX = (screenWidth - (cols * (boxWidth + padding) - padding)) / 2;
    int startY = 150;

    for (int i = 0; i < TABLE_SIZE; i++) {
        int row = i / cols;
        int col = i % cols;
        int x = startX + col * (boxWidth + padding);
        int y = startY + row * (boxHeight + padding);

        Color bgColor = LIGHTGRAY;
        string displayText = "";

        if (hashTable[i] == -1) {
            bgColor = RAYWHITE;
            displayText = "E";
        }
        else if (hashTable[i] == -2) {
            bgColor = RED;
            displayText = "D";
        }
        else {
            bgColor = GREEN;
            displayText = to_string(hashTable[i]);
        }

        if (isAnimating && currentProbeIndex < probePath.size() && i == probePath[currentProbeIndex]) {
            bgColor = YELLOW;
        }

        DrawRectangle(x, y, boxWidth, boxHeight, bgColor);
        DrawRectangleLines(x, y, boxWidth, boxHeight, BLACK);
        DrawText(to_string(i).c_str(), x + 5, y + 5, 12, DARKGRAY);
        int textWidth = MeasureText(displayText.c_str(), 20);
        DrawText(displayText.c_str(), x + (boxWidth - textWidth) / 2, y + (boxHeight - 20) / 2, 20, BLACK);
    }

    if (isAnimating) {
        DrawText(TextFormat("Inserting %d...", animatingValue), startX, startY - 40, 20, BLUE);
    }
}