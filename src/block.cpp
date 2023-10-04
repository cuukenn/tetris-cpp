#include <iostream>
#include <random>
#include "block.h"
Block::Block()
{
    int blocks[BLOCK_TYPE_SIZE][BLOCK_CELL_SIZE] = {
        1, 3, 5, 7, // I
        2, 4, 5, 7, // z 1
        3, 5, 4, 6, // z 2
        3, 5, 4, 7, // T
        2, 3, 5, 7, // L
        3, 5, 7, 6, // J
        2, 3, 4, 5  // 田
    };
    blockType = 1 + rand() % BLOCK_TYPE_SIZE;
    for (int i = 0; i < BLOCK_CELL_SIZE; i++)
    {
        int value = blocks[blockType - 1][i];
        this->smallBlock[i].row = value / 2;
        this->smallBlock[i].col = value % 2;
    }
}

Block::~Block()
{
}
void Block::drop()
{
    for (int i = 0; i < BLOCK_CELL_SIZE; i++)
    {
        this->smallBlock[i].row++;
    }
}
bool Block::blockInMap(std::vector<std::vector<int>> &map)
{
    int maxRows = map.size();
    int maxCols = map[0].size();
    for (int i = 0; i < BLOCK_CELL_SIZE; i++)
    {
        if (this->smallBlock[i].col < 0 || this->smallBlock[i].col >= maxCols ||
            this->smallBlock[i].row < 0 || this->smallBlock[i].row >= maxRows ||
            map[this->smallBlock[i].row][this->smallBlock[i].col] != 0)
        {
            return false;
        }
    }
    return true;
}
void Block::solidify(std::vector<std::vector<int>> &map)
{
    for (int i = 0; i < BLOCK_CELL_SIZE; i++)
    {
        map[this->smallBlock[i].row][this->smallBlock[i].col] = blockType;
    }
}
void Block::moveleftRigt(int offset)
{
    for (int i = 0; i < BLOCK_CELL_SIZE; i++)
    {
        smallBlock[i].col += offset;
    }
}
void Block::rotate()
{
    Point p = smallBlock[1];
    for (int i = 0; i < BLOCK_CELL_SIZE; i++)
    {
        Point temp = smallBlock[i];
        smallBlock[i].col = p.col - temp.row + p.row;
        smallBlock[i].row = p.row + temp.col - p.col;
    }
}

int Block::getBlockType()
{
    return blockType;
}
Block &Block::operator=(const Block &other)
{
    if (this == &other)
    {
        return *this;
    }

    this->blockType = other.blockType;

    for (int i = 0; i < BLOCK_CELL_SIZE; i++)
    {
        this->smallBlock[i] = other.smallBlock[i];
    }
    return *this;
}