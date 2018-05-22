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
    // print_matrix(matrix_values, first_word.size(), second_word.size());
    // print_matrix(matrix_signs, first_word.size(), second_word.size());
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

std::vector<std::pair<std::string, std::string>> lcs_sentences(std::string first_sentence, std::string second_sentence){
    std::vector<std::pair<std::string, std::string>> result_sentence;
    std::stringstream first_stream(first_sentence);
    std::stringstream second_stream(second_sentence);
    std::string first_word, second_word, result_word, diff_sum, diff_signs;
    while(std::getline(first_stream, first_word, ' ') && std::getline(second_stream, second_word, ' ')){
        result_word = lcs_two_strings(first_word, second_word);
        std::cout << result_word << std::endl <<std::endl;
        diff_sum.reserve(first_word.size() + second_word.size() - result_word.size());
        diff_signs.reserve(first_word.size() + second_word.size() - result_word.size());
        int l = 0, k = 0, j = 0;
        for(int i = 0; i < first_word.size() + second_word.size() - result_word.size(); ++i){
            //std::cout << "bleeeeeeeeeeeeee" << std::endl;
            if(l != result_word.size() && (k != first_word.size() && first_word[k] == result_word[l]) && (j != second_word.size() && second_word[j] == result_word[l])){
                diff_sum += result_word[l];
                diff_signs += '=';
                //std::cout << diff_signs.size() << "\n" << diff_sum.size() << std::endl;
                k++;
                j++;
                l++;
            }
            else{
                if (k != first_word.size() && first_word[k] != result_word[l]){
                    diff_sum += first_word[k];
                    diff_signs += '-';
                    k++;
                }
                if (j != second_word.size() && second_word[j] != result_word[l]){
                    diff_sum += second_word[j];
                    diff_signs += '+';
                    j++;
                }
            }
        }
        std::cout << diff_signs << "\n" << diff_sum << std::endl;
        diff_signs.clear();
        diff_sum.clear();
    }
    return result_sentence;
}