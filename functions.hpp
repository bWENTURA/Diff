#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

void manage_file(std::istream& file_0, std::istream& file_1);

template <typename T>
void print_matrix(T matrix, int height, int width);

template <typename T>
std::vector<std::vector<T>> create_matrix(int height, int width);

#endif