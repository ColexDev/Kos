#include <iostream>
#include <vector>
#include <ncurses.h>

#include "utils.h"

std::string ask_cell_data()
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
    std::string token_ = token;
    return token_;
}

void edit_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns)
{
    int index = ((cur_row - 1) * num_of_columns) + cur_col - 1;
    vec[index] = ask_cell_data();
}

void add_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns)
{
    vec.push_back(ask_cell_data());
}

void remove_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns)
{
    int index = ((cur_row - 1) * num_of_columns) + cur_col - 1;
    if (!(index < 0)) {
        vec.erase(vec.begin() + index);
    }
    clear_refresh();
}
