#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <string>
#include "cell.h"
#include "cellManager.h"
#include "function.h"
#include "fileManager.h"

using namespace std;

bool containsCommand(string command, string input)
{
    return input.rfind(command + " ", 0) == 0;
}


int main() {


	FileManager fileManager;
	
	//fileManager.read("input.txt");
   // fileManager.getCellManager()->getCells()[42]->getInfo();
	
	
    while (true)
    {
        string input;
        string command;
        getline(cin, input);

        if (input.compare("exit") == 0)
        {
            cout << "Exiting the program..." << endl;
            break;
        }
        else if (input.compare("help") == 0)
        {
            fileManager.help();
        }
        else if (containsCommand("open", input))
        {
            if (!fileManager.isOpened())
            {
                vector<string> words = Function().splitBySymbol(input,' ');
                
                string fileName = words[1];
                fileManager.read(fileName);
            }
            else cout << "Another file is currently in use. Please close all files in order to open a new one." << endl;
        }
        else if (input.compare("save") == 0)
        {
            if (fileManager.isOpened())
            {
                fileManager.save();
            }
            else cout << "No file is currently open" << endl;
        }
        else if (containsCommand("saveas", input))
        {
            if (fileManager.isOpened()) {
                vector<string> words = Function().splitBySymbol(input,' ');
                fileManager.saveAs(words[1]);
            }
            else cout << "No file is currently open" << endl;
        }
        else if (input.compare("close") == 0)
        {
            if (fileManager.isOpened())
            {
                fileManager.close();
            }
            else cout << "No file is currently open" << endl;
        }else if ((input.compare("print") == 0) && fileManager.isOpened()) {
            fileManager.getCellManager()->print();
        }
        else if (containsCommand("edit", input) && fileManager.isOpened())
        {
            vector<string> words = Function().splitBySymbol(input,' ');
            
            if (words.size()>=4)
            {
                if (fileManager.getCellManager()->isRowValid(words[1]) && fileManager.getCellManager()->isColumnValid(words[2]))
                {
                    int row = Function().strToInt(words[1]);
                    int column = Function().strToInt(words[2]);
                    if (words[3][0] == '=')
                    {
                        string formula;
                        for (int i = 3; i <words.size(); i++)
                        {
                            formula += words[i];
                        }                       
                        fileManager.getCellManager()->edit(row, column, formula);
                    }
                    else
                    {
                        fileManager.getCellManager()->edit(row, column, words[3]);
                    }
                    
                }
                else
                {
                    cout << "Invalid row/column values" << endl;
                }
                
            }
            else
            {
                cout << "Invalid command syntax" << endl;
            }
            
        }
        else cout << "Invalid command. Type help for a list of commands." << endl;
    }   
	return 0;
}