#include "block.h"
#include <random>
#include <iostream>
Block::Block()
{
    int blocks[TYPE_SIZE][TYPE_SIZE_S] = {
        1, 3, 5, 7, // I
        2, 4, 5, 7, // z 1
        3, 5, 4, 6, // z 2
        3, 5, 4, 7, // T
        2, 3, 5, 7, // L
        3, 5, 7, 6, // J
        2, 3, 4, 5  // 田
    };
    blockType = 1 + rand() % TYPE_SIZE;
    for (int i = 0; i < TYPE_SIZE_S; i++)
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
    for (int i = 0; i < TYPE_SIZE_S; i++)
    {
        this->smallBlock[i].row++;
    }
}
void Block::draw(int leftMargin, int topMargin)
{
    for (int i = 0; i < TYPE_SIZE_S; i++)
    {
        _SetConsoleCursor(this->smallBlock[i].col + leftMargin, this->smallBlock[i].row + topMargin);
        std::cout << "*";
    }
}
void Block::undraw(int leftMargin, int topMargin)
{
    for (int i = 0; i < TYPE_SIZE_S; i++)
    {
        _SetConsoleCursor(this->smallBlock[i].col + leftMargin, this->smallBlock[i].row + topMargin);
        std::cout << " ";
    }
}
bool Block::blockInMap(std::vector<std::vector<int>> &map)
{
    int maxRows = map.size();
    int maxCols = map[0].size();
    for (int i = 0; i < TYPE_SIZE_S; i++)
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
    for (int i = 0; i < TYPE_SIZE_S; i++)
    {
        map[this->smallBlock[i].row][this->smallBlock[i].col] = blockType;
    }
}
void Block::moveleftRigt(int offset)
{
    for (int i = 0; i < TYPE_SIZE_S; i++)
    {
        smallBlock[i].col += offset;
    }
}
void Block::rotate()
{
    Point p = smallBlock[1];
    for (int i = 0; i < TYPE_SIZE_S; i++)
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

    for (int i = 0; i < TYPE_SIZE_S; i++)
    {
        this->smallBlock[i] = other.smallBlock[i];
    }
    return *this;
}