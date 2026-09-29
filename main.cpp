// Main file handles all the execution and output of all modules 
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <stdexcept>
#include "Consoleutil.h"
#include "Login.h"
#include "User.h"

using namespace std;

int main()
{
    header("WELCOME");

    cout << "Manage your daily expenses easily.\n";

    loading("Starting Application");
    User u;
    Login l;
    int choice = 0;
    bool loggedIn = false;

    do
    {
        header("MAIN MENU");

        console::color(console::NEON);
        cout << "1. Sign Up\n";
        cout << "2. Login\n";

        if (loggedIn)
        {
            cout << "---------------------------------------------\n";
            cout << "3. Add Expense\n";
            cout << "4. Display Expenses\n";
            cout << "5. Reload File\n";
            cout << "6. Search Expense\n";
            cout << "7. Delete Expense\n";
            cout << "8. Update Expense\n";
            cout << "9. Expense Summary\n";
            cout << "10. Set Budget\n";
            cout << "11. Monthly Report\n";
        }
        else
        {
            console::color(console::RED);
            cout << "\nLogin first to unlock Options 3-11.\n";
            console::reset();
        }

        console::color(console::NEON);
        cout << "\n12. Exit\n";
        console::reset();

        console::color(console::LIGHT_YELLOW);
        cout << "Enter your choice: ";
        console::reset();

        try
        {
            cin >> choice;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                choice = 0;
                throw invalid_argument("Menu choice must be a valid number.");
            }

            cin.ignore(10000, '\n');

            if (!loggedIn && choice >= 3 && choice <= 11)
            {
                throw logic_error("Access Denied: Please login first!");
            }

            system("cls");

            switch (choice)
            {
            case 1:
                l.signup();
                break;
            case 2:
                if (l.login())
                {
                    loggedIn = true;
                    u.setSessionUser(l.getUsername());
                }
                else
                {
                    pauseScreen();
                }
                break;
            case 3:
                console::color(console::CYAN);
                u.addtouser();
                console::reset();
                pauseScreen();
                break;
            case 4:
                console::color(console::BLUE);
                u.displayuser();
                console::reset();
                pauseScreen();
                break;
            case 5:
                console::color(console::BLUE);
                u.loadfromfile();
                console::reset();
                console::color(console::GREEN);
                cout << "File reloaded successfully." << endl;
                console::reset();
                transitionDelay();
                break;
            case 6:
                console::color(console::BLUE);
                u.searchbyid();
                console::reset();
                pauseScreen();
                break;
            case 7:
                console::color(console::RED);
                u.deleteExpense();
                console::reset();
                pauseScreen();
                break;
            case 8:
                console::color(console::CYAN);
                u.updateExpense();
                console::reset();
                pauseScreen();
                break;
            case 9:
                console::color(console::LIGHT_GREEN);
                u.summary();
                console::reset();
                pauseScreen();
                break;
            case 10:
                console::color(console::CYAN);
                u.changeBudget();
                console::reset();
                pauseScreen();
                break;
            case 11:
                console::color(console::LIGHT_GREEN);
                u.showMonthlyReport();
                console::reset();
                pauseScreen();
                break;
            case 12:
                console::color(console::GRAY);
                cout << "Exiting program..." << endl;
                console::reset();
                Sleep(1000);
                break;
            default:
                throw invalid_argument("Invalid Selection! Please choose a number between 1 and 12.");
            }
        }
        catch (const exception &e)
        {
            console::color(console::RED);
            cout << "\n[ ERROR ]: " << e.what() << endl;
            console::reset();
            pauseScreen();
        }

    } while (choice != 12);

    return 0;
}