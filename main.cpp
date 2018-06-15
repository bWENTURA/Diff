#include "header.hpp"
#include "functions.hpp"
#include "longest_sequence.hpp"

int main(int argc, char* argv[]){
    if(argc == 3){
        std::vector<std::vector<std::pair<char, std::string>>> result_matrix;
        std::ifstream file_0, file_1;
        file_0.open(argv[1], std::ios_base::in);
        file_1.open(argv[2], std::ios_base::in);
        if(file_0 && file_1)
            result_matrix = get_sentences_from_file(file_0, file_1);
        file_0.close();
        file_1.close();
        update_differences(result_matrix);
        std::cout << "*** 1," << result_matrix[0].size() << " ***\n";
        int counter = 0;
        for(const auto &it : result_matrix[0])
            std::cout << ++counter << ". " << it.first << "  " << it.second << "\n";
        std::cout << "--- 1," << result_matrix[1].size() << " ---\n";
        counter = 0;
        for(const auto &it : result_matrix[1])
            std::cout << ++counter << ". " << it.first << "  " << it.second << "\n";
        std::cout << std::endl;
    }
    system("pause");
    return 0;
}