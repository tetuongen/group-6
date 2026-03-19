#pragma once
#include "raylib.h"
#include <vector>
#include <bitset>
#include <string>

#define MAX_SIZE 100001ll

using namespace std;

class Button {
public:
    Button(float x, float y, float width, float height, string text, Color color);
    void draw();
    bool isPressed(Vector2 mousePos, bool mousePressed);
private:
    Rectangle rect;
    string text;
    Color color;
};

class InputBox {
private:
    Rectangle rect;
    int letterCount;
    int framesCounter;

public:
    char text[4];
    bool boxPressed;

    InputBox(float x, float y, float width, float height);
    void Update();
    void Draw();
    int GetValue();
    void Clear();
    void checkPressed(Vector2 mousePos, bool mousePressed);
};

class doubleHash {
public:
    int TABLE_SIZE;
    int keysPresent;
    int PRIME;

    vector<int> hashTable;
    bitset<MAX_SIZE> isPrime;

    bool isAnimating;
    vector<int> probePath;
    int currentProbeIndex;
    int animatingValue;
    float animationTimer;
    float animationDelay;

    doubleHash(int n);

    void __setSieve();
    int inline hash1(int value);
    int inline hash2(int value);
    bool inline isFull();

    void insert(int value, bool animate = true);
    void erase(int value);
    int search(int value);

    void updateAnimation(float dt);
    void draw(int screenWidth, int screenHeight);
};