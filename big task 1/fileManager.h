#ifndef fileManager_header
#define fileManager_header
#include "cellManager.h"
#include "Function.h"
#include "cell.h"
#include <iostream>
#include <vector>
using namespace std;

class FileManager {
private:
    string fileName;
    CellManager cellManager;


public:
    FileManager();

    string getFileName();
    void setFileName(string name);

    CellManager* getCellManager();  
    

    bool isOpened();
    void read(string name);
    void save();
    void close();
    void saveAs(string name);
    void help();
};


#endif
