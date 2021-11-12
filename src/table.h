#pragma once
#include <iostream>
#include <vector>
#include <ncurses.h>

std::vector<int> find_longest_entries(std::vector<std::string> &par_vec, std::vector<std::string> &header_vec,int num_of_values);
std::vector<int> find_longest_headers(std::vector<std::string> &header_vec, int num_of_values);
void draw_header(std::vector<std::string> &par_vec, std::vector<std::string> &header_vec, int num_of_values);
void draw_entries(std::vector<std::string> &par_vec, std::vector<std::string> &header_vec, int num_of_values);
void draw_table(std::vector<std::string> &entries_vec, std::vector<std::string> &header_vec, int num_of_values);
void menu_init(std::vector<std::string> &vec, std::vector<std::string> &headVec,int num_of_columns);
