#include"board.h"

const std::vector<char> board::letters{ 'A','B','C','D','E','F','G','H','I',
	'J','K','L','M','N','O','P','Q','R','S','T' };
const std::vector<std::string> board::possible_colours{ "yellow","blue","red",
	"green" };

board::board()
{
	size = 20;
	number_of_players = 4;
	// reserve space for four players on the players vector
	players.reserve(4); // makes the program faster
	board_colours = std::make_unique<std::string[]>(size * size);
	for (size_t i{}; i < size * size; i++) {
		board_colours[i] = "white"; // initially the entire board is white
	}
	for (size_t i{}; i < number_of_players; i++) {
		players.push_back(players_set{ possible_colours.at(i) });
	}
}


size_t board::get_size() const
{
	return size;
}

size_t board::get_number_of_players_left() const
{
	return players.size();
}

players_set board::get_player(const size_t player_number) const
{
	return players[player_number];
}

size_t board::get_players_score(const size_t player_number) const
{
	size_t score{ 0 };
	for (size_t i{ 1 }; i <= players[player_number].get_number_of_pieces();
		i++) { // the score is the sum of all the squares player has left
		score += players[player_number].get_piece(i)->get_number_of_squares();
	}
	return score;
}

std::string board::get_players_colour(const size_t player_number) const
{
	return players[player_number].get_colour();
}

size_t board::convert_input_to_position(const char board_letter,
	const size_t board_number) const
{
	if (std::find(letters.begin(), letters.end(),
		board_letter) == letters.end()) {
		throw ("Invalid letter.");
	}
	else if (board_number < 1 || board_number > 20) {
		throw ("Invalid number.");
	}
	// find the board position associated with the input
	auto iterator{ std::find(letters.begin(), letters.end(),board_letter) };
	int index{ std::distance(letters.begin(),iterator) }; // always positive
	size_t position{ static_cast<size_t>(size * index + board_number - 1) };
	return position;
}

bool board::check_board_square(const size_t player_number,
	const size_t position) const
{
	std::vector<std::string> colours_adjacent;
	colours_adjacent.reserve(4);
	// check if pieces at the adjacent positions exist before accessing them
	if (position > 19) {
		colours_adjacent.push_back(board_colours[position - 20]);
	}
	if (position % 20 != 0) {
		colours_adjacent.push_back(board_colours[position - 1]);
	}
	if (position < 380) {
		colours_adjacent.push_back(board_colours[position + 20]);
	}
	if (position % 20 != 19) {
		colours_adjacent.push_back(board_colours[position + 1]);
	}
	bool adjacent{ false };
	std::string players_colour{ players[player_number].get_colour() };
	if (board_colours[position] == "white" && std::find(colours_adjacent.begin(),
		colours_adjacent.end(), players_colour) == colours_adjacent.end()) {
		/*
           if the square is white and adjacent squares have colours different
		   that player's colour
        */ 
		adjacent = true;
	}
	return adjacent;
}

bool board::check_diagonally(const size_t player_number,
	const size_t position) const
{
	std::vector<std::string> colours_diagonally;
	colours_diagonally.reserve(4);
	// check if pieces at the adjacent positions exist before accessing them
	if (position > 19 && position % 20 != 0) {
		colours_diagonally.push_back(board_colours[position - 21]);
	}
	if (position > 19 && position % 20 != 19) {
		colours_diagonally.push_back(board_colours[position - 19]);
	}
	if (position < 380 && position % 20 != 0) {
		colours_diagonally.push_back(board_colours[position + 19]);
	}
	if (position < 380 && position % 20 != 19) {
		colours_diagonally.push_back(board_colours[position + 21]);
	}
	bool diagonally{ false };
	std::string players_colour{ players[player_number].get_colour() };
	if (std::find(colours_diagonally.begin(), colours_diagonally.end(),
		players_colour) != colours_diagonally.end()) {
		/*
           if at least one of the squares touching corners with the square has 
           the same colour as the player
        */
		diagonally = true;
	}
	return diagonally;
}

