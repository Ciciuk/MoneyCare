#ifndef USER_H
#define USER_H

#include <iostream>

using namespace std;

class User {
    int id;
    string login;
    string password;
    string name;
    string surname;

   public:
    User(int id = 0, string login = "", string password = "", string name = "", string surname = "") {
        this->id = id;
        this->login = login;
        this->password = password;
        this->name = name;
        this->surname = surname;
    };

    int getId() const;
    string getLogin() const;
    string getPassword() const;
    string getName() const;
    string getSurname() const;

    void setId(int id);
    void setLogin(string login);
    void setPassword(string password);
    void setName(string name);
    void setSurname(string surname);
};

#endif