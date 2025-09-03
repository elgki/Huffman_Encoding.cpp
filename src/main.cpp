#include <iostream>
#include <string>
#include <vector>
#include "freq_finder.cpp"
#include "tree_builder.cpp"
using namespace std;

//main function
int main(){
    cout<<"Enter the name of a file to read: ";
    string fname;
    int c_count;                                //initialize unique character counter
    unordered_map<char,int>frequencies;         //initialize a map to fill
    cin >> fname;
    auto result = freq_finder(fname);           //freq_finder function call
    if (result.first.empty()){
        cout << "File not found or empty\n";
    }
    else{
        frequencies = result.first;
        c_count = result.second;
        create_Huffman_Tree(frequencies,fname);
    }
    return 0;
}

