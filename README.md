# Kos

Kos is an ncurses table system. Currently is is a menu system that mirrors rudimentary functions of excel

[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

## Features

- Ability to easily create an excel like table
- Add/remove cells
- Move cells around in table
- Edit cells within the table
- Save table to file
- Create a table without a menu
- Simple, scalable progress bars


## Documentation

### Excel Table Example
```cpp
#include <iostream>
#include <vector>
#include <ncurses.h>

#include "utils.h"
#include "table.h"

int main() 
{
    // Sets up ncurses, this can be done manually
    init_ncurses();

    std::vector<std::string> headers = {"Header1", "Header2"};
    std::vector<std::string> entries = file_input();

    while (true) {
        // (vector_with_cells, vector_with_headers)
        menu_init(entries, headers);
    }

    endwin();
}
```
In the above an example a file named "saved.txt" needs to contain the desired cells in the table, this is where the program will read and write from

---

### Progress Bar Example
```cpp
#include <iostream>
#include <ncurses.h>

#include "progress_bar.h"
#include "utils.h"

int main()
{
    // Sets up ncurses, this can be done manually
    init_ncurses();

    // (percent, length, show_percent, row = 0, column = 0)
    print_progress_bar(45, 20, true);

    getch();
    endwin();
}
```
Output:
```
[#########-----------] [45.00%]
```

### Keybindings:
```
Cursor Movement:
h - select cell to the left
j - select cell below
k - select cell above
l - select cell to the right

Cell Movement:
H - move cell to the left
J - move cell below
K - move cell above
L - move cell to the right

Cell Manipulation:
n - creates a new cell
x - deletes selected cell
e - edits selected cell

Other:
s - saves table to "saved.txt"
q - quits program (does NOT autosave)
```

## Todo

- Make this into a static shared library
- Make simple tables work again
- Make vectors be able to hold any datatype
- Be able to do calculations on cells 
