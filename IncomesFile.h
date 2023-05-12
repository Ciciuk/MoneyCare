#ifndef INCOMESFILE_H
#define INCOMESFILE_H

#include "File.h"
#include "AuxilaryMethods.h"
#include "Markup.h"

#include <string>
#include <vector>



using namespace std;

class IncomesFile : public File{
    

   public:
    IncomesFile(string fileName) : File(fileName){};
    vector<Record> loadRecordsByUserId(int id);
    void saveNewRecord(const Record income);
};

#endif