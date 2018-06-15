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
            sentences_matrix[0].push_back(std::make_pair('d', result_sentence));
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
    get_lcs_whole_text(result_matrix[0], result_matrix[1]);
    std::vector<std::pair<char, std::string>>::iterator it_result_second_start = result_matrix[1].begin(); 
    for(std::vector<std::pair<char, std::string>>::iterator it_result_first = result_matrix[0].begin(); it_result_first != result_matrix[0].end(); ++it_result_first){
        if(it_result_first->first == ' '){
            ++it_result_first;
            while(it_result_second_start != result_matrix[1].end() && it_result_second_start->first != ' ')
                ++it_result_second_start;
            if(it_result_second_start->first == ' ')
                ++it_result_second_start;
        }
        if(it_result_second_start == result_matrix[1].end() || it_result_first == result_matrix[0].end())
            break;
        float calculated_lcs_length = 0;
        std::vector<std::pair<char, std::string>>::iterator it_result_second;
        for(std::vector<std::pair<char, std::string>>::iterator temp_it = it_result_second_start; temp_it != result_matrix[1].end() && temp_it->first != ' '; ++temp_it){
            float temp_length = calculate_lcs_sentences(compare_matrix_first[it_result_first - result_matrix[0].begin()], compare_matrix_second[temp_it - result_matrix[1].begin()]);
            if(temp_length >= 0.5 && temp_length >= calculated_lcs_length){
                calculated_lcs_length = temp_length;
                it_result_second = temp_it;
            }
        }
        if(calculated_lcs_length >= 0.5){
            it_result_first->first = 'c';
            it_result_second->first = 'c';
            it_result_second_start = it_result_second + 1;
        }
    }

}



