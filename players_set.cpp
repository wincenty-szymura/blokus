#include"players_set.h"

players_set::players_set(const std::string players_colour)
{
	colour = players_colour;
	// create a vector with all the 21 pieces
	set_of_pieces.reserve(21);
	set_of_pieces.push_back(std::make_shared <tetromino_22>(2, true));
	set_of_pieces.push_back(std::make_shared <tetromino_32>(4, 
		tetromino_32::get_construction_vector('Z')));
	set_of_pieces.push_back(std::make_shared <tetromino_32>(4, 
		tetromino_32::get_construction_vector('L')));
	set_of_pieces.push_back(std::make_shared <pentomino_51>(0, true));
	set_of_pieces.push_back(std::make_shared <monomino_11>(0, true));
	set_of_pieces.push_back(std::make_shared <tetromino_32>(4, 
		tetromino_32::get_construction_vector('T')));
	set_of_pieces.push_back(std::make_shared <pentomino_32>(4, 
		pentomino_32::get_construction_vector('U')));
	set_of_pieces.push_back(std::make_shared <pentomino_33>(7, 
		pentomino_33::get_construction_vector('T')));
	set_of_pieces.push_back(std::make_shared <pentomino_33>(7, 
		pentomino_33::get_construction_vector('Z')));
	set_of_pieces.push_back(std::make_shared <pentomino_33>(7, 
		pentomino_33::get_construction_vector('V')));
	set_of_pieces.push_back(std::make_shared <tromino_31>(0, true));
	set_of_pieces.push_back(std::make_shared <pentomino_42>(5, 
		pentomino_42::get_construction_vector('Y')));
	set_of_pieces.push_back(std::make_shared <pentomino_42>(5, 
		pentomino_42::get_construction_vector('L')));
	set_of_pieces.push_back(std::make_shared <domino_21>(0, true));
	set_of_pieces.push_back(std::make_shared <tetromino_41>(0, true));
	set_of_pieces.push_back(std::make_shared <pentomino_33>(7, 
		pentomino_33::get_construction_vector('W')));
	set_of_pieces.push_back(std::make_shared <pentomino_32>(4, 
		pentomino_32::get_construction_vector('P')));
	set_of_pieces.push_back(std::make_shared <pentomino_42>(5, 
		pentomino_42::get_construction_vector('N')));
	set_of_pieces.push_back(std::make_shared <pentomino_33>(7, 
		pentomino_33::get_construction_vector('X')));
	set_of_pieces.push_back(std::make_shared <tromino_22>(2, 
		tromino_22::get_construction_vector('L')));
	set_of_pieces.push_back(std::make_shared <pentomino_33>(7, 
		pentomino_33::get_construction_vector('F')));
	// populate the coordinate vectors
	coordinates_horizontally.reserve(21);
	coordinates_horizontally.push_back(std::make_pair(110, 19));
	coordinates_horizontally.push_back(std::make_pair(125, 19));
	coordinates_horizontally.push_back(std::make_pair(145, 21));
	coordinates_horizontally.push_back(std::make_pair(165, 23));
	coordinates_horizontally.push_back(std::make_pair(185, 19));
	coordinates_horizontally.push_back(std::make_pair(195, 21));
	coordinates_horizontally.push_back(std::make_pair(110, 25));
	coordinates_horizontally.push_back(std::make_pair(145, 27));
	coordinates_horizontally.push_back(std::make_pair(175, 27));
	coordinates_horizontally.push_back(std::make_pair(195, 27));
	coordinates_horizontally.push_back(std::make_pair(110, 39));
	coordinates_horizontally.push_back(std::make_pair(120, 33));
	coordinates_horizontally.push_back(std::make_pair(145, 35));
	coordinates_horizontally.push_back(std::make_pair(170, 39));
	coordinates_horizontally.push_back(std::make_pair(170, 35));
	coordinates_horizontally.push_back(std::make_pair(195, 35));
	coordinates_horizontally.push_back(std::make_pair(115, 43));
	coordinates_horizontally.push_back(std::make_pair(135, 45));
	coordinates_horizontally.push_back(std::make_pair(160, 43));
	coordinates_horizontally.push_back(std::make_pair(180, 45));
	coordinates_horizontally.push_back(std::make_pair(195, 43));
	coordinates_vertically.reserve(21);
	coordinates_vertically.push_back(std::make_pair(110, 19));
	coordinates_vertically.push_back(std::make_pair(130, 19));
	coordinates_vertically.push_back(std::make_pair(145, 19));
	coordinates_vertically.push_back(std::make_pair(165, 23));
	coordinates_vertically.push_back(std::make_pair(185, 19));
	coordinates_vertically.push_back(std::make_pair(200, 19));
	coordinates_vertically.push_back(std::make_pair(110, 25));
	coordinates_vertically.push_back(std::make_pair(145, 27));
	coordinates_vertically.push_back(std::make_pair(175, 27));
	coordinates_vertically.push_back(std::make_pair(195, 27));
	coordinates_vertically.push_back(std::make_pair(110, 35));
	coordinates_vertically.push_back(std::make_pair(130, 29));
	coordinates_vertically.push_back(std::make_pair(150, 35));
	coordinates_vertically.push_back(std::make_pair(175, 39));
	coordinates_vertically.push_back(std::make_pair(185, 35));
	coordinates_vertically.push_back(std::make_pair(195, 35));
	coordinates_vertically.push_back(std::make_pair(120, 43));
	coordinates_vertically.push_back(std::make_pair(135, 41));
	coordinates_vertically.push_back(std::make_pair(160, 43));
	coordinates_vertically.push_back(std::make_pair(180, 45));
	coordinates_vertically.push_back(std::make_pair(195, 43));
}

