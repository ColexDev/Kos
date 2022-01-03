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

**NOTE**: Currently only supports data type(s) - std::string

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

    std::vector<std::string> headers = file_input_header();
    std::vector<std::string> entries = file_input_cell();

    while (true) {
        // (vector_with_cells, vector_with_headers)
        table_init(entries, headers);
    }

    endwin();
}
```
In the above an example a file named "cell.txt" needs to contain the desired cells in the table and "header.txt" needs to contain the desired headers, this is where the program will read and write from

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

---

### Keybindings
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
n - creates a new cell at the current cursor position
N - creates a new cell at the end of the table
x - deletes selected cell
e - edits data selected cell

Header Manipulation:
t - creates new header in current column
T - creates a new header after other headers
C-x - removes header of selected column 

Other:
s - saves table to "cell.txt" and "header.txt"
q - quits program (does NOT autosave)
```

## Todo

- Make this into a static shared library
- Make simple tables work again
- Make vectors be able to hold any datatype
- Be able to do calculations on cells 
- Find better keybindings (mainly for header manipulation)
