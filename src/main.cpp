#include <iostream>
#include <vector>
#include <ncurses.h>

#include "table.h"
#include "progress_bar.h"
#include "utils.h"

int main()
{
    init_ncurses();
    std::vector<std::string> headers = {"Test Headerrrrrr", "Test Header 2", "Longer Test header", "New Header"};
    std::vector<std::string> entries = {"Test Entry", "Test Entry 2", "Test Entry 3", "This is a long test entry", "Test 5", "Test Entry 6", "Test Entry 7", "Test Entry 8", "Test 9", "Test 10", "Test 11", "Test 12", "Test 13"};
    // draw_table(entries, headers, 3);
    // NOTE: Always run new_menu_init at the end of the loop or else other things will not show up until a key is pressed
    while(true) {
        // print_progress_bar(45, 20, true, 8);
        menu_init(entries, headers);
    }
    endwin();
}
