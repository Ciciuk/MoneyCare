#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>

#include "Record.h"

using namespace std;

class File {
    const string FILE_NAME;

   public:
   File(string fileName) : FILE_NAME (fileName){};
   virtual vector<Record> loadRecordsByUserId(int id){};
   virtual void saveNewRecord(const Record income){};
   void setName(string s);
   string getName();
};

#endif