#ifndef SPECIFIC_PIECES_H
#define SPECIFIC_PIECES_H

#include"abstract_pieces.h"

// digits after the underscore correspond to initial length and width 
class monomino_11 : public monomino
{
public:
    monomino_11() : monomino{ 1,1,0 } {}
    monomino_11(const size_t hand, const bool square);
    monomino_11(const monomino_11& copied_monomino_11) :
        monomino(copied_monomino_11) {}
    monomino_11(monomino_11&& moved_monomino_11) noexcept :
        monomino(std::move(moved_monomino_11)) {}
    ~monomino_11() {}
    void rotate() {}
    void flip() {}
    void pick_up(std::vector<std::string>& directions) const {}
};

class domino_21 : public domino
{
public:
    domino_21() : domino{ 2,1,0 } {}
    domino_21(const size_t hand, const bool squares);
    domino_21(const domino_21& copied_domino_21) : domino(copied_domino_21) {}
    domino_21(domino_21&& moved_domino_21) noexcept :
        domino(std::move(moved_domino_21)) {}
    ~domino_21() {}
    void rotate();
    void flip() {}
    void pick_up(std::vector<std::string>& directions) const;
};

class tromino_22 : public tromino
{
private:
    // suggested input to the parametrized constructor
    static const std::vector<bool> tromino_L;
public:
    tromino_22() : tromino{ 2,2,0 } {}
    tromino_22(const size_t hand, const std::vector<bool>& squares);
    tromino_22(const tromino_22& copied_tromino_22) :
        tromino(copied_tromino_22) {}
    tromino_22(tromino_22&& moved_tromino_22) noexcept :
        tromino(std::move(moved_tromino_22)) {}
    ~tromino_22() {}
    void rotate();
    void flip();
    void pick_up(std::vector<std::string>& directions) const;
    static std::vector<bool> get_construction_vector(const char letter);
};

class tromino_31 : public tromino
{
public:
    tromino_31() : tromino{ 3,1,0 } {}
    tromino_31(const size_t hand, const bool squares);
    tromino_31(const tromino_31& copied_tromino_31) :
        tromino(copied_tromino_31) {}
    tromino_31(tromino_31&& moved_tromino_31) noexcept :
        tromino(std::move(moved_tromino_31)) {}
    ~tromino_31() {}
    void rotate();
    void flip() {}
    void pick_up(std::vector<std::string>& directions) const;
};

class tetromino_22 : public tetromino
{
public:
    tetromino_22() : tetromino{ 2,2,0 } {}
    tetromino_22(const size_t hand, const bool squares);
    tetromino_22(const tetromino_22& copied_tetromino_22) :
        tetromino(copied_tetromino_22) {}
    tetromino_22(tetromino_22&& moved_tetromino_22) noexcept :
        tetromino(std::move(moved_tetromino_22)) {}
    ~tetromino_22() {}
    void rotate();
    void flip();
    void pick_up(std::vector<std::string>& directions) const;
};

class tetromino_32 : public tetromino
{
private:
    // suggested inputs to the parametrized constructor
    static const std::vector<bool> tetromino_L;
    static const std::vector<bool> tetromino_T;
    static const std::vector<bool> tetromino_Z;
public:
    tetromino_32() : tetromino{ 3,2,0 } {}
    tetromino_32(const size_t hand, const std::vector<bool>& squares);
    tetromino_32(const tetromino_32& copied_tetromino_32) :
        tetromino(copied_tetromino_32) {}
    tetromino_32(tetromino_32&& moved_tetromino_32) noexcept :
        tetromino(std::move(moved_tetromino_32)) {}
    ~tetromino_32() {}
    void rotate();
    void flip();
    void pick_up(std::vector<std::string>& directions) const;
    static std::vector<bool> get_construction_vector(const char letter);
};

class tetromino_41 : public tetromino
{
public:
    tetromino_41() : tetromino{ 4,1,0 } {}
    tetromino_41(const size_t hand, const bool squares);
    tetromino_41(const tetromino_41& copied_tetromino_41) :
        tetromino(copied_tetromino_41) {}
    tetromino_41(tetromino_41&& moved_tetromino_41) noexcept :
        tetromino(std::move(moved_tetromino_41)) {}
    ~tetromino_41() {}
    void rotate();
    void flip() {}
    void pick_up(std::vector<std::string>& directions) const;
};

class pentomino_32 : public pentomino
{
private:
    // suggested inputs to the parametrized constructor
    static const std::vector<bool> pentomino_P;
    static const std::vector<bool> pentomino_U;
public:
    pentomino_32() : pentomino{ 3,2,0 } {}
    pentomino_32(const size_t hand, const std::vector<bool>& squares);
    pentomino_32(const pentomino_32& copied_pentomino_32) :
        pentomino(copied_pentomino_32) {}
    pentomino_32(pentomino_32&& moved_pentomino_32) noexcept :
        pentomino(std::move(moved_pentomino_32)) {}
    ~pentomino_32() {}
    void flip();
    void pick_up(std::vector<std::string>& directions) const;
    static std::vector<bool> get_construction_vector(const char letter);
};

class pentomino_33 : public pentomino
{
private:
    // suggested inputs to the parametrized constructor
    static const std::vector<bool> pentomino_T;
    static const std::vector<bool> pentomino_V;
    static const std::vector<bool> pentomino_Z;
    static const std::vector<bool> pentomino_W;
    static const std::vector<bool> pentomino_F;
    static const std::vector<bool> pentomino_X;
public:
    pentomino_33() : pentomino{ 3,3,0 } {}
    pentomino_33(const size_t hand, const std::vector<bool>& squares);
    pentomino_33(const pentomino_33& copied_pentomino_33) :
        pentomino(copied_pentomino_33) {}
    pentomino_33(pentomino_33&& moved_pentomino_33) noexcept :
        pentomino(std::move(moved_pentomino_33)) {}
    ~pentomino_33() {}
    void flip();
    void pick_up(std::vector<std::string>& directions) const;
    static std::vector<bool> get_construction_vector(const char letter);
};

class pentomino_42 : public pentomino
{
private:
    // suggested inputs to the parametrized constructor
    static const std::vector<bool> pentomino_L;
    static const std::vector<bool> pentomino_Y;
    static const std::vector<bool> pentomino_N;
public:
    pentomino_42() : pentomino{ 4,2,0 } {}
    pentomino_42(const size_t hand, const std::vector<bool>& squares);
    pentomino_42(const pentomino_42& copied_pentomino_42) :
        pentomino(copied_pentomino_42) {}
    pentomino_42(pentomino_42&& moved_pentomino_42) noexcept :
        pentomino(std::move(moved_pentomino_42)) {}
    ~pentomino_42() {}
    void flip();
    void pick_up(std::vector<std::string>& directions) const;
    static std::vector<bool> get_construction_vector(const char letter);
};

class pentomino_51 : public pentomino
{
public:
    pentomino_51() : pentomino{ 5,1,0 } {}
    pentomino_51(const size_t hand, const bool squares);
    pentomino_51(const pentomino_51& copied_pentomino_51) :
        pentomino(copied_pentomino_51) {}
    pentomino_51(pentomino_51&& moved_pentomino_51) noexcept :
        pentomino(std::move(moved_pentomino_51)) {}
    ~pentomino_51() {}
    void rotate();
    void flip() {}
    void pick_up(std::vector<std::string>& directions) const;
};

#endif