#pragma once
#include "raylib.h"
#include <vector>
#include <bitset>

#define MAX_SIZE 100001ll

using namespace std;

class doubleHash {
public:
    int TABLE_SIZE;
    int keysPresent;
    int PRIME;

    vector<int> hashTable;
    bitset<MAX_SIZE> isPrime;

    doubleHash(int n);

    void __setSieve();
    int inline hash1(int value);
    int inline hash2(int value);
    bool inline isFull();

    void insert(int value);
    void erase(int value);
    bool search(int value);

    void draw(int screenWidth, int screenHeight);
};