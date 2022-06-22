#include <iostream>
#include <vector>
#include <math.h>
#include <sstream>
#include <fstream>
#include <string>
#include "cell.h"
#include "cellManager.h"
#include "function.h"

CellManager::CellManager()
{

}

void CellManager::calculateTableSize(string fileName)
{
    //https://stackoverflow.com/questions/3482064/counting-the-number-of-lines-in-a-text-file
    //https://stackoverflow.com/questions/7868936/read-file-line-by-line-using-ifstream-in-c
    string line;
    ifstream myfile(fileName);
    int columns = 0;
    int currentCell = 0;
    int number_of_lines = 0;

    while (getline(myfile, line))//za vseki red
    {
        //cout << line << endl;
        number_of_lines++;
        size_t n = count(line.begin(), line.end(), ',');
        if (n > columns)
        {
            columns = n;
        }
    }
    setRows(number_of_lines);
    setColumns(columns + 1);
    
}

int CellManager::getNumberOfRows()
{
    return rows;
}

void CellManager::setRows(int rows)
{
    this->rows = rows;
}

int CellManager::getNumberOfColumns()
{
    return columns;
}

void CellManager::setColumns(int columns)
{
    this->columns=columns;
}

vector<Cell*> CellManager::getCells()
{
    return cells;
}

void CellManager::setAdressesOfCells()
{    
    int currentCell = 0;
    //setCellIds();
    for (int i = 1; i <= getNumberOfRows(); i++)
    {
        for (int j = 1; j <= getNumberOfColumns(); j++)
        {
            cells.push_back(&Cell(currentCell+1, i, j, "", ""));
            currentCell++;
        }
    }
}

void CellManager::clearTable()
{
    rows = 0;
    columns = 0;
    cells.clear();
}

void CellManager::addCell(Cell* cell)
{

    cells.push_back(cell);
}

bool CellManager::setCellDataTypes()// asdasdasdasd
{
    for (int i = 0; i < cells.size(); i++)
    {
       if (!cells[i]->isValueValid())
       {
             return false;
       } 
    }
    return true;
}

Cell* CellManager::getCellNyId(int cellId)
{
    for (int i = 0; i < cells.size(); i++)
    {
        int id = cells[i]->getId();
        
        if (id == cellId)
        {
            return cells[i];
        }
    }


    return &Cell();
}

int CellManager::getMaxColWidth(int columnId)
{
    int maxWidth = 1;

    for (int i = 0; i < getNumberOfRows(); i++)
    {
        int id = (getNumberOfColumns() ) * i + columnId + 1;
        //Cell* cell = getCellNyId(id);
        
        string value = getCellNyId(id)->getValue();
       
        if (value=="empty value")
        {
            value = "";
        }
        int valueLength = value.length();
        if (valueLength>maxWidth)
        {
            maxWidth = valueLength;
        }

       // cout << "value: "<<value <<" "<<"legth: "<< value.length() << endl;
    }
    
    return maxWidth;
}

void CellManager::print()
{
    for (int r = 0; r < rows; r++)//row
    {
        cout << "|";
        for (int c = 0; c < columns; c++)//column
        {
            int maxWidth = getMaxColWidth(c);
            int cellId = r * getNumberOfColumns() + c + 1;
            //Cell* cell = getCellNyId(cellId);
            
            string value = getCellNyId(cellId)->getValue();
            if (value=="empty value" || value=="empty")
            {
                value = "";
            }
            
            int valueLength = value.length();
            int extraSpace = maxWidth - valueLength;         
            for (int i = 0; i < extraSpace; i++)
            {
                cout << " ";
            }
            cout << value + "|";
           // cout << "id " << cellId << endl;
        }
        
        cout << endl;
        
    }

  
   
}

