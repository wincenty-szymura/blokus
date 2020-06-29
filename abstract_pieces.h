#ifndef ABSTRACT_PIECES_H
#define ABSTRACT_PIECES_H

#include"graphics_functions.h"

class piece // abstract parent class
{
protected:
    /*
       the piece is defined as a rectangle of dimensions just big enough
       to enclose the piece and an array of bools specifying positions of
       squares making up the piece within that rectangle
    */
    size_t number_of_squares;
    size_t length; // the horizontal dimension of the piece
    size_t width; // the vertical dimension of the piece
    size_t handle; // defines which square is used to place the piece on board
    /*
       length and width are swapped when the piece is rotated
       length is not necessarily bigger than width
       all the pieces in the game are initialized with length bigger than width
    */
    std::unique_ptr<bool[]> is_there_square;
public:
    piece();
    piece(const size_t squares, const size_t l, const size_t w, 
        const size_t hand);
    piece(const piece&); // copy constructor
    piece(piece&&) noexcept; // move constructor
    virtual ~piece() {}
    piece& operator=(const piece&); //copy assignment
    piece& operator=(piece&&) noexcept; //move assignment
    // access an is_there_square element
    bool& operator()(const size_t m, const size_t n) const;
    size_t get_number_of_squares() const;
    size_t get_length() const;
    size_t get_width() const;
    size_t get_handle() const;
    virtual void rotate() = 0;
    virtual void flip() = 0;
    virtual void pick_up(std::vector<std::string>& directions) const = 0;
    void display(const size_t x_left, const size_t y_top, 
        const size_t signature) const; 
    //x_left and y_top define corner of rectangle the piece can be fitted into
};

class monomino : public piece // derived abstract class - one-square piece
{
public:
    monomino() : piece{ 1,1,1,0 } {}
    monomino(const size_t l, const size_t w, const size_t hand) :
        piece{ 1,l,w,hand } {}
    monomino(const monomino& copied_monomino) : piece(copied_monomino) {}
    monomino(monomino&& moved_monomino) noexcept : 
        piece(std::move(moved_monomino)) {}
    virtual ~monomino() {}
};

class domino : public piece // derived abstract class - two-square piece
{
public:
    domino() : piece{ 2,2,1,0 } {}
    domino(const size_t l, const size_t w, const size_t hand) :
        piece{ 2,l,w,hand } {}
    domino(const domino& copied_domino) : piece(copied_domino) {}
    domino(domino&& moved_domino) noexcept : piece(std::move(moved_domino)) {}
    virtual ~domino() {}
};

class tromino : public piece // derived abstract class - three square piece
{
public:
    tromino() : piece{ 3,3,2,0 } {}
    tromino(const size_t l, const size_t w, const size_t hand) :
        piece{ 3,l,w,hand } {}
    tromino(const tromino& copied_tromino) : piece(copied_tromino) {}
    tromino(tromino&& moved_tromino) noexcept :
        piece(std::move(moved_tromino)) {}
    virtual ~tromino() {}
};

class tetromino : public piece // derived abstract class - four square piece
{
public:
    tetromino() : piece{ 4,4,2,0 } {}
    tetromino(const size_t l, const size_t w, const size_t hand) :
        piece{ 4,l,w,hand } {}
    tetromino(const tetromino& copied_tetromino) : piece(copied_tetromino) {}
    tetromino(tetromino&& moved_tetromino) noexcept :
        piece(std::move(moved_tetromino)) {}
    virtual ~tetromino() {}
};

class pentomino : public piece // derived abstract class - five square piece
{
public:
    pentomino() : piece{ 5,5,3,0 } {}
    pentomino(const size_t l, const size_t w, const size_t hand) :
        piece{ 5,l,w,hand } {}
    pentomino(const pentomino& copied_pentomino) : piece(copied_pentomino) {}
    pentomino(pentomino&& moved_pentomino) noexcept :
        piece(std::move(moved_pentomino)) {}
    virtual ~pentomino() {}
    virtual void rotate();
};

#endif