bool board::place_piece(const size_t player_number, const size_t piece_number,
	const size_t position, const bool test, const bool players_test)
{
	size_t current_position{ position }; // start at the handle
	std::vector<size_t> positions;
	size_t squares_diagonally{}; // to check the diagonal condition
	bool is_placed{ false };
	if (check_board_square(player_number, current_position)) {
		positions.push_back(current_position);
		if (check_diagonally(player_number, current_position)) {
			squares_diagonally++; 
		}
	   	std::shared_ptr<piece> used_piece{ players[player_number]
			.get_piece(piece_number) };
		std::vector<std::string> board_directions;
		// pass the directions on the piece to the vector
		used_piece->pick_up(board_directions);
		if (!board_directions.empty()) { // if not monomino_11 object
			// change the current_position value
			for (auto vector_iterator = board_directions.begin();
				vector_iterator < board_directions.end(); vector_iterator++) {
				for (auto string_iterator = (*vector_iterator).begin(); 
					string_iterator < (*vector_iterator).end();
					string_iterator++) { // access single letters
					if ((*string_iterator) == 'U') {
						if (current_position < 20) {
							// cannot go up if smaller than 20
							goto failed;
						}
						current_position -= 20;
					}
					else if ((*string_iterator) == 'D') {
						if (current_position > 379) {
							// cannot go down if bigger than 379
							goto failed;
						}
						current_position += 20;
					}
					else if ((*string_iterator) == 'L') {
						if (current_position % 20 == 0) {
							// cannot go left if at the left edge of the board 
							goto failed;
						}
						current_position -= 1;
					}
					else {
						if (current_position % 20 == 19) {
							// cannot go right if at the right edge of the board 
							goto failed;
						}
						current_position += 1;
					}
				}
				if (check_board_square(player_number, current_position)) {
					positions.push_back(current_position);
					if (check_diagonally(player_number, current_position)) {
						squares_diagonally++;
					}
				}
				else {
					goto failed;
				}
				current_position = position; // go back to the handle
			}
		}
		// only one positive return from the check_diagonally function is needed
		if (squares_diagonally > 0) {
			if (test) { // if using find_available moves function
				if (players_test) { // if not using check_if_can_place function
					for (auto positions_iterator = positions.begin();
						positions_iterator < positions.end(); 
						positions_iterator++) {
						board_colours[*positions_iterator] = "grey";
					}
					display(); // show an available position for the piece
					go_to_console_position(139, 6);
					system("pause"); // wait for the player
					for (auto positions_iterator = positions.begin();
						positions_iterator < positions.end(); 
						positions_iterator++) {
						board_colours[*positions_iterator] = "white";
					}
					display(); // hide the available position for the piece
					erase_text(139, 6);
				}
			}
			else { // if placing a piece
				for (auto positions_iterator = positions.begin();
					positions_iterator < positions.end(); positions_iterator++) {
					board_colours[*positions_iterator] = players[player_number]
						.get_colour(); // change colour of board squares
				}
				display(); // show the board with the piece on it
				// remove the piece from player's set
				players[player_number].remove_piece(piece_number); 
			}
			is_placed = true;
		}
	}
	failed:
	return is_placed;
}

