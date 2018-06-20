#include "header.hpp"
#include "functions.hpp"
#include "longest_sequence.hpp"

//  Function which gets sentences as strings and store them in sentences_matrix,
//  then moves the data by return
std::vector<std::vector<std::pair<char, std::string>>> get_sentences_from_file(std::istream& file_0, std::istream& file_1){
    std::vector<std::vector<std::pair<char, std::string>>> sentences_matrix(2);
    // Checks if file is not eof
    while(file_0.good()){
        // Clears flag if file
        file_0.clear();
        std::string result_sentence;
        getline(file_0, result_sentence, '.');
        //  Checks if getline haven't reached eof or '.'
        if(file_0.good()){
            //  Checks if newline character is the first in std::string, then erase it
            if(result_sentence.front() == '\n')
                result_sentence.erase(result_sentence.begin(), result_sentence.begin() + 1);
            //  Replacing '\n' with whitespaces if sentence was accidentally writen in multiple lines
            std::replace(result_sentence.begin(), result_sentence.end(), '\n', ' ');
            //  Adding '.' in case because getline gets all the characters of string without the delim sign ('.' in that case)
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

//  Function creates sub_vector of single words from the whole sentence
std::vector<std::string> create_vector_subsentence(const std::string &sentence){
    std::vector<std::string> result;
    std::stringstream temp_stream;
    std::string temp;
    temp_stream.str(sentence.substr(0, sentence.size() - 1));
    while(getline(temp_stream, temp, ' '))
        result.push_back(temp);
    return result;
}

//  Function updates char flags in std::pairs of char and sentences
void update_differences(std::vector<std::vector<std::pair<char, std::string>>>& result_matrix){
  //  Creating compare matrixes which stores the vector of words of each sentence
    std::vector<std::vector<std::string>> compare_matrix_first, compare_matrix_second;
    compare_matrix_first.reserve(result_matrix[0].size());
    compare_matrix_second.reserve(result_matrix[1].size());
    for(const auto &it : result_matrix[0])
        compare_matrix_first.push_back(create_vector_subsentence(it.second));
    for(const auto &it : result_matrix[1])
        compare_matrix_second.push_back(create_vector_subsentence(it.second));
    //  Function gets longest common subsequence in whole text and updates the char flags in result_matrix
    get_lcs_whole_text(result_matrix[0], result_matrix[1]);
    //  Loop which checks sentences, between these included in lcs, if they can be marked as 'c' (changed) nor deleted nor added
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
        //  If there is space, search for changed sentences
        float calculated_lcs_length = 0;
        std::vector<std::pair<char, std::string>>::iterator it_result_second;
        for(std::vector<std::pair<char, std::string>>::iterator temp_it = it_result_second_start; temp_it != result_matrix[1].end() && temp_it->first != ' '; ++temp_it){
            float temp_length = calculate_lcs_sentences(compare_matrix_first[it_result_first - result_matrix[0].begin()], compare_matrix_second[temp_it - result_matrix[1].begin()]);
            if(temp_length >= 0.5 && temp_length >= calculated_lcs_length){
                calculated_lcs_length = temp_length;
                it_result_second = temp_it;
            }
        }
        //  If calculated_lcs_length of two sentences is big enough, mark as changed
        if(calculated_lcs_length >= 0.5){
            it_result_first->first = 'c';
            it_result_second->first = 'c';
            it_result_second_start = it_result_second + 1;
        }
    }
}
