#include <iostream>
#include <ncurses.h>

void clear_refresh()
{
    wclear(stdscr);
    wrefresh(stdscr);
}

void init_ncurses()
{
    clear_refresh();
    initscr();
    curs_set(0);
    setlocale(LC_ALL, "");
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
}
