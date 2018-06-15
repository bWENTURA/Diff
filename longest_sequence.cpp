#include "header.hpp"
#include "functions.hpp"
#include "longest_sequence.hpp"

// template <typename T>
// void print_matrix(T matrix, int height, int width){
//     for(int i = 0; i <= height; ++i){
//         for(int j = 0; j <= width; ++j)
//             std::cout << matrix[i][j] << " ";
//         std::cout << std::endl;
//     }
// }

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
    int temp_length = matrix_values[first_word.size()][second_word.size()];
    int i = first_word.size(), j = second_word.size();
    std::string result_word;
    result_word.resize(temp_length);
    while(temp_length){
        if(matrix_signs[i][j] == '\\'){
            --i;
            --j; 
            --temp_length;
            result_word[temp_length] = first_word[i];
        }
        else{
            if(matrix_signs[i][j] == '^') --i;
            else --j;
        }
    }
    return result_word;
}

std::pair<std::string, std::string> create_pair_of_diff(std::string first_word, std::string second_word, std::string result_word){
    std::string diff_sum, diff_signs;
    diff_sum.reserve(2*(first_word.size() + second_word.size() - result_word.size()));
    diff_signs.reserve(2*(first_word.size() + second_word.size() - result_word.size()));
    int l = 0, k = 0, j = 0;
    for(int i = 0; i < first_word.size() + second_word.size() - result_word.size(); ++i){
        if(l != result_word.size() && (k != first_word.size() && first_word[k] == result_word[l]) && (j != second_word.size() && second_word[j] == result_word[l])){
            diff_sum += result_word[l];
            diff_sum += " ";
            diff_signs += "= ";
            k++;
            j++;
            l++;
        }
        else{
            if (k != first_word.size() && first_word[k] != result_word[l]){
                diff_sum += first_word[k];
                diff_sum += " ";
                diff_signs += "- ";
                k++;
            }
            if (j != second_word.size() && second_word[j] != result_word[l]){
                diff_sum += second_word[j];
                diff_sum += " ";
                diff_signs += "+ ";
                j++;
            }
        }
    }
    std::pair<std::string, std::string> result_pair(diff_signs, diff_sum);
    return result_pair;
}

// std::vector<std::pair<std::string, std::string>> lcs_sentences(std::string first_sentence, std::string second_sentence){
//     std::vector<std::pair<std::string, std::string>> result_sentence;
//     std::vector<std::pair<std::string, std::string>> vec_of_diffs;
//     std::stringstream first_stream(first_sentence);
//     std::stringstream second_stream(second_sentence);
//     std::string first_word, second_word, diff_sum, diff_signs;
//     while(std::getline(first_stream, first_word, ' ') && std::getline(second_stream, second_word, ' ')){
//         vec_of_diffs.push_back(create_pair_of_diff(first_word, second_word, lcs_two_strings(first_word, second_word)));
//     }
//     for(auto it: vec_of_diffs)
//         std::cout << it.first << ",    ";
//     std::cout << "\n";
//     for(auto it: vec_of_diffs)
//         std::cout << it.second << ",    ";
//     std::cout << std::endl;
//     return result_sentence;
// }

float calculate_lcs_sentences(const std::vector<std::string>& first_sentence, const std::vector<std::string>& second_sentence){
    float lcs_lenght = 0;
    // std::cout << first_sentence << " " << second_sentence << std::endl;
    // std::cout << first_sentence.size() << " " << second_sentence.size() << std::endl;
    std::vector<std::vector<int>> matrix_values = create_matrix<int>(first_sentence.size() + 1, second_sentence.size() + 1);
    std::vector<std::vector<char>> matrix_signs = create_matrix<char>(first_sentence.size(), second_sentence.size());
    for(int i = 1; i <= first_sentence.size(); ++i){
        for(int j = 1; j <= second_sentence.size(); ++j){
            if(first_sentence[i - 1] == second_sentence[j - 1]){
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
    int temp_length = matrix_values[first_sentence.size()][second_sentence.size()];
    int i = first_sentence.size(), j = second_sentence.size();
    while(temp_length){
        if(matrix_signs[i][j] == '\\'){
            --i;
            --j; 
            --temp_length;
            ++lcs_lenght;
        }
        else{
            if(matrix_signs[i][j] == '^') 
                --i;
            else 
                --j;
        }
    }
    return lcs_lenght/first_sentence.size();
}

// int lcs_sentences(std::string first_sentence, std::string second_sentence){
//     int temp=0;
//     std::vector<std::pair<std::string, std::string>> result_sentence;
//     std::vector<std::pair<std::string, std::string>> vec_of_diffs;
//     std::stringstream first_stream(first_sentence);
//     std::stringstream second_stream(second_sentence);
//     std::string first_word, second_word, diff_sum, diff_signs;
//     while(std::getline(first_stream, first_word, ' ') && std::getline(second_stream, second_word, ' ')){
//         vec_of_diffs.push_back(create_pair_of_diff(first_word, second_word, lcs_two_strings(first_word, second_word)));
//     }
//     for(auto it: vec_of_diffs)
//         std::cout << it.first << ",    ";
//     std::cout << "\n";
//     for(auto it: vec_of_diffs)
//         std::cout << it.second << ",    ";
//     std::cout << std::endl;
//     return temp;
// }

