#include <iostream>
#include <vector>
#include <ncurses.h>

#include "utils.h"

std::string ask_cell_data(std::string input = "Enter new cell data: ")
{
    char token[512];
    int row, col;
    getmaxyx(stdscr, row, col);
    mvprintw(row - 1, 1, input.c_str());
    move(row - 1, input.length() + 1);
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

void add_cell_at_end(std::vector<std::string> &vec)
{
    vec.push_back(ask_cell_data());
}

void add_cell_at_current(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns)
{
    int index = ((cur_row - 1) * num_of_columns) + cur_col - 1;
    auto position = vec.begin() + index;
    vec.insert(position, ask_cell_data());
}

void remove_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns)
{
    int index = ((cur_row - 1) * num_of_columns) + cur_col - 1;
    if (!(index < 0)) {
        vec.erase(vec.begin() + index);
    }
    clear_refresh();
}

void add_header_at_end(std::vector<std::string> &header_vec)
{
    header_vec.push_back(ask_cell_data("Enter new header name: "));
}

void add_header_at_current(std::vector<std::string> &header_vec, int cur_col)
{
    auto position = header_vec.begin() + cur_col - 1;
    header_vec.insert(position, ask_cell_data("Enter new header name: "));
}

void remove_header(std::vector<std::string> &header_vec, int cur_col, int num_of_columns)
{
    auto position = header_vec.begin() + cur_col - 1;
    if (num_of_columns != 1) {
        header_vec.erase(position);
    }
}
