#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>

//represents the Huffman tree node
class T_node{
public:
    char ch;
    int freq;
    T_node* left;
    T_node* right;
    T_node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

/*print_encoded_res
@param f_name: name of the original .txt file
@param h_code: resulting unordered map after the code assignments to each character
function:prints the resulting encoded string
@return encoded string*/
std::string print_encoded_res(const std::string f_name, std::unordered_map<char,std::string>& h_code);
/*free_tree
@param r: root of Huffman tree
function: deallocate memory used by the Huffman tree*/
void free_Tree(T_node* r);
/*create_Huffman_Tree
@param f_map: input unordered map of <character,frequency> pairings
function: create huffman tree from frequency map
@return the final tree*/
T_node* create_Huffman_Tree(const std::unordered_map<char,int>f_map);
/*create_encoding_map
@param T_node* root: root of the Huffman tree
function: create an unordered map of <char,string> pairings
@return the unordered_map */
std::unordered_map<char,std::string> create_encoding_map(T_node* root);
/*freq_finder
@param f_name : a txt file name as input
function: reads the file and fills a map with every character and its frequency
@return an unordered map of <char,int> pairings*/
std::pair<std::unordered_map<char,int>,int> freq_finder(const std::string f_name);
/*decode_text
@param T_node* root : the root of the huffman tree
@param c_str : the encoded string from previous function
function: parses the binary string and uses the huffman tree as a lexicon to determine
the corresponding character
@return the decoded text*/
std::string decode_text(T_node* root, const std::string& c_str);