//Caesar Cipher Breaker
//Mary-Paule Monks

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;


struct alphaCount
{
    char letter;
    int count;
};

struct dynamicArray
{
    int size;
    int capacity;
    alphaCount* array;
    int indexOfLargest;
    
    dynamicArray();
    ~dynamicArray();
    
    void expand();
    void add(char c);
};

string encoder();

int main(){

    ifstream infile {"ciphered_text.txt"};
 
    string toDecode {istreambuf_iterator<char>(infile), istreambuf_iterator<char>()};
    dynamicArray storage;

    //iterating over the entire passage
    for(char &c : toDecode){
       
        int exist = -1;

        //checking to see if it already exists
        for(int i = 0; i < storage.size -1; i++){
            if(storage.array[i].letter == c){
                exist = i;
            }
        }

        //if it already exist
        if(exist != -1){
            storage.array[exist].count ++;
          
            if(storage.array[exist].count > 
                                storage.array[storage.indexOfLargest].count){
              storage.indexOfLargest = exist;
            }
        }
        //if it doens't already exist
        else{
            storage.add(c);
        }
        
    }  

    //figuring out the shift
    char mostFrequent = storage.array[storage.indexOfLargest].letter;
    int shift = mostFrequent - ' ';

    //fixing based on the shift
    string fixed;
    for( char& c : toDecode){
        fixed += (c - shift);
    }

    cout << "Decoded passage:" << endl;
    cout << fixed << endl;

  return 0;
}


dynamicArray::dynamicArray(){
    array = new alphaCount[0];
    size = 0;
    capacity = 0;
    indexOfLargest = 0;
}

dynamicArray::~dynamicArray(){
    delete[] array;
}

void dynamicArray::expand(){
    (capacity == 0) ? capacity = 2 : capacity = size * 2;

    alphaCount* tempRay = new alphaCount[capacity];
    for(int i = 0; i < size; i++){
        tempRay[i] = array[i];
    }

    delete[] array;
    array = tempRay;
}

void dynamicArray::add(char c){

    if(size == capacity){
      expand();
    }

    alphaCount toAdd;
    toAdd.letter = c;
    toAdd.count = 1;

    array[size] = toAdd;
    size ++;

}
