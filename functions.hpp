#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

std::vector<std::vector<std::pair<char, std::string>>> get_sentences_from_file(std::istream& file_0, std::istream& file_1);

std::vector<std::string> create_vector_subsentence(const std::string &sentence);

void update_differences(std::vector<std::vector<std::pair<char, std::string>>> &result_matrix);

#endif