#pragma once
#include <vector>
#define BLOCK_TYPE_SIZE 7
#define BLOCK_CELL_SIZE 4
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
    bool blockInMap(std::vector<std::vector<int>> &map);
    void solidify(std::vector<std::vector<int>> &map);
    void moveleftRigt(int offset);
    void rotate();
    int getBlockType();
    Block &operator=(const Block &other);
    Point smallBlock[BLOCK_CELL_SIZE];
};