void CellManager::edit(int row, int column, string value)
{
    row--;
    column--;
    int cellId = row * getNumberOfColumns() + column + 1;
    Cell* cell = getCellNyId(cellId);
    string previousValue = cell->getValue();
    string previousFileValue = cell->getFileValue();
    string previousDataType = cell->getDataType();
    cell->setValue(value);
    if (previousDataType=="string")
    {
        cell->setFileValue(value);
    }
    bool isFormula = Function().isFormula(value);//ako cella ne e valid go resetvame kum previous steita mu
    if (!cell->isValueValid())
    {
        cell->setFileValue(previousFileValue);
        cell->setValue(previousValue);
        cell->setDataType(previousDataType);
        cout << "Wrong value format. No changes were made" << endl;
    }
    else
    {
        if (cell->getDataType()=="formula")

        {
            cell->setFileValue(value);
            applyFormula(cellId);
        }
        cout << "Value succesfully updated" << endl;
    }
}

bool CellManager::isRowValid(string rowString)
{
    
    if (rowString[0] !='-')
    {
        if (Function().isInt(rowString))
        {
            int rowInt=Function().strToInt(rowString);
            if (rowInt<=rows && rowInt>0)
            {
                return true;
            }
        }
    }
    return false;
}

bool CellManager::isColumnValid(string columnString)
{
    if (columnString[0] != '-')
    {
        if (Function().isInt(columnString))
        {
            int columnInt = Function().strToInt(columnString);
            if (columnInt <= columns && columnInt > 0)
            {
                return true;
            }
        }
    }
    return false;
}

Cell* CellManager::getCellByAdress(string adress)
{    
    //RxCy
    string newAdress;
    for (int i = 1; i < adress.size(); i++)
    {
        newAdress += adress[i];
    }
    vector<string> words = Function().splitBySymbol(newAdress,'C');
    if (words.size()==2)
    {
        if (isRowValid(words[0]) && isColumnValid(words[1]))
        {
            int row = Function().strToInt(words[0]);
            int column = Function().strToInt(words[1]);
            row--;
            column--;
            int id = row * getNumberOfColumns() + column + 1;
            Cell* cell = getCellNyId(id);
            return cell;
        }
    }    
    return &Cell(-1,-1,-1,"","ERROR");   
}

void CellManager::applyFormula(int cellId)
{
    bool hasError = false;
    char operation;
    Cell* formulaCell = getCellNyId(cellId);
    string formula = formulaCell->getFileValue();
    string newFormula;
    
    

    for (int i = 1; i < formula.size(); i++)
    {
        newFormula += formula[i];
        switch (formula[i])
        {
         case'+': operation = formula[i]; break;
         case'-': operation = formula[i]; break;
         case'*': operation = formula[i]; break;
         case'^': operation = formula[i]; break;
         case'/': operation = formula[i]; break;
        }
    }

    newFormula =Function().removeSpaces(newFormula);
    
    vector<string> words= Function().splitBySymbol(newFormula,operation);
    double result=operation=='*'?1:0;
    

    for (int i = 0; i < 2; i++)
    {
        double value;
       
       
        if (Function().isDouble(words[i])|| Function().isInt(words[i]))
        {
            value = stod(words[i]);
        }
        else
        {
            Cell* cell = getCellByAdress(words[i]);
            if (cell->getId()==formulaCell->getId())
            {
                cout << "You can't use the target cell as an argument" << endl;
               
                hasError = true;
                break;
            }
           
            if (cell->getDataType()=="ERROR" || Function().isFormula(cell->getValue()))
            {
               
                hasError = true;
                break;
            }
            value = cell->getNumericValue();
            
        }
        if (value == 0 && operation == '/' && i==1)
        {
            
            hasError = true;
            break;
        }
        switch (operation)
        {
        
             case'+': result += value; break;
             case'-':
             if (i==0)
            {
                result += value;
            }
             else
            {
                result -= value;
            } break;
             case'*': result *= value; break;
             case'^':
             if (i==0)
                 {
                     result += value;
                 }
             else
                 {
                     result = pow(result, value);
                 }
             break;
             case'/': 
             if (i==0)
                 {
                     result += value;
                 }
             else 
                 {
                     result /= value;
                 }
             break;
        }
       
    }
    if (hasError)
    {
        formulaCell->setValue("ERROR");
    }
    else
    {
        formulaCell->setValue(Function().removeTailingZeros(to_string(result)));
    }
}
   