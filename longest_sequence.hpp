#ifndef LONGEST_SEQUENCE_HPP
#define LONGEST_SEQUENCE_HPP

//  Function calculating lcs _length of sentences to see if they can be marked as changed
float calculate_lcs_sentences(const std::vector<std::string>& first_sentence, const std::vector<std::string>& second_sentence);

//  Function which mark unchanged sentences in whole text
void get_lcs_whole_text(std::vector<std::pair<char, std::string>>& first_block, std::vector<std::pair<char, std::string>>& second_block);

#endif