bool board::place_first_piece(const size_t player_number,
	const size_t piece_number)
{
	std::shared_ptr<piece> used_piece{ players[player_number]
		.get_piece(piece_number) };
	bool is_started{ false };
	/*
	   in the first round pieces need to be placed in the corners of the board,
	   mathematically, this results in a different condition for each corner
	 */
	if (player_number == 0 && (*used_piece)(1, 1) == true) {
		for (size_t i{}; i < used_piece->get_width(); i++) {
			for (size_t j{}; j < used_piece->get_length(); j++) {
				if ((*used_piece)(i + 1, j + 1) == true) {
					board_colours[j + size * i] = players[player_number]
						.get_colour(); // change colour of board squares
				}
			} 
		}
		is_started = true;
	}
	if (player_number == 1 
		&& (*used_piece)(1, used_piece->get_length()) == true) {
		for (size_t i{}; i < used_piece->get_width(); i++) {
			for (size_t j{}; j < used_piece->get_length(); j++) {
				if ((*used_piece)(i + 1, j + 1) == true) {
					// change colour of board squares
					board_colours[size - used_piece->get_length() + j + size
						* i] = players[player_number].get_colour();
				}
			}
		}
		is_started = true;
	}
	if (player_number == 2 && (*used_piece)(used_piece->get_width(),
		used_piece->get_length()) == true) {
		for (size_t i{}; i < used_piece->get_width(); i++) {
			for (size_t j{}; j < used_piece->get_length(); j++) {
				if ((*used_piece)(i + 1, j + 1) == true) {
					// change colour of board squares
					board_colours[size * (size + 1 + i - used_piece
						->get_width()) - used_piece->get_length() + j]
						= players[player_number].get_colour();
				}
			}
		}
		is_started = true;
	}
	if (player_number == 3 
		&& (*used_piece)(used_piece->get_width(),1) == true) {
		for (size_t i{}; i < used_piece->get_width(); i++) {
			for (size_t j{}; j < used_piece->get_length(); j++) {
				if ((*used_piece)(i + 1, j + 1) == true) {
					// change colour of board squares
					board_colours[size * (size + i - used_piece->get_width())
						+ j] = players[player_number].get_colour();
				}
			}
		}
		is_started = true;
	}
	if (is_started) {
		display(); // show the board with the piece on it
		// remove the piece from player's set
		players[player_number].remove_piece(piece_number);
	}
	return is_started;
}

void board::print_piece_menu(const bool capital) const
{
	go_to_console_position(115, 3);
	if (capital) {
		std::cout << "WHICH PIECE DO YOU WISH TO USE? PLEASE PICK A NUMBER.";
	}
	else {
		std::cout << "Which piece do you wish to use? Please pick a number.";
	}
	go_to_console_position(115, 4);
	std::cout << "Chosen piece: ";
}

void board::print_option_menu(const bool capital) const
{
	go_to_console_position(115, 6);
	if (capital) {
		std::cout << "WHAT DO YOU WISH TO DO?";
	}
	else {
		std::cout << "What do you wish to do?";
	}
	go_to_console_position(115, 7);
	std::cout << "- rotate (press r)";
	go_to_console_position(115, 8);
	std::cout << "- flip (press f)";
	go_to_console_position(115, 9);
	std::cout << "- place on the board (press p)";
	go_to_console_position(115, 10);
	std::cout << "- display allowed moves, not available during the first"
		<< " round (press d)";
	go_to_console_position(115, 11);
	std::cout << "- use different piece (press b)";
}

void board::print_place_menu(const bool capital) const
{
	go_to_console_position(115, 13);
	if (capital) {
		std::cout << "WHERE DO YOU WISH TO PLACE THE PIECE? PLEASE SPECIFY THE"
			<< " SQUARE BY STATING";
		go_to_console_position(115, 14);
		std::cout << "THE CORRESPONDING LETTER AND NUMBER (E.G. A1).";
		go_to_console_position(115, 15);
		std::cout << "ALTERNATIVELY, PRESS b TO GO BACK TO THE PIECE MENU.";
	}
	else {
		std::cout << "Where do you wish to place the piece? Please specify the"
			<< " square by stating";
		go_to_console_position(115, 14);
		std::cout << "the corresponding letter and number (e.g. A1).";
		go_to_console_position(115, 15);
		std::cout << "Alternatively, press b to go back to the piece menu.";
	}
	go_to_console_position(115, 16);
	std::cout << "Note that the piece square with the piece number on it will"
		<< " be placed on that board square.";
	go_to_console_position(115, 17);
	std::cout << "Chosen board square: ";
}

