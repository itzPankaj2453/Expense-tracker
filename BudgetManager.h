#ifndef BUDGETMANAGER_H
#define BUDGETMANAGER_H

#include <string>

class BudgetManager
{
private:
    float budget;

public:
    BudgetManager();

    void setBudgetAmount(float amount);
    float getBudgetAmount() const;

    void checkStatus(int usercount, const float expense[]) const;
    void runMonthlyReport(int usercount, const int productId[], const std::string title[],
                          const std::string category[], const std::string date[], const float expense[]) const;
};

#endif