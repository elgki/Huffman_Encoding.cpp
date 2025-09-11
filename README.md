# Huffman Encoding and Decoding

This is a C++ implementation of Huffman encoding, a compression algorithm that assigns variable-length binary codes to characters based on their frequencies (high frequency-> shorter codes,low frequency-> longer codes)

## Features
- Reads a text file and builds a frequency map.
- Constructs a Huffman tree using a min-priority queue.
- Encodes text into a binary string.
- Decodes the encoded string back into the original text.
- Memory cleanup with `free_tree`.

## How to run
(in VS Code)
-make sure you are in the src directory
-from the terminal run this: g++ -std=c++17 -Wall -Wextra -g *.cpp -o huffman.exe
-run with: ./huffman.exe
-the program sees the .txt files that are inside src, so you can tweak Small_test.txt or create 
your own .txt and add it to src

## Project Structure
-huffman.hpp : library with function declarations and the class declaration as the tree structure is used across files
-frequency_finder.cpp : opens a .txt file and creates an unordered_map with the characters and their frequencies
-encoding.cpp : Using the previous frequency map, it creates a huffman tree and assigns the binary codes, also has a decoding function
-main.cpp : combines function calls from the above .cpp files to implement the complete encoding-decoding procedure
-Small_test.txt : test file

Huffman_Encoding/
├── src/
│ ├── main.cpp
│ ├── freq_finder.cpp
│ ├── encoding.cpp
│ ├── decoding.cpp
│ └── huffman.hpp
├── .gitignore
└── README.md
## Expected output 

Huffman Codes:
i 1111
f 11101
c 11100
r 000
e 011
o 00100
T 00101
a 1010
  110
l 00111
t 010
p 1000
x 10010
. 00110
h 10011
s 1011
Encoded text:
0010110011111110111101111101111010101101000000101011100010111111100011110010011100100101101110111110011101111011101001000001100101001101111010001010000101101100000110
This is the original text: This is a practice text file for the parser.