void board::erase_text(const size_t x, const size_t y) const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	go_to_console_position(x, y);
	for (size_t i{}; i < 35; i++) {
		std::cout << " ";
	}
}

void board::take_turn(const size_t player_number, const bool first)
{
	// first two lines required due to recursion
	erase_text(129, 4); // erase the chosen piece number
	erase_text(136, 17); // erase the chosen square number
	go_to_console_position(139, 1);
	std::cout << players[player_number].get_colour();
	players[player_number].display(); // display players set
	print_piece_menu(true); // in capital letters
	bool is_end{ false };
	std::string input_string;
	size_t chosen_piece_number{};
	while (!is_end) {
		std::getline(std::cin, input_string);
		std::istringstream piece_number_stream{ input_string };
		piece_number_stream >> chosen_piece_number;
		if ((!piece_number_stream.fail()) && chosen_piece_number > 0
			&& chosen_piece_number <= players[player_number]
			.get_number_of_pieces() && ((input_string.size() == 1 
				&& chosen_piece_number < 10) || (input_string.size() == 2 
					&& chosen_piece_number >9))) {
			// if correct input
			erase_text(175, 3); // erase "Invalid input" if it appeared earlier
			is_end = true;
		}
		else {
			go_to_console_position(175, 3);
			std::cout << "Invalid input. Try again.";
			erase_text(129, 4); // erase the invalid input
			// go back to where piece number input is taken 
			go_to_console_position(129, 4);
		}
	}
	// once the piece number have been entered correctly
	std::shared_ptr<piece> used_piece{ players[player_number]
		.get_piece(chosen_piece_number) };
	print_piece_menu(false); // not in capital letters
	print_option_menu(true); // in capital letters
	is_end = false;
	while (!is_end) {
		go_to_console_position(139, 6);
		std::getline(std::cin, input_string);
		erase_text(139, 6); // hide the input 
		if (input_string[0] == 'r' && input_string.size() == 1) {
			erase_text(169, 6); // erase "Invalid input" if it appeared earlier
			players[player_number].erase_piece(chosen_piece_number);
			used_piece->rotate();
			players[player_number].display_piece(chosen_piece_number);
		}
		else if (input_string[0] == 'f' && input_string.size() == 1) {
			erase_text(169, 6); // erase "Invalid input" if it appeared earlier
			players[player_number].erase_piece(chosen_piece_number);
			used_piece->flip();
			players[player_number].display_piece(chosen_piece_number);
		}
		else if (input_string[0] == 'p' && input_string.size() == 1 && !first) {
			erase_text(169, 6); // erase "Invalid input" if it appeared earlier
			print_option_menu(false); // not in capital letters
			print_place_menu(true); // in capital letters
			bool is_placed{ false };
			size_t chosen_board_number{};
			while (!is_placed) {
				std::getline(std::cin, input_string);
				if (input_string[0] == 'b' && input_string.size() == 1) {
					// go back to the piece menu
					erase_text(129, 4); // erase the chosen piece number
					// erase "Invalid input" if it appeared earlier
					erase_text(170, 14); 
					print_place_menu(false); // not in capital letters
					erase_text(136, 17); // erase chosen square number
					// recursively call the function
					take_turn(player_number, false);
					// ensure all loops are exited after the recursion
					is_placed = true;
					is_end = true;
				}
				else {
					// board square letter is input first
					std::istringstream board_number_stream{ input_string
						.substr(1, std::string::npos) };
					board_number_stream >> chosen_board_number;
					if (std::find(letters.begin(), letters.end(), 
						input_string[0]) != letters.end() 
						&& !board_number_stream.fail() 
						&& chosen_board_number > 0 && chosen_board_number <= 20
						&& ((input_string.size() == 2 && chosen_board_number 
							< 10) || (input_string.size() == 3 
								&& chosen_board_number > 9))) {
						// if correct input
						size_t position{ convert_input_to_position(
							input_string[0],chosen_board_number) };
						// two negative bools mean the player is placing piece  
						is_placed = place_piece(player_number,
							chosen_piece_number, position, false, false);
						if (is_placed) {
							// erase "Invalid input" if it appeared earlier
							erase_text(170, 14); 
							print_place_menu(false); // not in capital letters
							is_end = true;
						}
						else {
							// erase "Invalid input" if it appeared earlier
							erase_text(170, 14);
							go_to_console_position(170, 14);
							std::cout << "Can't place the piece there";
							// erase the chosen square number
							erase_text(136, 17); 
							// go back to choose another board position
							go_to_console_position(136, 17);
						}
					}
					else {
						// erase "Invalid input" if it appeared earlier
						erase_text(170, 14); 
						go_to_console_position(170, 14);
						std::cout << "Invalid input. Try again.";
						erase_text(136, 17); // erase the chosen square number
						// go back to choose another board position
						go_to_console_position(136, 17);
					}
				}
			}
		}
		// placing a piece in the first round
		else if (input_string[0] == 'p' && input_string.size() == 1 && first) {
			erase_text(169, 6); // erase "Invalid input" if it appeared earlier
			print_option_menu(false); // not in capital letters
			bool is_started{ false };
			is_started = place_first_piece(player_number, chosen_piece_number);
			if (!is_started) {
				// erase "Invalid input" if it appeared earlier
				go_to_console_position(169, 6);
				std::cout << "Can't start this way";
				take_turn(player_number, true); // recursively call the function
			}
			is_end = true; 
		}
		// display option is not available in the first round
		else if (input_string[0] == 'd' && input_string.size() == 1 && !first) {
			bool is_available{ false };
			// is_available holds information on if there is any available move
			is_available = find_available_moves(player_number,
				chosen_piece_number, true);
			if (!is_available) {
				go_to_console_position(139, 6);
				std::cout << "No allowed moves found. ";
				system("pause");
				// two erase_text function calls are neede to erase all the text
				erase_text(139, 6); 
				erase_text(174, 6);
			}
		}
		else if (input_string[0] == 'b' && input_string.size() == 1 && !first) {
			erase_text(169, 6); // erase "Invalid input" if it appeared earlier
			erase_text(129, 4); // erase the chosen piece number
			// recursively call the function
			take_turn(player_number,false); // takes false as second argument
			// ensure all loops are exited after the recursion
			is_end = true; 
		}
		else if (input_string[0] == 'b' && input_string.size() == 1 && first) {
			erase_text(169, 6); // erase "Invalid input" if it appeared earlier
			erase_text(129, 4);// erase the chosen piece number
			take_turn(player_number, true); // takes true as second argument
			// ensure all loops are exited after the recursion
			is_end = true;
		}
		else { // if incorrect input
			go_to_console_position(169, 6);
			std::cout << "Invalid input. Try again.";
		}
	}
	erase_text(129, 4); // erase the chosen piece number
	erase_text(136, 17); // erase the chosen square number
	erase_text(139, 1); // erase player's colour
}

