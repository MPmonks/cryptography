//Mary-Paule Monks
//Caesar Cipher encoder

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main(){
    
    srand(time(NULL));
    int shift = rand() % 26;

    ifstream infile {"tester-text.txt"};
 
    string text {istreambuf_iterator<char>(infile), istreambuf_iterator<char>()};
   
    string jumbled;

    for (char &c : text){
        
        jumbled += (c + shift);
    }

    fstream outfile { "ciphered_text.txt"};
    
    outfile << jumbled;

    return 0;
}