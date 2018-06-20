#include "header.hpp"
#include "longest_sequence.hpp"

//  Template function which creates vector of vectors of different type
template <typename T>
std::vector<std::vector<T>> create_matrix(int height, int width){
    std::vector<std::vector<T>> matrix(height + 1);
    for(int i = 0; i <= height; ++i){
        std::vector<T> array(width + 1, 0);
        matrix[i] = array;
    }
    return matrix;
}

//  Function calculating lcs _length of sentences to see if they can be marked as changed
float calculate_lcs_sentences(const std::vector<std::string>& first_sentence, const std::vector<std::string>& second_sentence){
    std::vector<std::vector<int>> matrix_values = create_matrix<int>(first_sentence.size() + 1, second_sentence.size() + 1);
    for(unsigned int i = 1; i <= first_sentence.size(); ++i){
        for(unsigned int j = 1; j <= second_sentence.size(); ++j){
            if(first_sentence[i - 1] == second_sentence[j - 1])
                matrix_values[i][j] = matrix_values[i - 1][j - 1] + 1;
            else{
                if(matrix_values[i - 1][j] >= matrix_values[i][j - 1])
                    matrix_values[i][j] = matrix_values[i - 1][j];
                else
                    matrix_values[i][j] = matrix_values[i][j - 1];
            }
        }
    }
    float lcs_lenght = matrix_values[first_sentence.size()][second_sentence.size()];
    return lcs_lenght/first_sentence.size();
}

//  Function which mark unchanged sentences in whole text
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
