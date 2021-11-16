#include <iostream>
#include <vector>
#include <fstream>
#include <ncurses.h>

#include "utils.h"

std::vector<std::string> file_input()
{
    std::vector<std::string> vec;
    std::fstream file;
    file.open("saved.txt");
    std::string line;
    while (std::getline(file, line)) {
        vec.push_back(line);
    }
    return vec;
}

void file_output(std::vector<std::string> &vec, int num_of_rows)
{
    std::fstream file;
    file.open("saved.txt");
    for (auto cell : vec) {
        file << cell << "\n";
    }
    wattron(stdscr, A_BOLD);
    mvprintw(num_of_rows + 4, 1, "Successfully Saved File...");
    wattroff(stdscr, A_BOLD);
    getch();
    clear_refresh();
}
