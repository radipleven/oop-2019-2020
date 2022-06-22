#ifndef cell_header
#define cell_header
using namespace std;
#include <string>
class Cell {
private:
	int id;
	int row;
	int column;
	string value;
	string dataType;
	string fileValue;

public:

	Cell(int id, int row, int column, string value,string dataType);

	Cell();

	int getId();
	
	void setId(int id);

	int getRow();

	void setRow(const int row);

	int getColumn();

	void setColumn(const int column);

	string getValue();

	void setValue(string value);

	string getDataType();

	void setDataType(string dataType);

	string getFileValue();

	void setFileValue(string name);

	void getInfo();

	bool isValueValid();

	double getNumericValue();

};


#endif