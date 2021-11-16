#pragma once
#include <iostream>
#include <vector>

void edit_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns);
void add_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns);
void remove_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns);
