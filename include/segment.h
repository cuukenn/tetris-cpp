#pragma once
#include <windows.h>
inline void _SetConsoleCursor(int x, int y)
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD c = {(SHORT)x, (SHORT)y};
    SetConsoleCursorPosition(hOut, c);
}