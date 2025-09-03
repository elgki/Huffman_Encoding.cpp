#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
using namespace std;


/*freq_finder function:
receives a txt file name as input
reads the file and fills a map 
with every character and its frequency*/
pair<unordered_map<char,int>,int> freq_finder(string f_name){
    unordered_map<char,int>char_freq;
    int char_count = 0;
    std::ifstream ifs;
    ifs.open(f_name,std::ifstream::in);
    if (!ifs.is_open()) {
        cerr << "Unable to open file: " << f_name << '\n';
        return {char_freq, 0};
    }
    char c = ifs.get();
    while (ifs.good()){
        ++char_freq[c];
        c = ifs.get();
    }
    char_count = char_freq.size();
    ifs.close();
    return {char_freq,char_count};
}
/*print_result function:
receives a map of <character,frequency> pairings
and the sum of unique characters and prints them on the screen*/
void print_result(unordered_map<char,int>f_map,int c){
    cout << '\n' << "These are the frequencies of each character:" <<'\n';
    for(auto i = f_map.begin();i!=f_map.end();i++){
        cout << i->first << ":" << i->second<<'\n';             //print every pair <char,int>
    }
    cout << "This is the sum of unique characters detected: " << c << '\n';
}




