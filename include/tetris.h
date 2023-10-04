#pragma once
#include <vector>
#include "segment.h"
#include "draw.h"
#include "block.h"
#define MAX_LEVEL 5
#define RECORD_FILE "record_file.txt"
const int SPEED_QUICK = 50;                                   // ms
const int SPEED_NORMAL[MAX_LEVEL] = {500, 300, 150, 100, 80}; // ms
class Tetris
{
private:
    // init config
    int rows;
    int cols;
    int delay;
    int level;

    // game status
    bool gameOver;
    bool update;
    std::vector<std::vector<int>> map;

    // score
    int score;
    int higestScore;
    int lineCount;

    // Block
    Block *curBlock;
    Block *nextBlock;
    Block backBlock;
    Block backNextBlock;

    Draw *iDraw;

private:
    void init();
    void keyEvent();
    void updateWindow();
    int getDelay();
    void drop();
    void clearLine();
    void moveLeftRight(int offset);
    void rotate();
    void checkOver();
    void createMain();

public:
    Tetris(int rows, int cols, Draw *draw);
    ~Tetris();
    void play();
};
