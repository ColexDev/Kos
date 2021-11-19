#pragma once
#include <iostream>
#include <vector>

std::vector<std::string> file_input_header();
std::vector<std::string> file_input_cell();
void file_output_cell(std::vector<std::string> &vec, int num_of_rows);
void file_output_header(std::vector<std::string> &vec, int num_of_rows);
