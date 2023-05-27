#ifndef USERFILE_H
#define USERFILE_H

#include <string>
#include <vector>

#include "File.h"
#include "Markup.h"
#include "User.h"

using namespace std;


class UserFile {
    const string FILE_NAME;

   public:
    UserFile(string userFileName) : FILE_NAME(userFileName) {
    }
    void saveNewUserInFile(const User newUser);
    vector<User> loadUsersFromFile();
    void saveUserAfterPaswordChange(const User user);
};
#endif