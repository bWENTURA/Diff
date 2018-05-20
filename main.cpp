#include "header.hpp"
#include "functions.hpp"
#include "longest_sequence.hpp"

int main(int argc, char* argv[]){
    if(argc == 3){ 
        std::cout << "bleeeeee" << std::endl;
        std::ifstream file_0, file_1;
        file_0.open(argv[1], std::ios_base::in);
        file_1.open(argv[2], std::ios_base::in);
        manage_file(file_0, file_1);
    }
    system("pause");
    return 0;
}