#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <fstream>
using namespace std;
//represents the Huffman tree node
class T_node{
public:
    char ch;
    int freq;
    T_node* right;
    T_node* left;
    T_node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};
//compares T_node elements for min priority queue
class Compare{
public:
    bool operator()(T_node* a, T_node* b){
        return a->freq > b->freq;              //comparison needed to determine the less frequent symbol
    }
};
/*assign_Huffman_codes
parameters: 
-r: root of Huffman tree, 
-str: empty string to add 0 and/or 1
-h_code: unordered map <char,string> for each symbol and its binary code equivalent
function:
-starting from the root node, recursively assign:
0 -> left branches
1 -> right branches*/
void assign_Huffman_codes(T_node* r, string str, unordered_map<char,string>& h_code){
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
-prints the resulting encoded string*/
void print_encoded_res(const string f_name, unordered_map<char,string>& h_code){
    std::ifstream ifs;
    ifs.open(f_name,std::ifstream::in);
    if (!ifs.is_open()) {
        cerr << "Unable to open file: " << f_name << '\n';
        return;
    }
    string encoded_text = "";
    char c ;
    while (ifs.get(c)){
        encoded_text += h_code[c];
    }
    cout << "Encoded text:\n" << encoded_text << '\n';
}
/*free_tree
-r: root of Huffman tree
function:
-deallocate memory used by the Huffman tree*/
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
/*create_Huffman_Tree
parameters:
-f_map: input unordered map of <character,frequency> pairings
-fname: name of original .txt file to be encoded
function:
-create a min priority queue(minheap) to store unordered map pairings
-while there are more than 1 elements in the queue, "remove" the first 2, highest priority nodes
 (minimum frequency) and attach them to a parent node with a combined frequency
-push the parent node
-make top of the priority queue the root of the Huffman tree
-assign Huffman codes to every branch
-print resulting string*/
void create_Huffman_Tree(const unordered_map<char,int>f_map,const string fname){
    priority_queue<T_node*,vector<T_node*>,Compare> min_pq;     //create an empty priority queue
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

        min_pq.push(parent);
    }
    T_node* root = min_pq.top();            //root of Huffman tree
    unordered_map<char,string>h_code;       //create a new map to store pairings of <character,encoding>
    assign_Huffman_codes(root, "",h_code);  //assigns Huffman codes to each character
    cout << "Huffman Codes:\n";
    for (auto i : h_code) {
        cout << i.first << " " << i.second << "\n";
    }
    print_encoded_res(fname,h_code);        //prints the result
    free_Tree(root);
}
