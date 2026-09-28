#ifndef USER_H
#define USER_H

#include <string>
#include "BudgetManager.h"

class User
{
private:
    int expenseId[100];
    std::string title[100];
    std::string category[100];
    std::string date[100];
    float expense[100];
    int usercount;
    std::string currentFileName;

    // Connected module instance
    BudgetManager budgetMgr;

public:
    User();
    void setSessionUser(std::string uname);
    void savetofile();
    void loadfromfile();
    void addtouser();
    void displayuser();
    void searchbyid();
    void updateExpense();
    void deleteExpense();
    void summary();
    void changeBudget();
    void showMonthlyReport();
};

#endif
