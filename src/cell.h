#pragma once
#include <iostream>
#include <vector>

void edit_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns);
void add_cell_at_end(std::vector<std::string> &vec);
void remove_cell(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns);
void add_cell_at_current(std::vector<std::string> &vec, int cur_row, int cur_col, int num_of_columns);
void add_header_at_end(std::vector<std::string> &header_vec);
void add_header_at_current(std::vector<std::string> &header_vec, int cur_col);
void remove_header(std::vector<std::string> &header_vec, int cur_col, int num_of_columns);
std::string ask_cell_data();
