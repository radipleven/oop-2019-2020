#include <stdio.h>
#include "function.h"
#include "cell.h"
#include "cellManager.h"
#include <iostream>
#include <algorithm>
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




vector<string> Function::splitBySymbol(string input,char symbol) {
    stringstream test(input);
    string word;
    vector<string> words;

    while (getline(test, word, symbol)) words.push_back(word);

    return words;
}

bool Function::isInt(const string& s)
{
    //https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int/37864920
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;

    char* p;
    strtol(s.c_str(), &p, 10);

    return (*p == 0);

}

bool Function::isDouble(const string& s)
{
    //https://stackoverflow.com/questions/29169153/how-do-i-verify-a-string-is-valid-double-even-if-it-has-a-point-in-it
    if (!isInt(s)) {


        char* end = nullptr;
        double val = strtod(s.c_str(), &end);
        return end != s.c_str() && *end == '\0' && val != HUGE_VAL;
    }
    return false;
}

bool Function::isFormula(const string& s)
{
    if (s[0] == '=')
    {
        return 1;
    }
    else return 0;
}

bool Function::doesWordContainChar(string word, char character)
{
    if (word.find(character) != std::string::npos)
    {
        return 1;
    }
    else return 0;
    
    
}

string Function::removeSpaces(string input)
{
    string::iterator end_pos = remove(input.begin(), input.end(), ' ');
    input.erase(end_pos, input.end());

    return input;
}
bool Function::isValidString(string value)
{
    int quotesCount = 0;
    for (int i = 0; i < value.size(); i++)
    {
        char currentChar = value[i];
        char nextChar = i < value.size() - 1 ? value[i + 1] : 'a';
        char previousChar = i > 0 ? value[i - 1] : 'a';

        if (currentChar == '\\')
        {
            if (nextChar == '\\')
            {
                i++;
                continue;
            }

            if (nextChar != '\"')
            {
                return false;
            }
            else
            {
                quotesCount--;
            }
        }
        if (currentChar == '\"' )
        {
            quotesCount++;

        }
    }

    if (quotesCount % 2 != 0 || quotesCount == 0)
    {
        return false;
    }
    else
    {
        return true;
    }


}

string Function::getAbsString(string word)
{
    string value = "";
    for (int i = 0; i < word.size(); i++)
    {
        char currentChar = word[i];
        char nextChar = i < word.size() - 1 ? word[i + 1] : 'a';
        

        if (currentChar == '\\')
        {
            if (nextChar == '\\')
            {
                i++;
                value += currentChar;
                continue;
            }

            if (nextChar == '\"')
            {
                value += '\"';
            }
           
        }else if (currentChar != '\"')
        {
            value += currentChar;

        }
    }
    return value;
    
}

string Function::removeTailingZeros(string value)
{
    string newValue;
    int zeros = 0;

    for (int i = value.size()-1; i >0 ; i--)//25.50000  25.50055500
    {
        char currentChar = value[i];
        
        if (currentChar != '0')
        {
            break;
        }
        char previousChar = i > 1 ? value[i - 1] : 'a';
        if (currentChar=='0' && previousChar!='.')
        {
            zeros++;
        }
    }

    int addLast = value[value.size() - zeros-1] =='0'&& value[value.size() - zeros-2]=='.'?2:0;
    
    for (int i = 0; i < value.size()-zeros-addLast; i++)
    {
        newValue += value[i];
    }
    return newValue;
}