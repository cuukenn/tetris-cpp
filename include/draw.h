#pragma once
#include <vector>
#include "block.h"
class Draw
{
public:
    virtual void createMainWindow() = 0;
    virtual void drawMap(std::vector<std::vector<int>> &map) = 0;
    virtual void drawBlock(Block &block, int leftMargin, int topMargin) = 0;
    virtual void unDrawBlock(Block &block, int leftMargin, int topMargin) = 0;
    virtual void gameOver() = 0;
};
class ConsoleDraw : public Draw
{
private:
    int rows;
    int cols;
    int leftMargin;
    int topMargin;
    std::vector<std::vector<int>> baseMap;

public:
    ConsoleDraw(int rows, int cols, int leftMargin, int topMargin);
    virtual void createMainWindow() override;
    virtual void drawMap(std::vector<std::vector<int>> &map);
    virtual void drawBlock(Block &block, int leftMargin, int topMargin) override;
    virtual void unDrawBlock(Block &block, int leftMargin, int topMargin) override;
    virtual void gameOver() override;
};