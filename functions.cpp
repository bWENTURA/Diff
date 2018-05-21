#include "header.hpp"
#include "longest_sequence.hpp"
#include "functions.hpp"

void manage_file(std::istream& file_0, std::istream& file_1){
    std::string first_line, second_line;
    std::vector<std::pair<std::string, std::string>> results_lines;
    while(std::getline(file_0, first_line) && std::getline(file_1, second_line)){
        results_lines = lcs_sentences(first_line, second_line);
    }
}




