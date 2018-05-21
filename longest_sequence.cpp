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

std::vector<std::pair<std::string, std::string>> lcs_sentences(std::string first_string, std::string second_string){
    std::vector<std::pair<std::string, std::string>> result_sentence;
    std::stringstream first_stream(first_string);
    std::stringstream second_stream(second_string);
    std::string temp_first, temp_second, result_words;
    while(std::getline(first_stream, temp_first, ' ') && std::getline(second_stream, temp_second, ' '))
        lcs_two_strings(temp_first, temp_second);
    return result_sentence;
}

std::string lcs_two_strings(std::string first_word, std::string second_word){
    std::cout << first_word << " " << second_word << std::endl;
    std::cout << first_word.size() << " " << second_word.size() << std::endl;
    std::vector<std::vector<int>> matrix_values = create_matrix<int>(first_word.size() + 1, second_word.size() + 1);
    std::vector<std::vector<char>> matrix_signs = create_matrix<char>(first_word.size(), second_word.size());
    for(int i = 1; i <= first_word.size(); ++i){
        for(int j = 1; j <= second_word.size(); ++j){
            if(first_word[i - 1] == second_word[j - 1]){
                matrix_values[i][j] = matrix_values[i - 1][j - 1] + 1;
                matrix_signs[i][j] = '\\';
            }
            else{
                if(matrix_values[i - 1][j] >= matrix_values[i][j - 1]){
                    matrix_values[i][j] = matrix_values[i - 1][j];
                    matrix_signs[i][j] = '^';
                }
                else{
                    matrix_values[i][j] = matrix_values[i][j - 1];
                    matrix_signs[i][j] = '<';
                }
            }
        }
    }
    print_matrix(matrix_values, first_word.size(), second_word.size());
    print_matrix(matrix_signs, first_word.size(), second_word.size());
    int temp_length = matrix_values[first_word.size()][second_word.size()];
    int i = first_word.size(), j = second_word.size();
    std::string result;
    result.resize(temp_length);
    while(temp_length){
        if(matrix_signs[i][j] == '\\'){
            --i;
            --j; 
            --temp_length;
            result[temp_length] = first_word[i];
        }
        else{
            if(matrix_signs[i][j] == '^') --i;
            else --j;
        }
    }
    return result;
}