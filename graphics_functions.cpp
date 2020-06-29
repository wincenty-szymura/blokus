#include"graphics_functions.h"

void go_to_console_position(size_t x, size_t y)
{
    COORD position{ static_cast<SHORT>(x), static_cast<SHORT>(y) };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void top::draw_square(size_t x, size_t y)
{
    go_to_console_position(x, y);
    std::cout << "    ";
    go_to_console_position(x, y + 1);
    std::cout << "____"; // separates the square from the square below
}

void bottom::draw_square(size_t x, size_t y)
{
    go_to_console_position(x, y);
    std::cout << "    ";
    go_to_console_position(x, y + 1);
    std::cout << "    "; // there is no square below, so no need to separate
}