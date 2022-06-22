#include <iostream>
#include "cell.h"
#include "function.h"

using namespace std;

Cell::Cell(int id, int row, int column, string value, string dataType)
{
    setId(id);
    setRow(row);
    setColumn(column);
    setValue(value);
    setDataType(dataType);
}


Cell::Cell():Cell(0,0,0,"empty","unknown")
{
}

int Cell::getId()
{
    return id;
}
void Cell::setId(int id)
{
    this->id = id;
}
int Cell::getRow()
{
    return row;
}

void Cell::setRow(const int row)
{
    this->row = row;
}

int Cell::getColumn()
{
    return column;
}
void Cell::setColumn(const int column)
{
    this->column = column;
}

string Cell::getValue()
{
    return value;
}
void Cell::setValue(string  value)
{
    this->value= value;
}
string Cell::getDataType()
{
    return dataType;
}
void Cell::setDataType(string dataType)
{
   this->dataType=dataType;
}

string Cell::getFileValue()
{
    return fileValue;
}
void Cell::setFileValue(string fileValue)
{
    this->fileValue = fileValue;
}

void Cell::getInfo()
{
    cout << "Cell id: " << id << endl;
    cout << "Cell row number: " << row << endl;
    cout << "Cell column number: " << column << endl;
    cout << "Cell value: " << getValue() << endl;
    cout << "Cell data type: " << dataType << endl;

}

bool Cell::isValueValid()
{
    
    if (Function().isInt(value))
    {
        setDataType("int");
    }
    else if (Function().isDouble(value))
    {
        setDataType("double");
    }
    else if (Function().isFormula(value))
    {
        setDataType("formula");
    }
    /*
    else if (value != "empty value" && value != "")
        {
        // if (cells[i].getValue()) proverqvame dali valueto ima \ ili " i ako ima proverqvame dali sa escapenati
        //samo ako sa escapenati slagame kletkata kato string inache trqbva da vleze v unknown data type

        if (Function().doesWordContainChar(value, '\\')) // proverqvam dali ima \ v stringa
        {
            
            if ((value.find("\\\\") != std::string::npos))// proverqvam dali e escapenata
            {
                setDataType("string");//ako e - kazvam ok
            }
            else
            {

                setDataType("unknown");//ako ne e pravq data taipa na unknown i printiram iskaniq message
                cout << "Error. row " << getRow()+1 << ", col" << getColumn()+1 << ", " << getValue() << " is an unknown data type" << endl;

                return false;
            }
        }

        if (Function().doesWordContainChar(getValue(), '\"')) // proverqvam dali ima kavichka v stringa
        {
            if ((value.find("\\\"") != std::string::npos))// proverqvam dali stringa e escapenat
            {
                setDataType("string");//ako e - kazvam ok
            }
            else
            {
                setDataType("unknown");//ako ne e pravq data taipa na unknnown i printiram iskaniq message
                cout << "Error. row " << getRow() << ", col" <<getColumn() << ", " << value << " is an unknown data type" << endl;

                return false;
            }
        }
    }*/
    else if  (value != "empty value" && value != "")
    {
        if (Function().isValidString(value))
        {
            setDataType("string");//ako e - kazvam ok
            value = Function().getAbsString(value);
        }
        else
        {
            setDataType("unknown");//ako ne e pravq data taipa na unknnown i printiram iskaniq message
            cout << "Error. row " << row+1 << ", col " << column+1 << ", " << value << " is an unknown data type" << endl;

            return false;
        }

    }
    else
    {
        setDataType("unknown");
    }

    return true;
}

double Cell::getNumericValue()
{
    if (dataType=="formula")
    {
        if (value=="ERROR")
        {
            return 0;
        }
        else
        {
            return  stod(value);
        }
    }else if (dataType=="int")
    {
        return Function().strToInt(value);
    }
    else if (dataType=="double")
    {
        
        return stod(value);
    }
    else if (dataType=="string")
    {
        string temp = Function().getAbsString(value);
        
        if (Function().isDouble(temp))
        {
            return stod(temp);
        }
        else if (Function().isNumber(temp))
        {
            return Function().strToInt(temp);
        }
        else
        {
            return 0;
        }
    }

    return 0;
}