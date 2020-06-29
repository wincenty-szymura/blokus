#include"specific_pieces.h"

//
// MON0MINO_11
//

monomino_11::monomino_11(const size_t hand, const bool square) :
    monomino{ 1,1,hand }
{
    if (!square) {
        throw("Exception: trying to declare an invalid piece");
    }
    is_there_square[0] = square;
}

//
// DOMINO_21
//

domino_21::domino_21(const size_t hand, const bool squares) :
    domino{ 2,1,hand }
{
    if (!squares) {
        throw("Exception: trying to declare an invalid piece");
    }
    for (size_t i{}; i < length * width; i++) {
        is_there_square[i] = squares;
    }
}

void domino_21::rotate()
{
    if (length < width && handle == 0) {
        handle = 1;
    }
    else if (length < width && handle == 1) {
        handle = 0;
    }
    std::swap(length, width);
}

void domino_21::pick_up(std::vector<std::string>& directions) const
{
    /* 
       R, L, D and U correspond to right, left, down and up, respectively
       directions to other squares from the handle square are pushed back    
    */
    if (length > width && handle == 0) {
        directions.push_back("R");
    }
    else if (length > width && handle == 1) {
        directions.push_back("L");
    }
    else if (length < width && handle == 0) {
        directions.push_back("D");
    }
    else if (length < width && handle == 1) {
        directions.push_back("U");
    }
}

//
// TROMINO_22
//

const std::vector<bool> tromino_22::tromino_L{ true,false,true,true };

tromino_22::tromino_22(const size_t hand, const std::vector<bool>& squares) :
    tromino{ 2,2,hand }
{
    if (squares.size() != length * width) {
        throw("Exception: invalid vector size");
    }
    size_t bool_counter{};
    for (auto squares_iterator = squares.begin(); squares_iterator <
        squares.end(); squares_iterator++) {
        if (*squares_iterator) {
            bool_counter++;
        }
    }
    if (bool_counter != number_of_squares) {
        throw("Exception: trying to declare an invalid piece");
    }
    for (size_t i{}; i < length * width; i++) {
        is_there_square[i] = squares[i];
    }
}

void tromino_22::rotate()
{ 
    std::vector<size_t> order{ 2,0,1,3 }; // of values handle takes
    std::rotate(order.begin(), std::find(order.begin(), order.end(), handle),
        order.end()); // place handle at the beginning of the order vector
    // rotate
    handle = order.at(1); 
    std::swap(is_there_square[order.at(2)], is_there_square[order.at(3)]);
}

void tromino_22::flip()
{
    std::swap(is_there_square[0], is_there_square[1]);
    std::swap(is_there_square[2], is_there_square[3]);
    if (handle % 2 == 0) {
        handle++;
    }
    else {
        handle--;
    }
}

void tromino_22::pick_up(std::vector<std::string>& directions) const
{
    if (handle == 2) {
        directions.push_back("U");
        directions.push_back("R");
    }
    else if (handle == 0) {
        directions.push_back("D");
        directions.push_back("R");
    }
    else if (handle == 1) {
        directions.push_back("D");
        directions.push_back("L");
    }
    else if (handle == 3) {
        directions.push_back("U");
        directions.push_back("L");
    }
}

std::vector<bool> tromino_22::get_construction_vector(const char letter)
{
    if (letter != 'L') {
        throw("Exception: invalid letter.");
    }
    std::vector<bool> construction_vector{ tromino_L };
    return construction_vector;
}

//
// TROMINO_31
//

tromino_31::tromino_31(const size_t hand, const bool squares) :
    tromino{ 3,1,hand }
{
    if (!squares) {
        throw("Exception: trying to declare an invalid piece");
    }
    for (size_t i{}; i < length * width; i++) {
        is_there_square[i] = squares;
    }
}

void tromino_31::rotate()
{
    if (length < width && handle == 0) {
        handle = 2;
    }
    else if (length < width && handle == 2) {
        handle = 0;
    }
    std::swap(length, width);
}

void tromino_31::pick_up(std::vector<std::string>& directions) const
{
    if (length > width && handle == 0) {
        directions.push_back("RR");
        directions.push_back("R");
    }
    else if (length > width && handle == 2) {
        directions.push_back("LL");
        directions.push_back("L");
    }
    else if (length < width && handle == 0) {
        directions.push_back("DD");
        directions.push_back("D");
    }
    else if (length < width && handle == 2) {
        directions.push_back("UU");
        directions.push_back("U");
    }
}

