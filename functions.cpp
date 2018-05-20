#include "header.hpp"
#include "longest_sequence.hpp"
#include "functions.hpp"

void manage_file(std::istream& file_0, std::istream& file_1){
    std::string first_line, second_line, result;
    while(!file_0.eof() && !file_1.eof()){
        std::getline(file_0, first_line, '.');
        std::getline(file_1, second_line, '.');
        result = longest_subsequence_between_2strings(first_line, second_line);
    }
}


