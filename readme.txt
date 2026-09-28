EXPENSE TRACKER SYSTEM

====================================================
PROJECT OVERVIEW
================

Expense Tracker System is a C++ console application developed to help users manage their daily expenses efficiently. The application supports multiple users, where each user has a separate account and personal expense records stored in an individual text file.

====================================================
FEATURES
========

• User Sign Up & Login
• Separate Account for Every User
• Add New Expenses
• Display All Expenses
• Search Expense by Product ID
• Update Existing Expense
• Delete Expense
• Expense Summary
• Budget Management
• Monthly Expense Report
• Automatic File Saving & Loading

====================================================
HOW TO USE THE APPLICATION
==========================

Step 1:
Run the application.

Step 2:
Select **1. Sign Up** if you are a new user.

Step 3:
Enter a unique username.

Step 4:
Enter a numeric password.

Step 5:
Return to the main menu and select **2. Login**.

Step 6:
Enter your username and password.

Step 7:
If you are logging in for the first time, the application will ask you to set your overall budget.

Step 8:
After logging in, the following options become available:

• Add Expense
- Enter Product ID
- Enter Title
- Enter Category
- Enter Date (dd-mm-yyyy)
- Enter Expense Amount

• Display Expenses
- View all saved expense records.

• Reload File
- Reloads the latest saved data from your file.

• Search Expense
- Search any expense using Product ID.

• Delete Expense
- Delete an expense by entering its Product ID.

• Update Expense
- Modify Category, Date or Expense Amount.

• Expense Summary
- Displays:
- Total Records
- Total Expense
- Average Expense
- Highest Expense
- Lowest Expense

• Set Budget
- Update your overall budget at any time.

• Monthly Report
- Enter Month (MM) and Year (YYYY) to view monthly expenses and remaining budget.

Step 9:
Select **12. Exit** to close the application.

====================================================
PROJECT MECHANISM
=================

1. A new user creates an account using Sign Up.

2. The application stores the username and password inside:

   all_users.txt

3. During Login, the entered credentials are verified using this file.

4. After successful login, the application automatically creates (or opens) a personal file for that user.

Example:

```
user_John.txt
user_Alice.txt
user_Nisha.txt
```

5. The user's budget and all expense records are loaded from this file.

6. Whenever a new expense is added, updated, or deleted, the changes are automatically saved.

7. The next time the user logs in, all previous data is loaded automatically.

====================================================
FILE STRUCTURE
==============

Project Folder

│
├── ExpenseTracker.exe
├── all_users.txt
├── user_John.txt
├── user_Alice.txt
├── user_Nisha.txt
├── *.cpp
├── *.h
└── README.txt

====================================================
MENU OPTIONS
============

1. Sign Up
2. Login
3. Add Expense
4. Display Expenses
5. Reload File
6. Search Expense
7. Delete Expense
8. Update Expense
9. Expense Summary
10. Set Budget
11. Monthly Report
12. Exit

====================================================
DATA STORAGE
============

all_users.txt

Stores the login credentials of all registered users.

Example:

John
1234
Alice
5678

---

user_John.txt

Stores:

• Budget
• Product ID
• Title
• Category
• Date
• Expense Amount

Each registered user has their own separate file.

====================================================
IMPORTANT NOTES
===============

• Sign Up only once using a unique username.
• Password must contain numbers only.
• Login is required before accessing expense-related features.
• Maximum of 100 expense records can be stored per user.
• All data is saved automatically after every change.
• Do not delete or rename the text files while the application is running.
• Keep all project files in the same folder as the executable.

====================================================
WORKFLOW
========

Run Program
↓
Sign Up (New User)
↓
Credentials Saved in all_users.txt
↓
Login
↓
Authentication Successful
↓
Open/Create user_<username>.txt
↓
Set Budget (First Login Only)
↓
Manage Expenses
(Add / Search / Update / Delete)
↓
Data Saved Automatically
↓
Exit
↓
Next Login Loads Previous Data

====================================================
THANK YOU
=========

Thank you for using the Expense Tracker System.
This application is designed to provide a simple, efficient, and organized way to manage personal expenses while maintaining separate records for each registered user.
