#pragma once
#include <vector>
#include "segment.h"
#define TYPE_SIZE 7
#define TYPE_SIZE_S 4
struct Point
{
    int row;
    int col;
};

class Block
{
private:
    int blockType;

public:
    Block(/* args */);
    ~Block();
    void drop();
    void draw(int leftMargin, int topMargin);
    void undraw(int leftMargin, int topMargin);
    bool blockInMap(std::vector<std::vector<int>> &map);
    void solidify(std::vector<std::vector<int>> &map);
    void moveleftRigt(int offset);
    void rotate();
    int getBlockType();
    Block &operator=(const Block &other);
    Point smallBlock[TYPE_SIZE_S];
};