std::string players_set::get_colour() const
{
	return colour;
}

size_t players_set::get_number_of_pieces() const
{
	return set_of_pieces.size();
}

std::shared_ptr<piece> players_set::get_piece(const size_t piece_number) const
{ 
	// piece number varies between 1 and 21
	return set_of_pieces[piece_number - 1];
}

void players_set::remove_piece(const size_t piece_number)
{
	erase_piece(piece_number);
	set_of_pieces.erase(set_of_pieces.begin() + piece_number - 1);
	// erase coordinates of the piece together with the piece
	coordinates_horizontally.erase(coordinates_horizontally.begin()
		+ piece_number - 1);
	coordinates_vertically.erase(coordinates_vertically.begin()
		+ piece_number - 1);
}

void players_set::display() const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// clear the piece area of the console window
	SetConsoleTextAttribute(hConsole, 15); // black background, white text
	for (size_t i{}; i < 30; i++) {
		go_to_console_position(110, 19 + i);
		for (size_t j{}; j < 100; j++) {
			std::cout << " ";
		}
	}
	for (size_t i{ 1 }; i <= set_of_pieces.size(); i++) {
		display_piece(i); // takes numbers between 1 and 21
	}
}

void players_set::erase_piece(const size_t piece_number) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15); // black background, white text
	size_t piece_length{ set_of_pieces.at(piece_number - 1)->get_length() };
	size_t piece_width{ set_of_pieces.at(piece_number - 1)->get_width() };
	if (piece_width >= piece_length) { // if positioned vertically
		for (size_t i{}; i < piece_width; i++) {
			for (size_t j{}; j < piece_length; j++) {
				bottom::draw_square(coordinates_vertically.at(piece_number - 1)
					.first + 5 * j, coordinates_vertically.at(piece_number - 1)
					.second + 2 * i);
			}
		}
	}
	else { // if positioned horizontally
		for (size_t i{}; i < piece_width; i++) {
			for (size_t j{}; j < piece_length; j++) {
				bottom::draw_square(coordinates_horizontally.at(piece_number - 1)
					.first + 5 * j, coordinates_horizontally.at(piece_number - 1)
					.second + 2 * i);
			}
		}
	}
}

void players_set::display_piece(const size_t piece_number) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	if (colour == "yellow") {
		SetConsoleTextAttribute(hConsole, 224); // yellow background, black text
	}
	else if (colour == "blue") {
		SetConsoleTextAttribute(hConsole, 144); // blue background, black text
	}
	else if (colour == "red") {
		SetConsoleTextAttribute(hConsole, 192); // red background, black text
	}
	else if (colour == "green") {
		SetConsoleTextAttribute(hConsole, 160); // green background, black text
	}
	size_t piece_length{ set_of_pieces.at(piece_number - 1)->get_length() };
	size_t piece_width{ set_of_pieces.at(piece_number - 1)->get_width() };
	if (piece_length >= piece_width) { // if positioned horizontally
		set_of_pieces.at(piece_number - 1)->display(coordinates_horizontally
			.at(piece_number - 1).first, coordinates_horizontally
			.at(piece_number - 1).second, piece_number);
	}
	else { // if positioned vertically
		set_of_pieces.at(piece_number - 1)->display(coordinates_vertically
			.at(piece_number - 1).first, coordinates_vertically
			.at(piece_number - 1).second, piece_number);
	}
	SetConsoleTextAttribute(hConsole, 15); // black background, white text
}