bool board::find_available_moves(const size_t player_number,
	const size_t piece_number, const bool players_test)
{
	bool is_placed{ false }, is_any{ false };
	for (size_t i{}; i < size * size; i++) { // for all the board squares
		is_placed = place_piece(player_number, piece_number, i, true,
			players_test);
		// is_any will be true if is_placed was true at least once
		if (is_placed) {
			is_any = true;
		}
	}
	return is_any;
}

bool board::check_if_can_place(const size_t player_number)
{
	go_to_console_position(139, 1);
	std::cout << players[player_number].get_colour();
	players[player_number].display(); // display players set
	bool can_place{ false };
	// if player still has pieces
	if (players[player_number].get_number_of_pieces() > 0) { 
		for (size_t i{ 1 }; i <= players[player_number].get_number_of_pieces();
			i++) { // for all the pieces
			can_place = find_available_moves(player_number, i, false);
			if (can_place) { // if at least one piece can be placed anywhere
				break;
			}
		}
		if (!can_place) {
			for (size_t i{ 1 }; i <= players[player_number]
				.get_number_of_pieces(); i++) { // for all the pieces
				// check all the rotated shapes
				for (size_t j{}; j < 4; j++) {
					players[player_number].get_piece(i)->rotate();
					if (!can_place) {
						can_place = find_available_moves(player_number, i,
							false);
					}
				}
				if (can_place) { // if at least one piece can be placed anywhere
					break;
				}
			}
		}
		if (!can_place) {
			for (size_t i{ 1 }; i <= players[player_number]
				.get_number_of_pieces(); i++) { // for all the pieces
				players[player_number].get_piece(i)->flip();
				// check all the rotated shapes after flipping them
				for (size_t j{}; j < 4; j++) {
					go_to_console_position(115, 18);
					players[player_number].get_piece(i)->rotate();
					if (!can_place) {
						can_place = find_available_moves(player_number, i,
							false);
					}
				}
				players[player_number].get_piece(i)->flip(); // flip back
				if (can_place) { // if at least one piece can be placed anywhere
					break;
				}
			}
		}
	}
	return can_place;
}

