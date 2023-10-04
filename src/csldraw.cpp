#include <iostream>
#include "segment.h"
#include "draw.h"
#define CELL_FILL "■"
#define CELL_EMPTY " "
#define CELL_WIDTH 1
ConsoleDraw::ConsoleDraw(int rows, int cols, int leftMargin, int topMargin)
{
    this->leftMargin = leftMargin;
    this->topMargin = topMargin;
    this->rows = rows;
    this->cols = cols;
    for (int row = 0; row < rows; row++)
    {
        std::vector<int> rowMap;
        for (int col = 0; col < cols; col++)
        {
            rowMap.push_back(0);
        }
        this->baseMap.push_back(rowMap);
    }
}
void ConsoleDraw::createMainWindow()
{
    int l_rows = rows + 2, l_cols = cols + 2, l_cols_n = CELL_WIDTH * l_cols;
    for (int col = 0; col < l_cols_n; col += CELL_WIDTH)
    {
        _SetConsoleCursor(col + leftMargin, topMargin);
        std::cout << CELL_FILL;
        _SetConsoleCursor(col + leftMargin, l_rows - CELL_WIDTH + topMargin);
        std::cout << CELL_FILL;
    }
    for (int row = 0; row < l_rows; row++)
    {
        _SetConsoleCursor(leftMargin, row + topMargin);
        std::cout << CELL_FILL;
        _SetConsoleCursor(l_cols_n - CELL_WIDTH + leftMargin, row + topMargin);
        std::cout << CELL_FILL;
    }
}
void ConsoleDraw::drawMap(std::vector<std::vector<int>> &map)
{
    int l_rows = map.size(), l_cols = map[0].size();
    for (int row = 0; row < l_rows; row++)
    {
        for (int col = 0; col < l_cols; col++)
        {
            if (this->baseMap[row][col] != map[row][col])
            {
                this->baseMap[row][col] = map[row][col];
                int x = CELL_WIDTH * (col + 1) + leftMargin;
                int y = row + topMargin + 1;
                _SetConsoleCursor(x, y);
                std::cout << (this->baseMap[row][col] == 0 ? CELL_EMPTY : CELL_FILL);
            }
        }
    }
}
void ConsoleDraw::drawBlock(Block &block, int leftMargin, int topMargin)
{
    for (int i = 0; i < BLOCK_CELL_SIZE; i++)
    {
        _SetConsoleCursor(CELL_WIDTH * (block.smallBlock[i].col + 1) + leftMargin, block.smallBlock[i].row + topMargin + 1);
        std::cout << CELL_FILL;
    }
}
void ConsoleDraw::unDrawBlock(Block &block, int leftMargin, int topMargin)
{
    for (int i = 0; i < BLOCK_CELL_SIZE; i++)
    {
        _SetConsoleCursor(CELL_WIDTH * (block.smallBlock[i].col + 1) + leftMargin, block.smallBlock[i].row + topMargin + 1);
        std::cout << CELL_EMPTY;
    }
}
void ConsoleDraw::gameOver()
{
    const int len = 12;
    char gameOver[len] = {'G', 'a', 'm', 'e', ' ', 'o', 'v', 'e', 'r', '!', '!', '!'};
    _SetConsoleCursor(CELL_WIDTH * ((cols - len) / 2) + leftMargin, rows / 2 + topMargin + 1);
    for (char c : gameOver)
    {
        std::cout << c;
    }
    _SetConsoleCursor(0, rows + 2);
}