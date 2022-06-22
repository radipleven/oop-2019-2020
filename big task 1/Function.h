#ifndef function_header
#define function_header
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "cell.h"
#include "cellManager.h"
#include <vector>
using namespace std;

class Function  {
public:

    Function();
    int strToInt(string input);
    bool isNumber(const string& s);
    bool isInt(const string& s);
    bool isDouble(const string& s);
    bool isFormula(const string& s);
    bool isValidString(string input);
    string getAbsString(string value);
    bool doesWordContainChar(string word, char character);
    vector<string> splitBySymbol(string input, char symbol);
    string removeSpaces(string input);
    string removeTailingZeros(string input);
};
#endif
 

