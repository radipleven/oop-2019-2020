#include <stdio.h>
#include "function.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

Function::Function() {

}


int Function::strToInt(string input)
{
    //https://www.geeksforgeeks.org/converting-strings-numbers-cc/
    stringstream st(input);
    int result = 0;
    st >> result;
    return result;
}

bool Function::isNumber(const string& s)
{
    //https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
    return !s.empty() && std::find_if(s.begin(),
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

vector<string> Function::splitBySpace(string input) {
    stringstream test(input);
    string word;
    vector<string> words;

    while (getline(test, word, ' ')) words.push_back(word);

    return words;
}
