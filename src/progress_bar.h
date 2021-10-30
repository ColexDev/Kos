#pragma once
#include <iostream>
#include <ncurses.h>
#include <sstream>

void print_progress_bar(float percent, int lengthOfBar = 20, int row = 0, int column = 0, bool show_percent = false);
