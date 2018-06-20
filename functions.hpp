#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

//  Function which gets sentences as strings and store them in sentences_matrix,
//  then moves the data by return
std::vector<std::vector<std::pair<char, std::string>>> get_sentences_from_file(std::istream& file_0, std::istream& file_1);

//  Function creates sub_vector of single words from the whole sentence
std::vector<std::string> create_vector_subsentence(const std::string &sentence);

//  Function updates char flags in std::pairs of char and sentences
void update_differences(std::vector<std::vector<std::pair<char, std::string>>> &result_matrix);

#endif
