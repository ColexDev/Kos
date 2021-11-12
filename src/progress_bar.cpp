#include <iostream>
#include <ncurses.h>
#include <sstream>

// TODO: Consider moving this to a utils.cpp file (if other utils exist as well)
template <typename T>
std::string to_string_with_precision(const T a_value, const int n = 2)
{
    std::ostringstream out;
    out.precision(n);
    out << std::fixed << a_value;
    return out.str();
}

void print_progress_bar(float percent, int lengthOfBar = 20, bool show_percent = false, int row = 0, int column = 0)
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
        output += "[" + to_string_with_precision(percent) + "%]";
    }
    mvprintw(row, column, output.c_str());
}

