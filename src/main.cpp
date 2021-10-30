#include <iostream>
#include <vector>
#include <ncurses.h>

#include "table.h"
#include "progress_bar.h"
#include "utils.h"



int main()
{
    init_ncurses();
    /* TODO PORT MENU_INITILIZATION TO THIS TO HAVE THE OPTION TO TURN THE TABLE INTO A MENU, AND MAKE IT EASY TO ADD NEW SELECTIONS IN THE MENU AS WELL */
    std::vector<std::string> headers = {"Test Headerrrrrr", "Test Header 2", "Longer Test header"};
    std::vector<std::string> entries = {"Test Entry", "Test Entry 2", "Test Entry 3", "This is a long test entry", "Test 5", "Test Entry 6", "Test Entry 7", "Test Entry 8"};
    draw_table(entries, headers, 3);
    mvprintw(7, 1, "Press any key to exit...");
    print_progress_bar(45, 20, 10);
    getch();
    endwin();
}