//
// TETROMINO_22
//

tetromino_22::tetromino_22(const size_t hand, const bool squares) :
    tetromino{ 2,2,hand }
{
    if (!squares) {
        throw("Exception: trying to declare an invalid piece");
    }
    for (size_t i{}; i < length * width; i++) {
        is_there_square[i] = squares;
    }
}

void tetromino_22::rotate()
{
    std::vector<size_t> order{ 2,0,1,3 }; // of values handle takes
    std::rotate(order.begin(), std::find(order.begin(), order.end(), handle),
        order.end()); // place handle at the beginning of the order vector
    handle = order.at(1); // rotate
}

void tetromino_22::flip()
{
    if (handle % 2 == 0) {
        handle++;
    }
    else {
        handle--;
    }
}

void tetromino_22::pick_up(std::vector<std::string>& directions) const
{
    if (handle == 2) {
        directions.push_back("U");
        directions.push_back("R");
        directions.push_back("UR");
    }
    else if (handle == 0) {
        directions.push_back("D");
        directions.push_back("R");
        directions.push_back("DR");
    }
    else if (handle == 1) {
        directions.push_back("D");
        directions.push_back("L");
        directions.push_back("DL");
    }
    else if (handle == 3) {
        directions.push_back("U");
        directions.push_back("L");
        directions.push_back("UL");
    }
}

//
// TETROMINO_32
//

const std::vector<bool> tetromino_32::tetromino_L{ 
    true,false,false,true,true,true };
const std::vector<bool> tetromino_32::tetromino_T{ 
    false,true,false,true,true,true };
const std::vector<bool> tetromino_32::tetromino_Z{ 
    false,true,true,true,true,false };

tetromino_32::tetromino_32(const size_t hand,
    const std::vector<bool>& squares) : tetromino{ 3,2,hand }
{
    if (squares.size() != length * width) {
        throw("Exception: invalid vector size");
    }
    size_t bool_counter{};
    for (auto squares_iterator = squares.begin(); squares_iterator <
        squares.end(); squares_iterator++) {
        if (*squares_iterator) {
            bool_counter++;
        }
    }
    if (bool_counter != number_of_squares) {
        throw("Exception: trying to declare an invalid piece");
    }
    for (size_t i{}; i < length * width; i++) {
        is_there_square[i] = squares[i];
    }
}

