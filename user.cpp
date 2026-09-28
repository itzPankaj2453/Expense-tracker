#include "User.h"
#include "Consoleutil.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <windows.h>

using namespace std;

User::User()
{
    usercount = 0;
    currentFileName = "";
}

void User::setSessionUser(string uname)
{
    currentFileName = "user_" + uname + ".txt";
    loadfromfile();

    if (budgetMgr.getBudgetAmount() <= 0.0f)
    {
        console::color(console::LIGHT_YELLOW);
        cout << "\n[ NOTICE ]: No budget configured for this user profile yet.\n";
        console::reset();
        try
        {
            changeBudget();
        }
        catch (const exception &e)
        {
            console::color(console::RED);
            cout << "[ ERROR ]: " << e.what() << "\nDefaulting budget to 0.\n";
            console::reset();
            Sleep(1500);
        }
    }
}

void User::savetofile()
{
    if (currentFileName.empty())
        return;

    ofstream outfile(currentFileName, ios::trunc);
    if (!outfile)
    {
        throw runtime_error("Failed to access save file. Data may not be saved.");
    }

    outfile << budgetMgr.getBudgetAmount() << endl;

    for (int i = 0; i < usercount; i++)
    {
        outfile << expenseId[i] << endl;
        outfile << title[i] << endl;
        outfile << category[i] << endl;
        outfile << date[i] << endl;
        outfile << expense[i] << endl;
    }
    outfile.close();
    console::color(console::LIGHT_GREEN);
    cout << "Data Saved Successfully!" << endl;
    console::reset();
}

void User::loadfromfile()
{
    if (currentFileName.empty())
        return;

    ifstream infile(currentFileName);
    if (!infile)
    {
        usercount = 0;
        budgetMgr.setBudgetAmount(0.0f);
        return;
    }

    usercount = 0;
    float savedBudget = 0.0f;
    if (!(infile >> savedBudget))
    {
        savedBudget = 0.0f;
    }
    budgetMgr.setBudgetAmount(savedBudget);
    infile.ignore();

    while (usercount < 100 && infile >> expenseId[usercount])
    {
        infile.ignore();
        getline(infile, title[usercount]);
        getline(infile, category[usercount]);
        getline(infile, date[usercount]);
        infile >> expense[usercount];
        infile.ignore();
        usercount++;
    }
    infile.close();
}

void User::changeBudget()
{
    float amt;
    cout << "Enter your total overall budget (INR): ";
    cin >> amt;
    budgetMgr.setBudgetAmount(amt);
    savetofile();
    console::color(console::LIGHT_GREEN);
    cout << "Budget updated successfully to INR " << amt << endl;
    console::reset();
    budgetMgr.checkStatus(usercount, expense);
    transitionDelay(1200);
}

void User::showMonthlyReport()
{
    budgetMgr.runMonthlyReport(usercount, expenseId, title, category, date, expense);
}

void User::addtouser()
{
    if (usercount >= 100)
    {
        throw overflow_error("Storage list is full! Maximum limit of 100 expenses reached.");
    }

    int tempId;
    cout << "Enter Expense ID (Number only): ";
    cin >> tempId;

    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw invalid_argument("Expense ID must be a valid number.");
    }

    for (int i = 0; i < usercount; i++)
    {
        if (expenseId[i] == tempId)
        {
            throw invalid_argument("Expense ID already exists! Duplicates are not allowed.");
        }
    }

    expenseId[usercount] = tempId;

    cout << "Enter Title: ";
    cin.ignore();
    getline(cin, title[usercount]);
    cout << "Enter Category: ";
    getline(cin, category[usercount]);
    cout << "Enter Date (dd-mm-yyyy): ";
    getline(cin, date[usercount]);

    cout << "Enter Expense Amount (INR): ";
    cin >> expense[usercount];
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw invalid_argument("Expense amount must be a numeric value.");
    }

    usercount++;
    console::color(console::LIGHT_GREEN);
    cout << "Expense Added!" << endl;
    console::reset();
    savetofile();
    budgetMgr.checkStatus(usercount, expense);
    transitionDelay(1000);
}

void User::displayuser()
{
    if (usercount == 0)
    {
        throw logic_error("No expenses recorded yet.");
    }
    console::color(console::BLUE);
    cout << "\n--- Your Expense Records ---" << endl;
    for (int i = 0; i < usercount; i++)
    {
        cout << "Expense ID : " << expenseId[i] << endl;
        cout << "Title      : " << title[i] << endl;
        cout << "Category   : " << category[i] << endl;
        cout << "Date       : " << date[i] << endl;
        cout << "Expense    : (INR) " << expense[i] << endl;
        cout << "------------------------------------" << endl;
    }
    console::reset();
    budgetMgr.checkStatus(usercount, expense);
}

