# Kos

Kos is an ncurses table system. Currently is is a menu system that mirrors rudimentary functions of excel

[![GPLv3 License](https://img.shields.io/badge/License-GPL%20v3-yellow.svg)](https://opensource.org/licenses/)

## Features

- Ability to easily create an excel like table
- Move cells around in table
- Edit cells within the table
- Save table to file
- Create a table without a menu


## Documentation

Example of setting up an Excel like table
```cpp
#include <iostream>
#include <vector>
#include <ncurses.h>

#include "utils.h"
#include "table.h"

int main() 
{
    init_ncurses();
    std::vector<std::string> headers = {"Header1", "Header2"};
    std::vector<std::string> entries = file_input();

    while(true) {
        menu_init(entries, headers);
    }
    endwin();
}
```
In the above an example a file named "saved.txt" needs to contain the desired cells in the table, this is where the program will read and write from

## Todo

- Make this easily usable by #include 
- Make simple tables work again
- Add more functionality to excel like tables (menu_init)

