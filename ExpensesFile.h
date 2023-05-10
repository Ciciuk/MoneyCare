#ifndef EXPENSESFILE_H
#define EXPENSESFILE_H

#include <File.h>

#include <string>
#include <vector>

using namespace std;

class ExpensesFile : public File{
    

   public:
    ExpensesFile(string fileName) : File(fileName){};
    vector<Record> loadRecordsByUserId(int id);
    void saveNewRecord(int id);
};

#endif