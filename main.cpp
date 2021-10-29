#include <iostream>
#include <vector>
#include <ncurses.h>
#include <sstream>

constexpr int space_between = 2;

void clear_refresh()
{
    wclear(stdscr);
    wrefresh(stdscr);
}

template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

void print_progress_bar(float percent, int lengthOfBar = 20, int row = 0, int column = 0, bool show_percent = false)
{
    std::string output = " [";
    int numOfHashes = stof(to_string_with_precision(percent / 10.0)) * (lengthOfBar / 10);
    for (int i = 0; i < numOfHashes; i++) {
        output += "#";
    }
    for (int i = 0; i < (lengthOfBar - numOfHashes); i++) {
        output += "-";
    }
    output += "] ";
    if (show_percent) {
        output += "[" + to_string_with_precision(percent * 10) + "%]";
    }
    mvprintw(row, column, output.c_str());
}

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
    for (auto value : header_vec) {
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
    for (auto value : par_vec) {
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

/* Function for end users to use */
void draw_table(std::vector<std::string> &entries_vec, std::vector<std::string> &header_vec, int num_of_values)
{
    draw_header(entries_vec, header_vec, num_of_values);
    draw_entries(entries_vec, header_vec, num_of_values);
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

int main()
{
    init_ncurses();
    /* TODO PORT MENU_INITILIZATION TO THIS TO HAVE THE OPTION TO TURN THE TABLE INTO A MENU, AND MAKE IT EASY TO ADD NEW SELECTIONS IN THE MENU AS WELL */
    std::vector<std::string> headers = {"Test Headerrrrrr", "What", "Yooo this is cool"};
    std::vector<std::string> entries = {"Test Entry", "Whyyyyyy", "I can now exceed :)", "ok ig", "what", "okay", "I", "Guesss"};
    draw_table(entries, headers, 3);
    mvprintw(7, 1, "Press any key to exit...");
    print_progress_bar(45, 20, 10);
    getch();
    endwin();
}
