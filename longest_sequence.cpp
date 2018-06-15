#include "header.hpp"
#include "functions.hpp"
#include "longest_sequence.hpp"

template <typename T>
std::vector<std::vector<T>> create_matrix(int height, int width){
    std::vector<std::vector<T>> matrix(height + 1);
    for(int i = 0; i <= height; ++i){
        std::vector<T> array(width + 1, 0);
        matrix[i] = array;
    }
    return matrix;
}

std::pair<std::string, std::string> create_pair_of_diff(std::string first_word, std::string second_word, std::string result_word){
    std::string diff_sum, diff_signs;
    diff_sum.reserve(2*(first_word.size() + second_word.size() - result_word.size()));
    diff_signs.reserve(2*(first_word.size() + second_word.size() - result_word.size()));
    unsigned int l = 0, k = 0, j = 0;
    for(unsigned int i = 0; i < first_word.size() + second_word.size() - result_word.size(); ++i){
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

float calculate_lcs_sentences(const std::vector<std::string>& first_sentence, const std::vector<std::string>& second_sentence){
    float lcs_lenght = 0;
    std::vector<std::vector<int>> matrix_values = create_matrix<int>(first_sentence.size() + 1, second_sentence.size() + 1);
    std::vector<std::vector<char>> matrix_signs = create_matrix<char>(first_sentence.size(), second_sentence.size());
    for(unsigned int i = 1; i <= first_sentence.size(); ++i){
        for(unsigned int j = 1; j <= second_sentence.size(); ++j){
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

void get_lcs_whole_text(std::vector<std::pair<char, std::string>>& first_block, std::vector<std::pair<char, std::string>>& second_block){
    std::vector<std::vector<int>> matrix_values = create_matrix<int>(first_block.size() + 1, second_block.size() + 1);
    std::vector<std::vector<char>> matrix_signs = create_matrix<char>(first_block.size(), second_block.size());
    for(unsigned int i = 1; i <= first_block.size(); ++i){
        for(unsigned int j = 1; j <= second_block.size(); ++j){
            if(first_block[i - 1].second == second_block[j - 1].second){
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
    int temp_length = matrix_values[first_block.size()][second_block.size()];
    int i = first_block.size(), j = second_block.size();
    while(temp_length){
        if(matrix_signs[i][j] == '\\'){
            --i;
            --j;
            --temp_length;
            first_block[i].first = ' ';
            second_block[j].first = ' ';
        }
        else{
            if(matrix_signs[i][j] == '^')
                --i;
            else
                --j;
        }
    }
}
