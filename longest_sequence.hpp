#ifndef LONGEST_SEQUENCE_HPP
#define LONGEST_SEQUENCE_HPP

std::pair<std::string, std::string> create_pair_of_diff(std::string first_word, std::string second_word, std::string result_word);

float calculate_lcs_sentences(const std::vector<std::string>& first_sentence, const std::vector<std::string>& second_sentence);

void get_lcs_whole_text(std::vector<std::pair<char, std::string>>& first_block, std::vector<std::pair<char, std::string>>& second_block);

#endif
