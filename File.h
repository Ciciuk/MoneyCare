#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

#include "Record.h"

using namespace std;

class File {
    const string FILE_NAME;
    int lastId;

   public:
   File(string fileName) : FILE_NAME (fileName){};
   virtual vector<Record> loadRecordsByUserId(){};
   virtual void saveNewRecord(){};

   string getName();
   int getLastId();
   void setLastId(int id);
};

#endif