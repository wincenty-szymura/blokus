#ifndef PLAYERS_SET_H
#define PLAYERS_SET_H

#include"specific_pieces.h"

// class containing all the pieces still in possession of a player
class players_set 
{
private:
	std::string colour;
	std::vector<std::shared_ptr<piece>> set_of_pieces;
    // vectors holding console coordinates used for displaying the set
    std::vector<std::pair<size_t, size_t>> coordinates_horizontally;
    std::vector<std::pair<size_t, size_t>> coordinates_vertically;
public:
    players_set() {}
    players_set(const std::string players_colour);
    ~players_set() {}
    std::string get_colour() const;
    size_t get_number_of_pieces() const;
    std::shared_ptr<piece> get_piece(const size_t piece_number) const; 
    //  remove after being placed on the board
    void remove_piece(const size_t piece_number); 
    void display() const; // the entire set of pieces
    // erase the image of the piece from the console window
    void erase_piece(const size_t piece_number) const; 
    // display the image of the piecec on the console window
    void display_piece(const size_t piece_number) const; 
};

#endif