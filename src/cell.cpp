#include <iostream>
#include <vector>
#include <ncurses.h>

#include "utils.h"

void edit_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns)
{
    char token[512];
    int row, col;
    getmaxyx(stdscr, row, col);
    mvprintw(row - 1, 1, "Enter new cell data: ");
    move(row - 1, 22);
    echo();
    curs_set(1);
    getstr(token);
    curs_set(0);
    noecho();
    clear_refresh();

    int index = ((cur_row - 1) * num_of_columns) + cur_col - 1;
    vec[index] = token;
}

void add_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns)
{
    char token[512];
    int row, col;
    getmaxyx(stdscr, row, col);
    mvprintw(row - 1, 1, "Enter new cell data: ");
    move(row - 1, 22);
    echo();
    curs_set(1);
    getstr(token);
    curs_set(0);
    noecho();
    clear_refresh();

    vec.push_back(token);

}

void remove_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns)
{
    int index = ((cur_row - 1) * num_of_columns) + cur_col - 1;
    if (!(index < 0)) {
        vec.erase(vec.begin() + index);
    }
    clear_refresh();
}
