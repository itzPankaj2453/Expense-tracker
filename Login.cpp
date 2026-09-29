// It will handle all the authentication part
#include "Login.h"
#include "Consoleutil.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

using namespace std;

Login::Login()
{
    username = "";
    password = 0;
}

string Login::getUsername() const
{
    return username;
}

void Login::signup()
{
    string checkName;
    cout << "Enter User Name: ";

    getline(cin, checkName);

    ifstream checkFile("all_users.txt");
    if (checkFile)
    {
        string fileUname;
        int filePass;
        while (getline(checkFile, fileUname))
        {
            checkFile >> filePass;
            checkFile.ignore();
            if (fileUname == checkName)
            {
                checkFile.close();
                throw logic_error("Username " + checkName + " already exists! Try another name.");
            }
        }
        checkFile.close();
    }

    username = checkName;
    cout << "Enter Password (Numbers only): ";
    cin >> password;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw invalid_argument("Password must be a numeric value.");
    }
    cin.ignore();

    ofstream masterFile("all_users.txt", ios::app);
    if (!masterFile)
    {
        throw runtime_error("Cannot open or create user file on disk.");
    }
    masterFile << username << endl;
    masterFile << password << endl;
    masterFile.close();

    console::color(console::LIGHT_GREEN);
    cout << "Sign Up Successful!\n";
    console::reset();
    transitionDelay(1500);
}

bool Login::login()
{
    string uname;
    int pass;
    cout << "Enter User Name: ";
    getline(cin, uname);

    cout << "Enter Password: ";
    cin >> pass;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw invalid_argument("Password must be a numeric value.");
    }
    cin.ignore();

    ifstream masterFile("all_users.txt");
    if (!masterFile)
    {
        throw logic_error("No users found. Please Sign Up first.");
    }

    int filePass;
    string fileUname;
    bool found = false;

    while (getline(masterFile, fileUname))
    {
        masterFile >> filePass;
        masterFile.ignore();
        if (fileUname == uname && filePass == pass)
        {
            found = true;
            this->username = fileUname;
            this->password = filePass;
            break;
        }
    }
    masterFile.close();

    if (found)
    {
        console::color(console::LIGHT_GREEN);
        cout << "--- Login Successful! Welcome " << username << " ---" << endl;
        console::reset();
        transitionDelay(1500);
        return true;
    }
    else
    {
        console::color(console::RED);
        cout << "Wrong Username or Password! Try again." << endl;
        console::reset();
        return false;
    }
}