#ifndef cellManager_header
#define cellManager_header
#include <vector>
#include "cell.h"
#include "function.h"

class CellManager {

private:
	vector<Cell*> cells;
	int rows;
	int columns;
	
	
	
public:
	CellManager();
	
	void calculateTableSize(string fileName);
	int getNumberOfRows();
	int getNumberOfColumns();
	
	void setRows(int rows);
	void setColumns(int columns);
	vector<Cell*> getCells();
	void addCell(Cell* cell);
	void setAdressesOfCells();
	bool setCellDataTypes();
	void clearTable();
	int getMaxColWidth(int columnId);
	void print();
	void edit(int row, int column, string value);
	Cell* getCellNyId(int id);
	bool isRowValid(string row);
	bool isColumnValid(string column);
	Cell* getCellByAdress(string adress);
	void applyFormula(int cellid);
	

	
};


#endif