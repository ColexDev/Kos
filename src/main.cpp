#include <iostream>
#include <vector>
#include <ncurses.h>

#include "table.h"
#include "progress_bar.h"
#include "utils.h"
#include "file.h"

int main()
{
    init_ncurses();
    std::vector<std::string> headers = file_input_header();
    std::vector<std::string> entries = file_input_cell();
    // draw_table(entries, headers, 3);

    // TODO Always run menu_init at the end of the loop or else other things will not show up until a key is pressed
    while (true) {
        // print_progress_bar(45, 20, true, 10);
        menu_init(entries, headers);
    }
    endwin();
}
