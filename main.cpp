#include <windows.h>
#include "tetris.h"
int main(int argc, char *args[])
{
    system("mode con cols=100 lines=40");
    system("chcp 65001");
    system("title Tetris");
    system("cls");
    int rows = 20, cols = 14;
    Tetris game(rows, cols, new ConsoleDraw(rows, cols, 0, 0));
    game.play();
    return 0;
}