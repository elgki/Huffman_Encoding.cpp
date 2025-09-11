#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <fstream>
#include "huffman.hpp"

//compares T_node elements for min priority queue
class Compare{
public:
    bool operator()(T_node* a, T_node* b){
        return a->freq > b->freq;              //comparison needed to determine the less frequent symbol
    }
};
/*starting from the root node, recursively assign:
0 -> left branches
1 -> right branches*/
void assign_Huffman_codes(T_node* r, std::string str, std::unordered_map<char,std::string>& h_code){
    if(r == nullptr){                       //check if tree is empty
        return;
    }
    if (!r->left && !r->right) {            //check if the node is a leaf node
        h_code[r->ch] = str;
    }
    assign_Huffman_codes(r->left, str + "0",h_code);
    assign_Huffman_codes(r->right, str + "1",h_code);
}
/*print_encoded_res
parameters:
-f_name: name of the original .txt file
-h_code: resulting unordered map after the code assignments to each character
function:
-prints the resulting encoded string
-returns the resulting string*/
std::string print_encoded_res(const std::string f_name, std::unordered_map<char,std::string>& h_code){
    std::ifstream ifs;
    ifs.open(f_name,std::ifstream::in);
    if (!ifs.is_open()) {
        std::cerr << "Unable to open file: " << f_name << '\n';
    }
    std::string encoded_text = "";
    char c ;
    while (ifs.get(c)){
        encoded_text += h_code[c];
    }
    std::cout << "Encoded text:\n" << encoded_text << '\n';
    return encoded_text;
}
/*free Huffman tree*/
void free_Tree(T_node* r){
    if(r!=nullptr){
        free_Tree(r->left);
        free_Tree(r->right);
        delete r;
    }
    else{
        return;
    }
}
/*-create a min priority queue(minheap) to store unordered map pairings
-while there are more than 1 elements in the queue, "remove" the first 2, highest priority nodes
 (minimum frequency) and attach them to a parent node with a combined frequency
-make top of the priority queue the root of the Huffman tree
-returns the root node*/
T_node* create_Huffman_Tree(const std::unordered_map<char,int>f_map){
    std::priority_queue<T_node*,std::vector<T_node*>,Compare> min_pq;     //create an empty priority queue
    for (auto p : f_map){                                       //insert each pair from the map in the queue
        min_pq.push(new T_node(p.first, p.second));
    }
    while (min_pq.size()>1){
        T_node* left = min_pq.top();
        min_pq.pop();
        T_node* right = min_pq.top();
        min_pq.pop();

        T_node* parent = new T_node('$', left->freq + right->freq); //create internal parent node with the previous two nodes as children
        parent->left = left;
        parent->right = right;

        min_pq.push(parent);                        //push parent node
    }
    T_node* root = min_pq.top();                   //root of Huffman tree
    return root;
}
/*-create an unordered map of <char,string> pairings,
demonstrating the symbol-binary code mappings
-assigns huffman codes
-returns the unordered_map */
std::unordered_map<char,std::string> create_encoding_map(T_node* root){
    std::unordered_map<char,std::string>h_code;       //create a new map to store pairings of <character,encoding>
    assign_Huffman_codes(root, "",h_code);  //assigns Huffman codes to each character
    std::cout << "Huffman Codes:\n";
    for (auto i : h_code) {
        std::cout << i.first << " " << i.second << "\n";
    }
    return h_code;
}
/*decodes the encoded string and returns the result*/
std::string decode_text(T_node* root, const std::string& c_str){
    std::string decoded_str;
    T_node* curr = root;
    for(char c : c_str){
        if (c == '0'){
            curr = curr->left;
        }
        else{
            curr =  curr->right;
        }
        if(!curr->left && !curr->right){
            decoded_str.push_back(curr->ch);
            curr = root;

        }
    }
    return decoded_str;
}