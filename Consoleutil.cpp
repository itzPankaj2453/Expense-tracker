#include "Consoleutil.h"
#include <iostream>
#include <cstdlib>
#include <windows.h>

void console::color(int c)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void console::reset()
{
    color(WHITE);
}

void header(std::string title)
{
    system("cls");

    console::color(console::LIGHT_YELLOW);

    std::cout << "=============================================================\n";
    std::cout << "                EXPENSE TRACKER SYSTEM\n";
    std::cout << "=============================================================\n";
    std::cout << " " << title << std::endl;
    std::cout << "=============================================================\n\n";

    console::reset();
}

void loading(std::string text)
{
    std::cout << "\n"
              << text;

    for (int i = 0; i < 5; i++)
    {
        std::cout << ".";
        Sleep(250);
    }

    system("cls");
}

void pauseScreen()
{
    console::color(console::LIGHT_YELLOW);
    std::cout << "\n\nPress any key to continue...";
    console::reset();

    system("pause > nul");
    system("cls");
}

void transitionDelay(int ms)
{
    std::cout << "\nLoading next screen...";
    Sleep(ms);
    system("cls");
}