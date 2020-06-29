#ifndef BOARD_H
#define BOARD_H

#include"players_set.h"


class board
{
private:
	size_t size; // one-dimensional length of the board
	size_t number_of_players; // initial
	std::vector<players_set> players;
	std::unique_ptr<std::string[]> board_colours;
	static const std::vector<char> letters; // first 20 letter of the alphabet
	static const std::vector<std::string> possible_colours; // for players
public:
	board(); // there is only one way to set up the board
	size_t get_size() const;
	size_t get_number_of_players_left() const;
	players_set get_player(const size_t player_number) const;
	size_t get_players_score(const size_t player_number) const;
	std::string get_players_colour(const size_t player_number) const;
	size_t convert_input_to_position(const char board_letter,
		const size_t board_number) const;
	bool check_board_square(const size_t player_number,
		const size_t position) const; // and adjacent squares
	bool check_diagonally(const size_t player_number,
		const size_t position) const; // squares diagonally wrt position
	// is used from the second round onward
	bool place_piece(const size_t player_number, const size_t piece_number, 
		const size_t position, const bool test, const bool players_test);
	bool place_first_piece(const size_t player_number,
		const size_t piece_number); // in the first round
	void print_piece_menu(const bool capital) const;
	void print_option_menu(const bool capital) const;
	void print_place_menu(const bool capital) const;
	void erase_text(const size_t x, const size_t y) const;
	void take_turn(const size_t player_number, const bool first);
	bool find_available_moves(const size_t player_number,
		const size_t piece_number, const bool players_test);
	bool check_if_can_place(const size_t player_number); // any piece
	void remove_player(const size_t player_number); // when they lose
	void display() const; // the board
};

#endif