void User::searchbyid()
{
    if (usercount == 0)
        throw logic_error("No expenses recorded to search.");

    int searchId;
    cout << "Enter Expense ID to search: ";
    cin >> searchId;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw invalid_argument("Expense ID must be a valid number.");
    }

    for (int i = 0; i < usercount; i++)
    {
        if (expenseId[i] == searchId)
        {
            cout << "\n--- Record Found ---" << endl;
            cout << "Expense ID : " << expenseId[i] << endl;
            cout << "Title      : " << title[i] << endl;
            cout << "Category   : " << category[i] << endl;
            cout << "Date       : " << date[i] << endl;
            cout << "Expense    : (INR) " << expense[i] << endl;
            return;
        }
    }
    throw logic_error("Expense ID not found in records.");
}

void User::updateExpense()
{
    if (usercount == 0)
        throw logic_error("No expenses available to update.");

    int updateId;
    cout << "Enter Expense ID to update: ";
    cin >> updateId;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw invalid_argument("Expense ID must be a valid number.");
    }

    cin.ignore();

    for (int i = 0; i < usercount; i++)
    {
        if (expenseId[i] == updateId)
        {
            cout << "\n--- Current Record ---" << endl;
            cout << "Expense ID: " << expenseId[i] << " | Title: " << title[i] << " | Category: " << category[i] << " | Date: " << date[i] << " | Expense: (INR) " << expense[i] << endl;
            cout << "------------------------------------" << endl;

            string temp;
            cout << "Enter New Category (or press Enter to keep old): ";
            getline(cin, temp);
            if (!temp.empty())
                category[i] = temp;

            cout << "Enter New Date (or press Enter to keep old): ";
            getline(cin, temp);
            if (!temp.empty())
                date[i] = temp;

            cout << "Enter New Expense Amount (or enter -1 to keep old): ";
            float tempExpense;
            cin >> tempExpense;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n');
                throw invalid_argument("Expense amount must be a numeric value. Update Cancelled.");
            }

            if (tempExpense >= 0)
                expense[i] = tempExpense;

            savetofile();
            console::color(console::GREEN);
            cout << "Expense updated successfully!" << endl;
            console::reset();
            budgetMgr.checkStatus(usercount, expense);
            transitionDelay(1200);
            return;
        }
    }
    throw logic_error("Expense ID not found.");
}

void User::deleteExpense()
{
    if (usercount <= 0)
        throw logic_error("No expenses available to delete.");

    int deleteId;
    cout << "Enter Expense ID to delete: ";
    cin >> deleteId;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        throw invalid_argument("Expense ID must be a valid number.");
    }

    char confirm;
    console::color(console::RED);
    cout << "Are You Sure? (Y/N): ";
    console::reset();
    cin >> confirm;

    if (confirm == 'Y' || confirm == 'y')
    {
        for (int i = 0; i < usercount; i++)
        {
            if (expenseId[i] == deleteId)
            {
                for (int j = i; j < usercount - 1; j++)
                {
                    expenseId[j] = expenseId[j + 1];
                    title[j] = title[j + 1];
                    category[j] = category[j + 1];
                    date[j] = date[j + 1];
                    expense[j] = expense[j + 1];
                }
                usercount--;
                savetofile();
                console::color(console::GREEN);
                cout << "Expense deleted successfully!" << endl;
                console::reset();
                transitionDelay(1200);
                return;
            }
        }
        throw logic_error("Expense ID not found.");
    }
    else
    {
        cout << "Deletion Cancelled!!\n";
    }
}

void User::summary()
{
    if (usercount == 0)
        throw logic_error("No expenses recorded yet to summarize.");

    float total = 0;
    int highest = 0, lowest = 0;
    for (int i = 0; i < usercount; i++)
    {
        total += expense[i];
        if (expense[i] > expense[highest])
            highest = i;
        if (expense[i] < expense[lowest])
            lowest = i;
    }

    console::color(console::LIGHT_BLUE);
    cout << "\n========== Expense Summary ==========\n";
    cout << "Total Records   : " << usercount << endl;
    cout << "Total Expense   : INR " << total << endl;
    cout << "Average Expense : INR " << total / usercount << endl;
    cout << "Highest Expense : INR " << expense[highest] << " (" << title[highest] << ")" << endl;
    cout << "Lowest Expense  : INR " << expense[lowest] << " (" << title[lowest] << ")" << endl;
    console::reset();
    budgetMgr.checkStatus(usercount, expense);
}