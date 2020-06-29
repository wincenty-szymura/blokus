#ifndef GRAPHICS_FUNCTIONS_H
#define GRAPHICS_FUNCTIONS_H

#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<memory>
#include<cstdlib>
#include<windows.h>
#include<utility>

// allows moving around the console
void go_to_console_position(size_t x, size_t y); 

// distinguishes two types of squares used in order to display the game
namespace top
{
    void draw_square(size_t x, size_t y);
}
namespace bottom
{
    void draw_square(size_t x, size_t y);
}

#endif