#ifndef CONSOLEUTIL_H
#define CONSOLEUTIL_H

#include <string>

class console
{
public:
    static const int BLACK = 0;
    static const int BLUE = 1;
    static const int GREEN = 2;
    static const int CYAN = 3;
    static const int RED = 4;
    static const int PURPLE = 5;
    static const int YELLOW = 6;
    static const int WHITE = 7;
    static const int LIGHT_BLUE = 9;
    static const int LIGHT_GREEN = 10;
    static const int LIGHT_RED = 12;
    static const int LIGHT_YELLOW = 14;
    static const int BRIGHT_WHITE = 15;
    static const int GRAY = 8;
    static const int NEON = 11;

    static void color(int c);
    static void reset();
};

void header(std::string title);
void loading(std::string text);
void pauseScreen();
void transitionDelay(int ms = 1500);

#endif
