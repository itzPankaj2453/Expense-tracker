// This module is designed to store the Budget and Expenses 
#include "BudgetManager.h"
#include "Consoleutil.h"
#include <iostream>
#include <sstream>

using namespace std;

BudgetManager::BudgetManager()
{
    budget = 0.0f;
}

void BudgetManager::setBudgetAmount(float amount)
{
    if (amount < 0)
    {
        throw invalid_argument("Budget must be a valid positive number.");
    }
    budget = amount;
}

float BudgetManager::getBudgetAmount() const
{
    return budget;
}

void BudgetManager::checkStatus(int usercount, const float expense[]) const
{
    float totalExpense = 0;
    for (int i = 0; i < usercount; i++)
    {
        totalExpense += expense[i];
    }

    if (budget > 0 && totalExpense > budget)
    {
        console::color(console::RED);
        cout << "\n[WARNING] Budget Exceeded! Total Expenses (INR " << totalExpense
             << ") exceed your Budget limit (INR " << budget << ")!" << endl;
        console::reset();
    }
}

void BudgetManager::runMonthlyReport(int usercount, const int productId[], const string title[],
                                     const string category[], const string date[], const float expense[]) const
{
    string inputMonth, inputYear;
    cout << "Enter Month (mm, e.g., 05): ";
    cin >> inputMonth;
    cout << "Enter Year (yyyy, e.g., 2026): ";
    cin >> inputYear;

    float monthlyTotal = 0;
    bool foundRecords = false;

    console::color(console::LIGHT_BLUE);
    cout << "\n=========================================\n";
    cout << "      MONTHLY REPORT: " << inputMonth << "-" << inputYear << "\n";
    cout << "=========================================\n";
    console::reset();

    for (int i = 0; i < usercount; i++)
    {
        stringstream ss(date[i]);
        string d, m, y;
        getline(ss, d, '-');
        getline(ss, m, '-');
        getline(ss, y, '-');

        if (m == inputMonth && y == inputYear)
        {
            foundRecords = true;
            monthlyTotal += expense[i];
            cout << "ID: " << productId[i] << " | " << "Title: " << title[i]
                 << " | Cat: " << category[i] << " | INR " << expense[i] << endl;
        }
    }

    if (!foundRecords)
    {
        cout << "No expense records found for this specific month/year." << endl;
    }

    float remainingMoney = budget - monthlyTotal;

    cout << "-----------------------------------------\n";
    cout << "Overall Saved Budget : INR " << budget << endl;
    cout << "Total Month Expense  : INR " << monthlyTotal << endl;

    if (remainingMoney < 0)
    {
        console::color(console::RED);
        cout << "Remaining Balance    : INR " << remainingMoney << " (Budget Exceeded!)" << endl;
    }
    else
    {
        console::color(console::GREEN);
        cout << "Remaining Balance    : INR " << remainingMoney << endl;
    }
    console::reset();
    cout << "=========================================\n";
}