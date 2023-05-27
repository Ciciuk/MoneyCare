#include "UserFile.h"

void UserFile::saveNewUserInFile(const User newUser) {
    CMarkup xml;
    string fileName = "";

    fileName.append(FILE_NAME);
    fileName.append(".xml");
    bool fileExists = xml.Load(fileName);
    if (!fileExists) {
        xml.SetDoc("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
        xml.AddElem("Users");
    }

    xml.FindElem();
    xml.IntoElem();
    xml.AddElem("User");
    xml.IntoElem();
    xml.AddElem("UserId", newUser.getId());
    xml.AddElem("Login", newUser.getLogin());
    xml.AddElem("Password", newUser.getPassword());
    xml.AddElem("Name", newUser.getName());
    xml.AddElem("Surname", newUser.getSurname());
    xml.Save(fileName);
}

vector<User> UserFile::loadUsersFromFile() {
    CMarkup xml;
    vector<User> vUser;
    User user;
    string fileName = "";
    int lastId;

    fileName.append(FILE_NAME);
    fileName.append(".xml");
    xml.Load(fileName);

    xml.FindElem();
    xml.IntoElem();
    while (xml.FindElem("User")) {
        xml.FindChildElem("UserId");
        user.setId(stoi(xml.GetChildData()));
        xml.FindChildElem("Login");
        user.setLogin(xml.GetChildData());
        xml.FindChildElem("Password");
        user.setPassword(xml.GetChildData());
        xml.FindChildElem("Name");
        user.setName(xml.GetChildData());
        xml.FindChildElem("Surname");
        user.setSurname(xml.GetChildData());
        vUser.push_back(user);
        lastId = user.getId();
    }
    return vUser;
}

void UserFile::saveUserAfterPaswordChange(const User user) {

    CMarkup xml;
    string fileName = "";
    int idCheck = 0;
    bool lastId;


    fileName.append(FILE_NAME);
    fileName.append(".xml");
    lastId = xml.Load(fileName);

    xml.FindElem();
    xml.IntoElem();
    while (xml.FindElem("User")) {
        xml.FindChildElem("UserId");
        if (user.getId() == stoi(xml.GetChildData())){
            xml.FindChildElem("Password");
            xml.SetChildData(user.getPassword());
        }
    }
    xml.Save(fileName);
    // xml.FindChildElem("Password");
        
}