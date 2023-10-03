#include "tetris.h"
int main(int argc, char *args[])
{
    Tetris game(20, 14, 0, 0, 1);
    game.play();
    return 0;
}