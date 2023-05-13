#include "File.h"

string File::getName(){
    return FILE_NAME;
}

int File::getLastId() {
    return lastId;
}

void File::setLastId(int id){
    lastId = id;
}