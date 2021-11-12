#include <iostream>
#include <vector>
#include <ncurses.h>

#include "utils.h"

constexpr int space_between = 2;

/* Finds the longest entries, returns a vector with longest in each column */
std::vector<int> find_longest_entries(std::vector<std::string> &par_vec, std::vector<std::string> &header_vec,int num_of_values)
{
    int i = 0;
    std::vector<int> longestValues(num_of_values, 0);
    for (auto value : par_vec) {
        if (value.length() > longestValues[i]) {
            longestValues[i] = value.length();
        }
        i++;
        if (i % (num_of_values) == 0) {
            i = 0;
        }
    }
    return longestValues;
}

/* Returns a vector with the lengths of all of the headers */
std::vector<int> find_longest_headers(std::vector<std::string> &header_vec, int num_of_values)
{
    int i = 0;
    std::vector<int> headerLengths(num_of_values, 0);
    for (auto value : header_vec) {
        if (value.length() > headerLengths[i]) {
            headerLengths[i] = value.length();
        }
        i++;
    }
    return headerLengths;
}

/* Draws the header and lines under the headers */
void draw_header(std::vector<std::string> &par_vec, std::vector<std::string> &header_vec, int num_of_values)
{
    int length = 1;
    int column = 1;
    int i = 0;
    std::vector<int> longestValues = find_longest_entries(par_vec, header_vec, num_of_values);
    std::vector<int> headerLengths = find_longest_headers(header_vec, num_of_values);
    for (std::string value : header_vec) {
        int extra = 0;
        mvprintw(1, column, value.c_str());
        if (longestValues[i] > value.length()) {
            extra = longestValues[i] - value.length();
        }
        column += value.length() + space_between + extra;
        i++;
    }
    i = 0;
    for (int value : longestValues) {
        if (value < headerLengths[i]) {
            value = headerLengths[i];
        }
        i++;
        for (int i = 0; i < value; i++){
            mvprintw(2, length + i, "-");
        }
        length += value + space_between;
    }
}

/* Draws the entries below the headers */
void draw_entries(std::vector<std::string> &par_vec, std::vector<std::string> &header_vec, int num_of_values)
{
    std::vector<int> longestValues = find_longest_entries(par_vec, header_vec, num_of_values);
    std::vector<int> headerLengths = find_longest_headers(header_vec, num_of_values);
    int row = 2;
    int column = 1;
    int i = 0;
    for (std::string value : par_vec) {
        int extra = 0;
        if ((i % num_of_values) == 0) {
            row++;
            column = 1;
            i = 0;
        }
        mvprintw(row, column, value.c_str());
        if (longestValues[i] > headerLengths[i]) {
            extra = longestValues[i] - headerLengths[i];
        }
        column += headerLengths[i] + space_between + extra;
        i++;
    }
}

// make function to find total # of rows
void edit_cell(std::vector<std::string> &vec, int cur_row, int cur_col)
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

    vec[0] = token;
}

// TODO Figure out what to do with these
int keyPress = 0;
int highlight_row = 1;
int highlight_col = 1;
constexpr int KEY_J = 106;
constexpr int KEY_K = 107;
constexpr int KEY_L = 108;
constexpr int KEY_H = 104;
constexpr int KEY_Q = 113;
constexpr int KEY_E = 101;

void menu_init(std::vector<std::string> &vec, std::vector<std::string> &headVec,int num_of_columns)
{
    clear_refresh();
    draw_header(vec, headVec, 3);
    std::vector<int> longestValues = find_longest_entries(vec, headVec, num_of_columns);
    std::vector<int> headerLengths = find_longest_headers(headVec, num_of_columns);
    int row = 2;
    int column = 1;
    int i = 0;
    int cur_col = 1;
    int num_of_rows = 0;
    for (int p = 0; p < vec.size(); p++) {
        if (p % num_of_columns == 0) {
            num_of_rows++;
        }
    }
    if (vec.size() % num_of_columns == 0) {
        num_of_rows++;
    }
    for (std::string value : vec) {
        int extra = 0;
        if ((i % num_of_columns) == 0) {
            row++;
            column = 1;
            cur_col = 1;
            i = 0;
        }
        if (highlight_row == (row - 2) && highlight_col == cur_col){
            wattron(stdscr, A_REVERSE);
        }
        mvprintw(row, column, value.c_str());
        wattroff(stdscr, A_REVERSE);
        if (longestValues[i] > headerLengths[i]) {
            extra = longestValues[i] - headerLengths[i];
        }
        column += headerLengths[i] + space_between + extra;
        i++;
        cur_col++;
    }
    keyPress = wgetch(stdscr);
    // TODO Every row can have a different number of columns, figure out how to do bounds checking with that (maybe check every column for number of rows)
    int test = vec.size() % num_of_columns;
    switch(keyPress) {
        case KEY_K:
            highlight_row--;
            if (highlight_row == 0) {
                highlight_row = 1;
            }
            break;
        case KEY_J:
            highlight_row++;
            if (test != 0) {
                if (highlight_col == num_of_columns) {
                    if (highlight_row == test + 1) {
                        highlight_row = test;
                    }
                }
            }
            if (highlight_row == num_of_rows + 1) {
                highlight_row = num_of_rows;
            }
            break;
        case KEY_H:
            highlight_col--;
            if (highlight_col == 0) {
                highlight_col = 1;
            }
            break;
        case KEY_L:
            highlight_col++;
            if (test != 0) {
                if (highlight_row == num_of_rows) {
                    if (highlight_col == test + 1) {
                        highlight_col = test;
                    }
                }
            }
            if (highlight_col == (num_of_columns + 1)) {
                highlight_col = num_of_columns;
            }
            break;
        case KEY_Q:
            endwin();
            exit(0);
        case KEY_E:
            edit_cell(vec, row - 2, cur_col);
    }
}

/* Function for end users to use */
void draw_table(std::vector<std::string> &entries_vec, std::vector<std::string> &header_vec, int num_of_values)
{
    draw_header(entries_vec, header_vec, num_of_values);
    draw_entries(entries_vec, header_vec, num_of_values);
}

