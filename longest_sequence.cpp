#include "header.hpp"
#include "functions.hpp"
#include "longest_sequence.hpp"

template <typename T>
void print_matrix(T matrix, int height, int width){
    for(int i = 0; i <= height; ++i){
        for(int j = 0; j <= width; ++j)
            std::cout << matrix[i][j] << " ";
        std::cout << std::endl;
    }
}

template <typename T>
std::vector<std::vector<T>> create_matrix(int height, int width){
    std::vector<std::vector<T>> matrix(height + 1);
    for(int i = 0; i <= height; ++i){
        std::vector<T> array(width + 1, 0);
        matrix[i] = array;
    }
    return matrix;
}

std::string longest_subsequence_between_2strings(std::string first_string, std::string second_string){
    std::cout << first_string << " " << second_string << std::endl;
    std::cout << first_string.size() << " " << second_string.size() << std::endl;
    std::vector<std::vector<int>> matrix_values = create_matrix<int>(first_string.size() + 1, second_string.size() + 1);
    std::vector<std::vector<char>> matrix_signs = create_matrix<char>(first_string.size(), second_string.size());
    // print_matrix(matrix_values, first_string.size(), second_string.size());
    // print_matrix(matrix_signs, first_string.size(), second_string.size());
    for(int i = 1; i <= first_string.size(); ++i){
        for(int j = 1; j <= second_string.size(); ++j){
            if(first_string[i - 1] == second_string[j - 1]){
                matrix_values[i][j] = matrix_values[i - 1][j - 1] + 1;
                matrix_signs[i][j] = '\\';
            }
            else{
                if(matrix_values[i - 1][j] >= matrix_values[i][j - 1]){
                    matrix_values[i][j] = matrix_values[i - 1][j];
                    matrix_signs[i][j] = 94;
                }
                else{
                    matrix_values[i][j] = matrix_values[i][j - 1];
                    matrix_signs[i][j] = 60;
                }
            }
        }
    }
    print_matrix(matrix_values, first_string.size(), second_string.size());
    print_matrix(matrix_signs, first_string.size(), second_string.size());
}