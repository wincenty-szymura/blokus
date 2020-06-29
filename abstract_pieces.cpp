#include"abstract_pieces.h"

piece::piece()
{
    number_of_squares = 0;
    length = 0;
    width = 0;
    handle = 0;
    is_there_square = nullptr;
}

piece::piece(const size_t squares, const size_t l, const size_t w,
    const size_t hand)
{
    if (squares < 1 || l < 1 || w < 1 || hand < 0 
        || squares > l * w || hand > l * w - 1) {
        throw("Exception: trying to declare an invalid piece");
    }
    number_of_squares = squares;
    length = l;
    width = w;
    handle = hand;
    is_there_square = std::make_unique<bool[]>(length * width);
    for (size_t i{}; i < length * width; i++) {
        if (i < number_of_squares) {
            is_there_square[i] = true;
        }
        else {
            is_there_square[i] = false;
        }
    }
}

piece::piece(const piece& input_piece)
{
    is_there_square.reset();
    is_there_square = nullptr; 
    number_of_squares = input_piece.number_of_squares;
    length = input_piece.length;
    width = input_piece.width;
    handle = input_piece.handle;
    if (length > 0 && width > 0) {
        is_there_square = std::make_unique<bool[]>(length * width);
        for (size_t i{}; i < length * width; i++) { // copy piece data
            is_there_square[i] = input_piece.is_there_square[i];
        }
    }
}

piece::piece(piece&& input_piece) noexcept
{
    // move member data of type size_t from input_piece
    number_of_squares = input_piece.number_of_squares;
    length = input_piece.length;
    width = input_piece.width;
    handle = input_piece.handle;
    // move unique pointer
    is_there_square = std::move(input_piece.is_there_square); 
    // set member data of type size_t of the input_piece to zero
    input_piece.number_of_squares = 0;
    input_piece.length = 0;
    input_piece.width = 0;
    input_piece.handle = 0;
}

piece& piece::operator=(const piece& input_piece)
{
    if (&input_piece == this) {
        return *this; // no self assignment
    }
    is_there_square.reset();
    is_there_square = nullptr;
    number_of_squares = input_piece.number_of_squares;
    length = input_piece.length;
    width = input_piece.width;
    handle = input_piece.handle;
    if (length > 0 && width > 0) {
        is_there_square = std::make_unique<bool[]>(length * width);
        for (size_t i{}; i < length * width; i++) { // copy piece data
            is_there_square[i] = input_piece.is_there_square[i];
        }
    }
    return *this; // return pointer to the object
}
piece& piece::operator=(piece&& input_piece) noexcept
{
    std::swap(number_of_squares, input_piece.number_of_squares);
    std::swap(length, input_piece.length);
    std::swap(width, input_piece.width);
    std::swap(handle, input_piece.handle);
    std::swap(is_there_square, input_piece.is_there_square);
    return *this; // return pointer to the object
}

bool& piece::operator()(const size_t m, const size_t n) const
{
    if (m > 0 && m <= width && n > 0 && n <= length) {
        return is_there_square[(n - 1) + (m - 1) * length];
    }
    else {
        throw("Exception: out of range");
    }
}

size_t piece::get_number_of_squares() const
{
    return number_of_squares;
}

size_t piece::get_length() const
{
    return length;
}

size_t piece::get_width() const
{
    return width;
}

size_t piece::get_handle() const
{
    return handle;
}

void piece::display(const size_t x_left, const size_t y_top,
    const size_t signature) const
{
    for (size_t i{}; i < width; i++) {
        for (size_t j{}; j < length; j++) {
            // if not in the bottom row
            if (is_there_square[i * length + j] && i < width - 1) {
                // if there is a square one row below
                if (is_there_square[(i + 1) * length + j]) {
                    top::draw_square(x_left + 5 * j, y_top + 2 * i);
                }
                // if there is no square one row below
                else {
                    bottom::draw_square(x_left + 5 * j, y_top + 2 * i);
                }
            }
            // if in the bottom row
            else if (is_there_square[i * length + j] && i == width - 1) {
                bottom::draw_square(x_left + 5 * j, y_top + 2 * i);
            }
            if (i * length + j == handle) {
                go_to_console_position(x_left + 5 * j, y_top + 2 * i);
                std::cout << signature; // position on player's piece vector
            }
        }
    }
}

void pentomino::rotate() // used by 3 out of 4 classes derived from pentomino
{
    bool changed{ false }; // used for updating handle 
    size_t divisor{ length };
    std::vector<std::pair<size_t, bool>> before; // piece before rotation
    // reserve space on the vector, it makes the program faster
    before.reserve(length * width);
    for (size_t i{}; i < length * width; i++) {
        before.push_back(std::make_pair(i, is_there_square[i]));
    }
    std::vector<std::pair<size_t, bool>> after(before.size()); // after rotation
    for (size_t i{}; i < length; i++) {
        std::copy_if(before.begin(), before.end(), after.begin() + i * width,
            [i, divisor](std::pair<size_t, bool> pair) {
            return (pair.first % divisor == divisor - 1 - i);
        }); // rotate by adding bools to the after vector in specific order
    }
    // the after vector is reversed compared to what is needed
    for (size_t i{}; i < length * width; i++) { 
        is_there_square[i] = after.at(length * width - 1 - i).second;
        if (after.at(length * width - 1 - i).first == handle && !changed) {
            handle = i; // update handle
            changed = true; // avoid changing handle twice
        }
    }
    std::swap(length, width);
}