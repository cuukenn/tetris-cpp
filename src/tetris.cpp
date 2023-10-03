#include "tetris.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <random>
#include <conio.h>

Tetris::Tetris(int rows, int cols, int left, int top, int blockSize)
{
    this->rows = rows;
    this->cols = cols;
    this->leftMargin = left;
    this->topMargin = top;
    this->blockSize = blockSize;
    for (int row = 0; row < this->rows; row++)
    {
        std::vector<int> rowMap;
        for (int col = 0; col < this->cols; col++)
        {
            rowMap.push_back(0);
        }
        this->map.push_back(rowMap);
    }
}

Tetris::~Tetris()
{
}
void Tetris::init()
{
    srand(time(NULL));

    for (int row = 0; row < this->rows; row++)
    {
        for (int col = 0; col < this->cols; col++)
        {
            map[row][col] = 0;
        }
    }

    this->level = 1;
    this->delay = SPEED_NORMAL[this->level - 1];
    this->score = 0;
    this->lineCount = 0;
    this->update = false;

    std::ifstream file(RECORD_FILE, std::fstream::in | std::fstream::out | std::fstream::app);
    if (!file.is_open())
    {
        std::cout << RECORD_FILE << ": open failed" << std::endl;
        this->higestScore = 0;
    }
    else
    {
        file >> this->higestScore;
    }
    file.close();

    this->gameOver = false;
}
void Tetris::play()
{
    init();

    nextBlock = new Block;
    curBlock = nextBlock;
    nextBlock = new Block;

    this->createMain();
    int timer = 0;
    while (1)
    {
        // get user key ops
        keyEvent();
        timer += getDelay();
        if (timer >= delay)
        {
            timer = 0;
            update = true;
            drop();
        }
        if (update)
        {
            update = false;
            // update screen
            updateWindow();
            // drain line
            clearLine();
        }
        if (this->gameOver)
        {
            this->higestScore = this->score;
            system("pause");
            this->init();
        }
    }
}
void Tetris::keyEvent()
{
    unsigned char ch;
    int dx = 0;
    bool rotateFlag = false;
    if (_kbhit())
    {
        ch = _getch();
        switch (ch)
        {
        case 'w':
            rotateFlag = true;
            break;
        case 'a':
            dx = -1;
            break;
        case 's':
            delay = SPEED_QUICK;
            break;
        case 'd':
            dx = 1;
            break;
        default:
            break;
        }
    }
    if (rotateFlag)
    {
        rotate();
        update = true;
        rotateFlag = false;
    }
    if (dx != 0)
    {
        moveLeftRight(dx);
        update = true;
    }
}
void Tetris::updateWindow()
{
    for (int row = 0; row < this->rows; row++)
    {
        for (int col = 0; col < this->cols; col++)
        {
            if (this->map[row][col] == 0)
            {
                continue;
            }

            int x = col * blockSize + leftMargin;
            int y = row * blockSize + topMargin;
            _SetConsoleCursor(x, y);
            std::cout << "*";
        }
    }

    backBlock.undraw(leftMargin, topMargin);
    curBlock->draw(leftMargin, topMargin);
    backNextBlock.undraw(this->cols + 10, this->rows >> 1);
    nextBlock->draw(this->cols + 10, this->rows >> 1);
}
int Tetris::getDelay()
{
    static unsigned long long lastTime = 0;
    unsigned long long currentTime = GetTickCount();
    if (lastTime == 0)
    {
        lastTime = currentTime;
        return 0;
    }
    else
    {
        int ret = currentTime - lastTime;
        lastTime = currentTime;
        return ret;
    }
}
void Tetris::drop()
{
    backBlock = *curBlock;
    curBlock->drop();

    if (!curBlock->blockInMap(map))
    {
        backBlock.solidify(map);
        delete curBlock;
        curBlock = nextBlock;
        backNextBlock = *nextBlock;
        nextBlock = new Block;

        this->checkOver();
    }
    delay = SPEED_NORMAL[level - 1];
}
void Tetris::checkOver()
{
    if (this->curBlock->blockInMap(this->map) == false)
    {
        this->gameOver = true;
    }
}
void Tetris::clearLine()
{
    int lines = 0;
    for (int row = this->rows - 1, k = this->rows - 1; row >= 0; row--)
    {
        int cn = 0;
        for (int col = 0; col < this->cols; col++)
        {
            if (this->map[row][col] == 1)
            {
                cn++;
            }
            this->map[k][col] = this->map[row][col];
        }
        if (cn < this->cols)
        {
            k--;
        }
        else
        {
            lines++;
        }
    }
    if (lines > 0)
    {
        int addScore[4] = {10, 30, 60, 80};
        this->score += addScore[lines - 1];
        this->lineCount += lines;
        // 难度升级
        this->level = (score + 99) / 100;
        if (level > MAX_LEVEL)
        {
            this->gameOver = true;
        }
        this->update = true;
    }
}
void Tetris::moveLeftRight(int offset)
{
    this->backBlock = *this->curBlock;
    this->curBlock->moveleftRigt(offset);

    if (!this->curBlock->blockInMap(map))
    {
        *this->curBlock = this->backBlock;
    }
}
void Tetris::rotate()
{
    this->backBlock = *this->curBlock;
    this->curBlock->rotate();
    if (!curBlock->blockInMap(map))
    {
        *this->curBlock = this->backBlock;
    }
}
void Tetris::createMain()
{
    // int l_rows = this->rows, l_cols = this->cols;
    // for (int col = 0; col < l_cols; col++)
    // {
    //     _SetConsoleCursor(col, 0);
    //     std::cout << "*";
    //     _SetConsoleCursor(col, l_rows);
    //     std::cout << "*";
    // }
    // for (int row = 0; row < l_rows; row++)
    // {
    //     _SetConsoleCursor(0, row);
    //     std::cout << "*";
    //     ;
    //     _SetConsoleCursor(l_cols, row);
    //     std::cout << "*";
    // }
}
