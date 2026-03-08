#include "HashTable.h"
#include <string>

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
}

void doubleHash::insert(int value) {
    if (value == -1 || value == -2) return;
    if (isFull()) return;

    int probe = hash1(value), offset = hash2(value);
    while (hashTable[probe] != -1) {
        if (hashTable[probe] == -2) break;
        probe = (probe + offset) % TABLE_SIZE;
    }
    hashTable[probe] = value;
    keysPresent++;
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

bool doubleHash::search(int value) {
    int probe = hash1(value), offset = hash2(value), initialPos = probe;
    bool firstItr = true;
    while (1) {
        if (hashTable[probe] == -1) 
            return false;
        if (hashTable[probe] == value) 
            return true;
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
    int startY = 80;

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

        DrawRectangle(x, y, boxWidth, boxHeight, bgColor);
        DrawRectangleLines(x, y, boxWidth, boxHeight, BLACK);
        DrawText(to_string(i).c_str(), x + 5, y + 5, 10, DARKGRAY);
        int textWidth = MeasureText(displayText.c_str(), 20);
        DrawText(displayText.c_str(), x + (boxWidth - textWidth) / 2, y + (boxHeight - 20) / 2, 20, BLACK);
    }
}