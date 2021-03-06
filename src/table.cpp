#include <iostream>
#include <vector>
#include <ncurses.h>

#include "utils.h"
#include "file.h"
#include "cell.h"

#define ctrl(x) (x & 0x1F)

constexpr int space_between = 2;
int highlight_row = 1;
int highlight_col = 1;

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
// void draw_entries(std::vector<std::string> &par_vec, std::vector<std::string> &header_vec, int num_of_values)
// {
    // std::vector<int> longestValues = find_longest_entries(par_vec, header_vec, num_of_values);
    // std::vector<int> headerLengths = find_longest_headers(header_vec, num_of_values);
    // int row = 2;
    // int column = 1;
    // int i = 0;
    // for (std::string value : par_vec) {
        // int extra = 0;
        // if ((i % num_of_values) == 0) {
            // row++;
            // column = 1;
            // i = 0;
        // }
        // mvprintw(row, column, value.c_str());
        // if (longestValues[i] > headerLengths[i]) {
            // extra = longestValues[i] - headerLengths[i];
        // }
        // column += headerLengths[i] + space_between + extra;
        // i++;
    // }
// }

/* Function for end users to use */
// void draw_table(std::vector<std::string> &entries_vec, std::vector<std::string> &header_vec, int num_of_values)
// {
    // draw_header(entries_vec, header_vec, num_of_values);
    // draw_entries(entries_vec, header_vec, num_of_values);
// }

void table_init(std::vector<std::string> &vec, std::vector<std::string> &header_vec)
{
    const int num_of_columns = header_vec.size();
    const int size = vec.size();
    draw_header(vec, header_vec, num_of_columns);
    std::vector<int> longestValues = find_longest_entries(vec, header_vec, num_of_columns);
    std::vector<int> headerLengths = find_longest_headers(header_vec, num_of_columns);
    int row = 2;
    int column = 1;
    int i = 0;
    int cur_col = 1;
    int num_of_rows = 0;

    // This gets the number of rows in the table
    for (int p = 0; p < size; p++) {
        if (p % num_of_columns == 0) {
            num_of_rows++;
        }
    }
    if (size % num_of_columns == 0) {
        num_of_rows++;
    }

    // This prints out the cell values
    for (std::string value : vec) {
        int extra = 0;
        // Checks to see if the column needs to end and a new row needs to start
        if ((i % num_of_columns) == 0) {
            row++;
            column = 1;
            cur_col = 1;
            i = 0;
        }

        // Determines which to highlight
        if (highlight_row == (row - 2) && highlight_col == cur_col){
            wattron(stdscr, A_REVERSE);
        }

        mvprintw(row, column, value.c_str());

        wattroff(stdscr, A_REVERSE);

        // Changes the header length if any cell value is longer than the header length
        if (longestValues[i] > headerLengths[i]) {
            extra = longestValues[i] - headerLengths[i];
        }

        column += headerLengths[i] + space_between + extra;
        i++;
        cur_col++;
    }

    int cells_in_last_row = size % num_of_columns;
    std::string temp;
    // Current index in the vector
    int index = ((highlight_row - 1) * num_of_columns) + highlight_col - 1;

    // Checks for users keypress
    /* Does bounds checking
     * only allows the "cursor" to go the edge of the table
     */
    // FIX: Possibly make this less nested as this is kinda cringe
    switch (getch()) {
    case 'k':
        highlight_row--;
        if (highlight_row == 0) {
            highlight_row = 1;
        }
        break;
    case 'j':
        highlight_row++;
        if (cells_in_last_row != 0) {
            if (highlight_row == num_of_rows) {
                if (highlight_col > cells_in_last_row) {
                    highlight_row = num_of_rows - 1;
                }
            }
        } else {
            if (highlight_row == num_of_rows) {
                highlight_row = num_of_rows - 1;
            }
        }

        if (highlight_row == num_of_rows + 1) {
            highlight_row = num_of_rows;
        }
        break;
    case 'h':
        highlight_col--;
        if (highlight_col == 0) {
            highlight_col = 1;
        }
        break;
    case 'l':
        highlight_col++;
        if (cells_in_last_row != 0) {
            if (highlight_row == num_of_rows) {
                if (highlight_col == cells_in_last_row + 1) {
                    highlight_col = cells_in_last_row;
                }
            }
        }
        if (highlight_col == (num_of_columns + 1)) {
            highlight_col = num_of_columns;
        }
        break;
    case 'H':
        if (highlight_col > 1) {
            temp = vec[index];
            vec[index] = vec[index - 1];
            vec[index - 1] = temp;
            highlight_col--;
            clear_refresh();
        }
        break;
    case 'L':
        if (highlight_col < num_of_columns) {
            if (!(highlight_row == num_of_rows && highlight_col == cells_in_last_row)) {
                temp = vec[index];
                vec[index] = vec[index + 1];
                vec[index + 1] = temp;
                highlight_col++;
                clear_refresh();
            }
        }
        break;
    case 'J':
        if (!(highlight_row == num_of_rows - 1 && highlight_col > cells_in_last_row)) {
            if (highlight_row < num_of_rows) {
                temp = vec[index];
                vec[index] = vec[index + num_of_columns];
                vec[index + num_of_columns] = temp;
                highlight_row++;
                clear_refresh();
            }
        }
        break;
    case 'K':
        if (highlight_row > 1) {
            temp = vec[index];
            vec[index] = vec[index - num_of_columns];
            vec[index - num_of_columns] = temp;
            highlight_row--;
            clear_refresh();
        }
        break;
    // NOTE: Removing all cells causes highlight_row to be 0 and highlight_col to be 4, this needs to be fixed
    case 'x':
        remove_cell(vec, highlight_row, highlight_col, num_of_columns);
        if (highlight_row == num_of_rows && highlight_col == 1 && cells_in_last_row == 1) {
            highlight_row--;
            highlight_col = num_of_columns;
        } else if (highlight_row == num_of_rows && highlight_col == cells_in_last_row || highlight_col == 4) {
            highlight_col--;
        }
        break;

        // TODO: ADD BOUNDS CHECKING FOR THIS
    case ctrl('x'):
        remove_header(header_vec, highlight_col, num_of_columns);
        if (highlight_col == num_of_columns && num_of_columns > 1) {
            highlight_col--;
        }
        break;
    case 'n':
        add_cell_at_current(vec, highlight_row, highlight_col, num_of_columns);
        break;
    case 'N':
        add_cell_at_end(vec);
        break;
    case 't':
        add_header_at_current(header_vec, highlight_col);
        break;
    case 'T':
        add_header_at_end(header_vec);
        break;
    case 's':
        file_output_header(header_vec, num_of_rows);
        file_output_cell(vec, num_of_rows);
        break;
    case 'q':
        endwin();
        exit(0);
    case 'e':
        edit_cell(vec, highlight_row, highlight_col, num_of_columns);
    case 'o':
        break;
        // NOTE: Try to make the ability to have certain cells run certain functions (maybe just remake menu_init and have it do this like old menu_init in Corcyra
    }
    clear_refresh();
}
