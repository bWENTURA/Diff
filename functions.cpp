#include "header.hpp"
#include "longest_sequence.hpp"
#include "functions.hpp"

std::vector<std::vector<std::pair<char, std::string>>> get_sentences_from_file(std::istream& file_0, std::istream& file_1){
    std::vector<std::vector<std::pair<char, std::string>>> sentences_matrix(2);
    while(file_0.good()){
        file_0.clear();
        std::string result_sentence;
        getline(file_0, result_sentence, '.');
        if(file_0.good()){
            if(result_sentence.front() == '\n')
                result_sentence.erase(result_sentence.begin(), result_sentence.begin() + 1);
            std::replace(result_sentence.begin(), result_sentence.end(), '\n', ' ');
            result_sentence += '.';
            sentences_matrix[0].push_back(std::make_pair('-', result_sentence));
        }
    }
     while(file_1.good()){
        file_1.clear();
        std::string result_sentence;
        getline(file_1, result_sentence, '.');
        if(file_1.good()){
            if(result_sentence.front() == '\n')
                result_sentence.erase(result_sentence.begin(), result_sentence.begin() + 1);
            std::replace(result_sentence.begin(), result_sentence.end(), '\n', ' ');
            result_sentence += '.';
            sentences_matrix[1].push_back(std::make_pair('a', result_sentence));
        }
    }
    return sentences_matrix;
}

std::vector<std::string> create_vector_subsentence(const std::string &sentence){
    std::vector<std::string> result;
    std::stringstream temp_stream;
    std::string temp;
    temp_stream.str(sentence.substr(0, sentence.size() - 1));
    while(getline(temp_stream, temp, ' '))
        result.push_back(temp);
    return result;
}

void update_differences(std::vector<std::vector<std::pair<char, std::string>>>& result_matrix){
    std::pair<int, float> max_lcs_index = std::make_pair(-1, 0.5);
    std::vector<std::vector<std::string>> compare_matrix_first, compare_matrix_second;
    compare_matrix_first.reserve(result_matrix[0].size());
    compare_matrix_second.reserve(result_matrix[1].size());
    for(const auto &it : result_matrix[0])
        compare_matrix_first.push_back(create_vector_subsentence(it.second));
    for(const auto &it : result_matrix[1])
        compare_matrix_second.push_back(create_vector_subsentence(it.second));
    // for(const auto& it : compare_matrix_first){
    //     for(const auto &sec_it : it)
    //         std::cout << sec_it;
    //     std::cout << "\n";
    // }
    //  for(const auto& it : compare_matrix_second){
    //     for(const auto &sec_it : it)
    //         std::cout << sec_it;
    //     std::cout << "\n";
    // }
    std::vector<std::pair<char, std::string>>::iterator it_result_second_start = result_matrix[1].begin(); 
    for(std::vector<std::pair<char, std::string>>::iterator it_result_first = result_matrix[0].begin(); it_result_first != result_matrix[0].end(); ++it_result_first){
        float calculated_lcs_length = 0;
        std::vector<std::pair<char, std::string>>::iterator it_result_second = it_result_second_start, temp_iterator;
        while(it_result_second != result_matrix[1].end()){
            if(it_result_first->second == it_result_second->second){
                if(it_result_second != result_matrix[1].begin()){
                    for(std::vector<std::pair<char, std::string>>::iterator temp_it = result_matrix[1].begin(); temp_it != it_result_second; ++temp_it)
                        temp_it->first = 'a';
                }
                it_result_second->first = ' ';
                it_result_second_start = it_result_second + 1;
                break;
            }
            else{
                float temp_length = calculate_lcs_sentences(compare_matrix_first[it_result_first - result_matrix[0].begin()], compare_matrix_second[it_result_second - result_matrix[1].begin()]);
                if(temp_length >= 0.5 && temp_length >= calculated_lcs_length){
                    calculated_lcs_length = temp_length;
                    temp_iterator = it_result_second;
                }
            }
            ++it_result_second;
        }
        if(it_result_second == result_matrix[1].end()){
            if(calculated_lcs_length < 0.5)
                it_result_first->first = '-';
            else{
                it_result_first->first = 'c';
                temp_iterator->first = 'c';
                it_result_second_start = temp_iterator + 1;
            }
            max_lcs_index.first = -1;
            max_lcs_index.second = 0.5;
        }
    }
    for(; it_result_second_start != result_matrix[1].end(); ++it_result_second_start)
        it_result_second_start->first = 'a';

}



