#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "Function.h"
#include "cellManager.h"
#include "fileManager.h"
#include "cell.h"
using namespace std;

FileManager::FileManager()
{
}

CellManager* FileManager::getCellManager()
{
    return &cellManager;
}

void FileManager::read(string name)
{
    setFileName(name);
    cellManager.calculateTableSize(fileName);
    
    string line;
    ifstream myfile(fileName);   
    int currentId = 0;
    while (getline(myfile, line))//za vseki red
    {
       //cout << line << endl;        
        // tuk celta e da vzemem vseki red kato string i spored zapetaite da pulnim kletkite  |
        // kato value shte se promenq na vsqko zavurtane i shte otiva v cell.setValue(value)  \/
       
        vector<string> valuesOnRow;
        stringstream test(line);
        string word;
        if (line.length() == 0)
        {
            for (size_t i = 0; i < cellManager.getNumberOfColumns(); i++)
            {
                valuesOnRow.push_back("empty value");
            }
        }
        else
        {

            int numberOfCommas = count(line.begin(), line.end(), ',') +1;
            int extraCommas = cellManager.getNumberOfColumns() - numberOfCommas;
            
            for (int i = 0; i < extraCommas; i++)
            {
                //valuesOnRow.push_back("empty");
                line += ",empty value";
            }
            valuesOnRow = Function().splitBySymbol(line,',');

            
        }
        for (int i = 0; i < valuesOnRow.size(); i++)
        {
            if (valuesOnRow[i]=="")
            {
                valuesOnRow[i] = "empty value";
            }
            Cell* cell = new Cell(currentId+1,0,0,valuesOnRow[i],"");
            cell->setFileValue(valuesOnRow[i]);
            cellManager.addCell(cell);
            currentId++;
           
        }
        
    }
    
    

    if (cellManager.setCellDataTypes())
    {
        for (int i = 0; i <cellManager.getCells().size(); i++)
        {
            if (cellManager.getCells()[i]->getDataType() == "formula")
            {

                cellManager.applyFormula(cellManager.getCells()[i]->getId());
            }
            cellManager.getCells()[i]->setColumn(i% cellManager.getNumberOfColumns());
            cellManager.getCells()[i]->setRow(i/cellManager.getNumberOfColumns());
            
        }
        cout << "Successfully opened " << fileName << endl;
        
    }
    else
    {
        cout << "Invalid configuration file" << endl;
        close();
    }
}

void FileManager::save()
{
    saveAs(fileName);
}

void FileManager::saveAs(string name)
{
    fstream fs(name, ios::out | ios::binary);

    for (int r = 0; r < cellManager.getNumberOfRows(); r++) {
        
        for (int c = 0; c < cellManager.getNumberOfColumns(); c++)
        {
            int id = r * cellManager.getNumberOfColumns() + c + 1;
            string config = cellManager.getCellNyId(id)->getValue();
            if (cellManager.getCellNyId(id)->getDataType()=="string")
            {
                config = cellManager.getCellNyId(id)->getFileValue();

            }
            int size = config.size();

            char* output = new char[size + 1];
            strcpy(output, config.c_str());
            
            fs.write(output, size);
            
            if (c<cellManager.getNumberOfColumns()-1)
            {
                fs.write(",", 1);
            }

            delete[]output;
        }
        if (r<cellManager.getNumberOfRows()-1)
        {
            fs.write("\n", 1);
        }
    }

   
    fs.close();

    cout << "Succesfully saved " << name << endl;
}

string FileManager::getFileName()
{
    return fileName;
}

void FileManager::setFileName(string name)
{
    fileName = name;
}

void FileManager::help()
{
    cout << "The following commands are supported:" << endl;
    cout << "open <file>        opens <file>" << endl;
    cout << "close                closes currently opened file" << endl;
    cout << "save                saves the currently open file" << endl;
    cout << "saveas <file>        saves the currently open file in <file>" << endl;
    cout << "help                prints this information" << endl;
    cout << "exit                exists the program" << endl;
}

bool FileManager::isOpened()
{
    return fileName.compare("") != 0;

}

void FileManager::close()
{
    setFileName("");
    cellManager.clearTable();
    cout << "Closed." << endl;

}
