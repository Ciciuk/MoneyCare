#include "User.h"

int User::getId() const {
    return id;
};

string User::getLogin() const {
    return login;
};

string User::getPassword() const {
    return password;
};

string User::getName() const {
    return name;
};

string User::getSurname() const {
    return surname;
};

void User::setId(int id){
    this->id = id;
};

void User::setLogin(string login){
    this->login = login;
};

void User::setPassword(string password){
    this->password = password;
};

void User::setName(string name){
    this->name = name;
};

void User::setSurname(string surname) {
    this->surname = surname;
};