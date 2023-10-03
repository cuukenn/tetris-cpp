#pragma once
#include <vector>
#include "block.h"
#include "segment.h"
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
    int blockSize;
    int leftMargin;
    int topMargin;
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
    Tetris(int rows, int cols, int left, int top, int blockSize);
    ~Tetris();
    void play();
};