void board::remove_player(const size_t player_number)
{
	players.erase(players.begin() + player_number);
}

void board::display() const
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// display squares on the corners of the board
	SetConsoleTextAttribute(hConsole, 224); // yellow background, black text
	bottom::draw_square(1, 1);
	SetConsoleTextAttribute(hConsole, 144); // blue background, black text
	bottom::draw_square(104, 1);
	SetConsoleTextAttribute(hConsole, 192); // red background, black text
	bottom::draw_square(104, 43);
	SetConsoleTextAttribute(hConsole, 160); // green background, black text
	bottom::draw_square(1, 43);
	SetConsoleTextAttribute(hConsole, 15); // grey background, black text
	for (size_t i{}; i < 20; i++) {
		// print board numbers and letters
		SetConsoleTextAttribute(hConsole, 15);
		go_to_console_position(6 + 5 * i, 1);
		std::cout << i +1;
		go_to_console_position(6 + 5 * i, 44);
		std::cout << i + 1;
		go_to_console_position(3, 4 + 2 * i);
		std::cout << letters.at(i);
		go_to_console_position(105, 4 + 2 * i);
		std::cout << letters.at(i);
		// display the board
		for (size_t j{}; j < 20; j++) {
			if (board_colours[i + 20* j] == "yellow") {
				SetConsoleTextAttribute(hConsole, 224);
			}
			else if (board_colours[i + 20 * j] == "blue") {
				SetConsoleTextAttribute(hConsole, 144);
			}
			else if (board_colours[i + 20 * j] == "red") {
				SetConsoleTextAttribute(hConsole, 192);
			}
			else if (board_colours[i + 20 * j] == "green") {
				SetConsoleTextAttribute(hConsole, 160);
			}
			else if (board_colours[i + 20 * j] == "white") {
				SetConsoleTextAttribute(hConsole, 240);
			}
			else if (board_colours[i + 20 * j] == "grey") {
				SetConsoleTextAttribute(hConsole, 128);
			}
			if (board_colours[i + 20 * j] == board_colours[i + 20 * (j + 1)] 
				&& j < 19) {
				top::draw_square(5 * (i + 1), 3 + 2 * j);
			}
			else {
				bottom::draw_square(5 * (i + 1), 3 + 2 * j);
			}
		}
	}
	// print the rules and instructions
	SetConsoleTextAttribute(hConsole, 15); // black background, white text
	go_to_console_position(1, 46);
	std::cout << "RULES AND INSTRUCTIONS: First round: the piece must be"
		<< " positioned in a way that one of its squares is in";
	go_to_console_position(1, 47);
	std::cout << "the corner square of the board. Other rounds: the piece"
		<< " cannot touch any other piece of the same colour";
	go_to_console_position(1, 48);
	std::cout << "with any of its sides, but at least one of its corners must"
		<< " touch a corner of a piece of the same colour.";
}