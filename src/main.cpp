#include <iostream>
#include <string>
#include <unordered_map>
#include "huffman.hpp"


//main function
int main(){
    std::cout<<"Enter the name of a file to read: ";
    std::string fname, encoded_str, decoded_str;
    //int c_count;                                        //initialize unique character counter
    std::unordered_map<char,int>frequencies;            //initialize a map to fill with the frequencies
    std::unordered_map<char,std::string>code_map;    //initialize a map to fill with the codes
    std::cin >> fname;
    auto result = freq_finder(fname);                   //freq_finder function call
    if (result.first.empty()){
        std::cout << "File not found or empty\n";
    }
    else{
        frequencies = result.first;
        //c_count = result.second;
        auto root = create_Huffman_Tree(frequencies);
        code_map = create_encoding_map(root);
        encoded_str = print_encoded_res(fname,code_map);
        decoded_str = decode_text(root,encoded_str);
        std::cout << "This is the original text: "<< decoded_str << "\n";
        free_Tree(root);
    }
    return 0;
}

