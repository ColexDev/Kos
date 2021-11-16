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
    std::vector<std::string> entries = file_input();
    // draw_table(entries, headers, 3);

    // NOTE: Always run menu_init at the end of the loop or else other things will not show up until a key is pressed
    while (true) {
        // print_progress_bar(45, 20, true, 8);
        menu_init(entries, headers);
    }
    endwin();
}
