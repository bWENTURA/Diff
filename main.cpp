#include "header.hpp"
#include "functions.hpp"
#include "longest_sequence.hpp"

int main(int argc, char* argv[]){
    //  Checking number of arguments
    if(argc == 3){
        //  Vector of size two which will store vectors of strings with format info from first file in result_matrix[0]
        //  and from second file in result_matrix[1]
        std::vector<std::vector<std::pair<char, std::string>>> result_matrix;
        std::ifstream file_0, file_1;
        file_0.open(argv[1], std::ios_base::in);
        file_1.open(argv[2], std::ios_base::in);
        //  Checking if files are alright
        if(file_0.is_open() && file_1.is_open()){
          // Function which gets sentences from file to vector result_matrix
          result_matrix = get_sentences_from_file(file_0, file_1);
          // Function update_differences sets char flags in std::pair to format the output of diff
          update_differences(result_matrix);
          //  Printing result
          if(result_matrix[0].size()){
              std::string temp_name = argv[1];
              std::cout <<  "**** " << temp_name << " *** 1," << result_matrix[0].size() << " ***\n";
              int counter = 0;
              for(const auto &it : result_matrix[0])
                  std::cout << ++counter << ". " << it.first << "  " << it.second << "\n";
          }
          if(result_matrix[1].size()){
              std::cout << "\n";
              std::string temp_name = argv[2];
              std::cout << "---- " << temp_name << " --- 1," << result_matrix[1].size() << " ---\n";
              int counter = 0;
              for(const auto &it : result_matrix[1])
                  std::cout << ++counter << ". " << it.first << "  " << it.second << "\n";
          }
          std::cout << "\na = added in second file || " << "d = deleted from first file || " << "c = line have some changes || " << "no sign = equal lines" << std::endl;
        }
        else
          std::cout << "Error with opening files." << std::endl;
        if(!(file_0.is_open()))
          file_0.close();
        if(!(file_1.is_open()))
          file_1.close();
    }
    else
      std::cout << "Wrong number of arguments." << std::endl;
    return 0;
}