void tetromino_32::rotate()
{
    bool changed{ false }; // used for updating handle
    size_t divisor{ length };
    std::vector<std::pair<size_t, bool>> before; // piece before rotation
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

void tetromino_32::flip()
{
    if (length > width) {
        std::swap(is_there_square[0], is_there_square[2]);
        std::swap(is_there_square[3], is_there_square[5]);
    }
    else {
        std::swap(is_there_square[0], is_there_square[4]);
        std::swap(is_there_square[1], is_there_square[5]);
    }
}

void tetromino_32::pick_up(std::vector<std::string>& directions) const
{
    // possible directions from handle to all the pieces
    std::vector<std::string> all_directions;
    if (handle == 4) {
        all_directions = { "UL","U","UR","L","","R" };
    }
    else if (handle == 2) {
        all_directions = { "U","UR","","R","D","DR" };
    }
    else if (handle == 1) {
        all_directions = { "L","","R","DL","D","DR" };
    }
    else if (handle == 3) {
        all_directions = { "UL","U","L","","DL","D" };
    }
    else {
        throw("Cannot pick up such a piece.");
    }
    // merge bool information about the existence of squares with directions
    std::vector <std::pair<bool, std::string>> pairs;
    pairs.reserve(length * width);
    for (size_t i{}; i < length * width; i++) {
        if (i != handle) {
            pairs.push_back(std::make_pair(is_there_square[i],
                all_directions.at(i)));
        }
    }
    // find all directions corresponding to existing squares
    std::for_each(pairs.begin(), pairs.end(),
        [&directions](std::pair<bool, std::string> pair) {
            if (pair.first) {
                directions.push_back(pair.second);
            }
        });
}

std::vector<bool> tetromino_32::get_construction_vector(const char letter)
{
    if (letter != 'L' && letter != 'T' && letter != 'Z') {
        throw("Exception: invalid letter.");
    }
    std::vector<bool> construction_vector;
    if (letter == 'L') {
        construction_vector = tetromino_L;
    }
    else if (letter == 'T') {
        construction_vector = tetromino_T;
    }
    else if (letter == 'Z') {
        construction_vector = tetromino_Z;
    }
    return construction_vector;
}

//
// TETROMINO_41
//

tetromino_41::tetromino_41(const size_t hand, const bool squares) :
    tetromino{ 4,1,hand }
{
    if (!squares) {
        throw("Exception: trying to declare an invalid piece");
    }
    for (size_t i{}; i < length * width; i++) {
        is_there_square[i] = squares;
    }
}

void tetromino_41::rotate()
{
    if (length < width && handle == 0) {
        handle = 3;
    }
    else if (length < width && handle == 3) {
        handle = 0;
    }
    std::swap(length, width);
}

void tetromino_41::pick_up(std::vector<std::string>& directions) const
{
    if (length > width && handle == 0) {
        directions.push_back("RRR");
        directions.push_back("RR");
        directions.push_back("R");
    }
    else if (length > width && handle == 3) {
        directions.push_back("LLL");
        directions.push_back("LL");
        directions.push_back("L");
    }
    else if (length < width && handle == 0) {
        directions.push_back("DDD");
        directions.push_back("DD");
        directions.push_back("D");
    }
    else if (length < width && handle == 3) {
        directions.push_back("UUU");
        directions.push_back("UU");
        directions.push_back("U");
    }
}

//
// PENTOMINO_32
//

const std::vector<bool> pentomino_32::pentomino_P{ 
    true,true,false,true,true,true };
const std::vector<bool> pentomino_32::pentomino_U{ 
    true,false,true,true,true,true };

pentomino_32::pentomino_32(const size_t hand,
    const std::vector<bool>& squares) : pentomino{ 3,2,hand }
{
    if (squares.size() != length * width) {
        throw("Exception: invalid vector size");
    }
    size_t bool_counter{};
    for (auto squares_iterator = squares.begin(); squares_iterator <
        squares.end(); squares_iterator++) {
        if (*squares_iterator) {
            bool_counter++;
        }
    }
    if (bool_counter != number_of_squares) {
        throw("Exception: trying to declare an invalid piece");
    }
    for (size_t i{}; i < length * width; i++) {
        is_there_square[i] = squares[i];
    }
}

void pentomino_32::flip()
{
    if (length > width) {
        std::swap(is_there_square[0], is_there_square[2]);
        std::swap(is_there_square[3], is_there_square[5]);
    }
    else {
        std::swap(is_there_square[0], is_there_square[4]);
        std::swap(is_there_square[1], is_there_square[5]);
    }
}

void pentomino_32::pick_up(std::vector<std::string>& directions) const
{
    // possible directions from handle to all the pieces
    std::vector<std::string> all_directions;
    if (handle == 4) {
        all_directions = { "UL","U","UR","L","","R" };
    }
    else if (handle == 2) {
        all_directions = { "U","UR","","R","D","DR" };
    }
    else if (handle == 1) {
        all_directions = { "L","","R","DL","D","DR" };
    }
    else if (handle == 3) {
        all_directions = { "UL","U","L","","DL","D" };
    }
    else {
        throw("Cannot pick up such a piece.");
    }
    // merge bool information about the existence of squares with directions
    std::vector < std::pair<bool, std::string>> pairs;
    pairs.reserve(length * width);
    for (size_t i{}; i < length * width; i++) {
        if (i != handle) {
            pairs.push_back(std::make_pair(is_there_square[i],
                all_directions.at(i)));
        }
    }
    // find all directions corresponding to existing squares
    std::for_each(pairs.begin(), pairs.end(),
        [&directions](std::pair<bool, std::string> pair) {
        if (pair.first) {
            directions.push_back(pair.second);
        }
    });
}

std::vector<bool> pentomino_32::get_construction_vector(const char letter)
{
    if (letter != 'P' && letter != 'U') {
        throw("Exception: invalid letter.");
    }
    std::vector<bool> construction_vector;
    if (letter == 'P') {
        construction_vector = { pentomino_P };
    }
    else if (letter == 'U') {
        construction_vector = { pentomino_U };
    }
    return construction_vector;
}

//
// PENTOMINO_33
//

const std::vector<bool> pentomino_33::pentomino_T{ 
    false,true,false,false,true,false,true,true,true };
const std::vector<bool> pentomino_33::pentomino_V{ 
    true,false,false,true,false,false,true,true,true };
const std::vector<bool> pentomino_33::pentomino_Z{ 
    true,true,false,false,true,false,false,true,true };
const std::vector<bool> pentomino_33::pentomino_W{ 
    true,false,false,true,true,false,false,true,true };
const std::vector<bool> pentomino_33::pentomino_F{ 
    false,true,true,true,true,false,false,true,false };
const std::vector<bool> pentomino_33::pentomino_X{ 
    false,true,false,true,true,true,false,true,false };

pentomino_33::pentomino_33(const size_t hand,
    const std::vector<bool>& squares) : pentomino{ 3,3,hand }
{
    if (squares.size() != length * width) {
        throw("Exception: invalid vector size");
    }
    size_t bool_counter{};
    for (auto squares_iterator = squares.begin(); squares_iterator <
        squares.end(); squares_iterator++) {
        if (*squares_iterator) {
            bool_counter++;
        }
    }
    if (bool_counter != number_of_squares) {
        throw("Exception: trying to declare an invalid piece");
    }
    for (size_t i{}; i < length * width; i++) {
        is_there_square[i] = squares[i];
    }
}

void pentomino_33::flip()
{
    if (handle % 3 == 1) {
        std::swap(is_there_square[0], is_there_square[2]);
        std::swap(is_there_square[3], is_there_square[5]);
        std::swap(is_there_square[6], is_there_square[8]);
    }
    else if (handle > 2 && handle < 6) {
        std::swap(is_there_square[0], is_there_square[6]);
        std::swap(is_there_square[1], is_there_square[7]);
        std::swap(is_there_square[2], is_there_square[8]);
    }
}

void pentomino_33::pick_up(std::vector<std::string>& directions) const
{
    // possible directions from handle to all the pieces
    std::vector<std::string> all_directions;
    if (handle == 7) {
        all_directions = { "UUL","UU","UUR","UL","U","UR","L","","R" };
    }
    else if (handle == 3) {
        all_directions = { "U","UR","URR","","R","RR","D","DR","DRR" };
    }
    else if (handle == 1) {
        all_directions = { "L","","R","DL","D","DR","DDL","DD","DDR" };
    }
    else if (handle == 5) {
        all_directions = { "ULL","UL","U","LL","L","","DLL","DL","D" };
    }
    else {
        throw("Cannot pick up such a piece.");
    }
    // merge bool information about the existence of squares with directions
    std::vector < std::pair<bool, std::string>> pairs;
    pairs.reserve(length * width);
    for (size_t i{}; i < length * width; i++) {
        if (i != handle) {
            pairs.push_back(std::make_pair(is_there_square[i],
                all_directions.at(i)));
        }
    }
    // find all directions corresponding to existing squares
    std::for_each(pairs.begin(), pairs.end(),
        [&directions](std::pair<bool, std::string> pair) {
        if (pair.first) {
            directions.push_back(pair.second);
        }
    });
}

std::vector<bool> pentomino_33::get_construction_vector(const char letter)
{
    if (letter != 'T' && letter != 'V' && letter != 'Z' && letter != 'W' 
        && letter != 'F' && letter != 'X') {
        throw("Exception: invalid letter.");
    }
    std::vector<bool> construction_vector;
    if (letter == 'T') {
        construction_vector = { pentomino_T };
    }
    else if (letter == 'V') {
        construction_vector = { pentomino_V };
    }
    else if (letter == 'Z') {
        construction_vector = { pentomino_Z };
    }
    else if (letter == 'W') {
        construction_vector = { pentomino_W };
    }
    else if (letter == 'F') {
        construction_vector = { pentomino_F };
    }
    else if (letter == 'X') {
        construction_vector = { pentomino_X };
    }
    return construction_vector;
}

//
// PENTOMINO_42
//

const std::vector<bool> pentomino_42::pentomino_L{ 
    true,false,false,false,true,true,true,true };
const std::vector<bool> pentomino_42::pentomino_Y{ 
    false,true,false,false,true,true,true,true };
const std::vector<bool> pentomino_42::pentomino_N{ 
    false,true,true,true,true,true,false,false };

pentomino_42::pentomino_42(const size_t hand,
    const std::vector<bool>& squares) : pentomino{ 4,2,hand }
{
    if (squares.size() != length * width) {
        throw("Exception: invalid vector size");
    }
    size_t bool_counter{};
    for (auto squares_iterator = squares.begin(); squares_iterator <
        squares.end(); squares_iterator++) {
        if (*squares_iterator) {
            bool_counter++;
        }
    }
    if (bool_counter != number_of_squares) {
        throw("Exception: trying to declare an invalid piece");
    }
    for (size_t i{}; i < length * width; i++) {
        is_there_square[i] = squares[i];
    }
}

void pentomino_42::flip()
{
    // pairs of positions to be flipped
    std::vector<std::pair<size_t, size_t>> pairs; 
    if (length > width) {
        pairs = { {0,3},{1,2},{4,7},{5,6} };
    } 
    else {
        pairs = { {0,6},{1,7},{2,4},{3,5} };
    }
    // flip and update handle
    for (auto pairs_iterator = pairs.begin(); pairs_iterator < pairs.end();
        pairs_iterator++) {
        std::swap(is_there_square[(*pairs_iterator).first],
            is_there_square[(*pairs_iterator).second]);
        if ((*pairs_iterator).first == handle) {
            handle = (*pairs_iterator).second;
        }
        else if ((*pairs_iterator).second == handle) {
            handle = (*pairs_iterator).first;
        }
    } 
}


void pentomino_42::pick_up(std::vector<std::string>& directions) const
{
    // possible directions from handle to all the pieces
    std::vector<std::string> all_directions;
    if (length > width && handle == 5) {
        all_directions = { "UL","U","UR","URR","L","","R","RR" };
    }
    else if (length > width && handle == 6) {
        all_directions = { "ULL","UL","U","UR","LL","L","","R" };
    }
    else if (length > width && handle == 1) {
        all_directions = { "L","","R","RR","DL","D","DR","DRR" };
    }
    else if (length > width && handle == 2) {
        all_directions = { "LL","L","","R","DLL","DL","D","DR" };
    }
    else if (length < width && handle == 2) {
        all_directions = { "U","UR","","R","D","DR","DD","DDR" };
    }
    else if (length < width && handle == 4) {
        all_directions = { "UU","UUR","U","UR","","R","D","DR" };
    }
    else if (length < width && handle == 3) {
        all_directions = { "UL","U","L","","DL","D","DDL","DD" };
    }
    else if (length < width && handle == 5) {
        all_directions = { "UUL","UU","UL","U","L","","DL","D" };
    }
    else {
        throw("Cannot pick up such a piece.");
    }
    // merge bool information about the existence of squares with directions
    std::vector < std::pair<bool, std::string>> pairs;
    pairs.reserve(length * width);
    for (size_t i{}; i < length * width; i++) {
        if (i != handle) {
            pairs.push_back(std::make_pair(is_there_square[i],
                all_directions.at(i)));
        }
    }
    // find all directions corresponding to existing squares
    std::for_each(pairs.begin(), pairs.end(),
        [&directions](std::pair<bool, std::string> pair) {
        if (pair.first) {
            directions.push_back(pair.second);
        }
    });
}

std::vector<bool> pentomino_42::get_construction_vector(const char letter)
{
    if (letter != 'L' && letter != 'Y' && letter != 'N') {
        throw("Exception: invalid letter.");
    }
    std::vector<bool> construction_vector;
    if (letter == 'L') {
        construction_vector = { pentomino_L };
    }
    else if (letter == 'Y') {
        construction_vector = { pentomino_Y };
    }
    else if (letter == 'N') {
        construction_vector = { pentomino_N };
    }
    return construction_vector;
}

//
// PENTOMINO_51
//

pentomino_51::pentomino_51(const size_t hand, const bool squares) :
    pentomino{ 5,1,hand }
{
    if (!squares) {
        throw("Exception: trying to declare an invalid piece");
    }
    for (size_t i{}; i < length * width; i++) {
        is_there_square[i] = squares;
    }
}

void pentomino_51::rotate()
{
    if (length < width && handle == 0) {
        handle = 4;
    }
    else if (length < width && handle == 4) {
        handle = 0;
    }
    std::swap(length, width);
}

void pentomino_51::pick_up(std::vector<std::string>& directions) const
{
    if (length > width && handle == 0) {
        directions.push_back("RRRR");
        directions.push_back("RRR");
        directions.push_back("RR");
        directions.push_back("R");
    }
    else if (length > width && handle == 4) {
        directions.push_back("LLLL");
        directions.push_back("LLL");
        directions.push_back("LL");
        directions.push_back("L");
    }
    else if (length < width && handle == 0) {
        directions.push_back("DDDD");
        directions.push_back("DDD");
        directions.push_back("DD");
        directions.push_back("D");
    }
    else if (length < width && handle == 4) {
        directions.push_back("UUUU");
        directions.push_back("UUU");
        directions.push_back("UU");
        directions.push_back("U");
    }
}