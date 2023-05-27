#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <iomanip>

#include "User.h"
#include "AuxilaryMethods.h"
#include "UserFile.h"

using namespace std;

class UserManager
{
	vector<User> users;
	UserFile userFile;

	User loggedUser;

	User userDataGathering();
	bool checkIfLoginIsNotUnique(string login);
	bool checkIfEmptyUsers();
	bool checkPassword(vector<User>::iterator i);
	bool checkLoginAndPassword();

public:
 	UserManager(string userFileName) : userFile(userFileName) {
		loadUsersFromFile();
	}

    int getLoggedUserId();
    void setLoggedUserId(int id);

    void loadUsersFromFile();
    void newUserRegistration();
    bool logginng();
    void changePassword();
};

#endif