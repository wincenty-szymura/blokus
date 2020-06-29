#include"board.h"

int main()
{
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE); // full screen
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // console handle
	SetConsoleTextAttribute(hConsole, 15); // black background, white text
	go_to_console_position(90, 1);
	std::cout << "WELCOME TO BLOKUS";
	go_to_console_position(90, 3);
	system("pause"); // wait for the players
	bool is_end{ false };
	while (!is_end) { // allow for multiple games
		SetConsoleTextAttribute(hConsole, 15); // black background, white text
		board Blokus_board;
		// erase the welcome menu
		Blokus_board.erase_text(90, 1); 
		Blokus_board.erase_text(90, 3);
		Blokus_board.display();
		size_t players_left{ 4 }; // start with four players
		bool can_play{ true };
		go_to_console_position(115, 1);
		std::cout << "Round 1          Player";
		// each player takes their first turn
		for (size_t i{}; i < players_left; i++) {
			Blokus_board.take_turn(i, true);
		}
		size_t j{ 2 }; // start counting rounds from round two
		// declare vectors and reserve space used at the end of the game
		// populated temporarily by the players who lost in the current round
		std::vector<size_t> losing_players; 
		losing_players.reserve(4);
		// keeps track of scores and players until the end of the game
		std::vector<std::pair<size_t, std::string>> scores_and_players;
		scores_and_players.reserve(4);
		while (Blokus_board.get_number_of_players_left() > 0) {
			// display round counter
			go_to_console_position(121, 1);
			std::cout << j;
			for (size_t i{}; i < Blokus_board.get_number_of_players_left();
				i++) { // a single round happens within this loop
				can_play = Blokus_board.check_if_can_place(i);
				if (can_play) {
					// negative bool parameter means it is not the first round
					Blokus_board.take_turn(i, false);
				}
				else { // if out of moves
					go_to_console_position(150, 1);
					std::cout << "You don't have any moves left. ";
					system("pause"); // wait for the player
					// two calls are needed in order to erase all the text
					Blokus_board.erase_text(140, 1);
					Blokus_board.erase_text(175, 1);
					losing_players.push_back(i);
					scores_and_players.push_back(std::make_pair(
						Blokus_board.get_players_score(i), 
						Blokus_board.get_players_colour(i)));
				}
			}
			if (!losing_players.empty()) { // if somebody lost during this round
				// needed for correct iterator arithmetics
				size_t iterator_helper{}; 
				for (auto losing_iterator = losing_players.begin(); 
					losing_iterator < losing_players.end(); losing_iterator++) {
					Blokus_board.remove_player(*losing_iterator 
						- iterator_helper);
					iterator_helper++; // to balance out the removal of a player
				}
				losing_players.clear();
			}
			j++; // next round
		}
		// clear part of the screen at the end of each game
		for (size_t i{}; i < 17; i++) {
			Blokus_board.erase_text(115, i + 1);
			Blokus_board.erase_text(145, i + 1);
			Blokus_board.erase_text(175, i + 1);
		}
		// print the scores 
		go_to_console_position(115, 1);
		std::cout << "The end of the game.";
		std::sort(scores_and_players.begin(), scores_and_players.end());
		go_to_console_position(115, 2);
		std::cout << scores_and_players.at(0).second 
			<< " player wins, congratulations!";
		go_to_console_position(115, 3);
		std::cout << "Scores:";
		for (size_t i{}; i < 4; i++) {
			go_to_console_position(115, 4 + i);
			std::cout << scores_and_players.at(i).second << ": " 
				<< scores_and_players.at(i).first;
		}
		go_to_console_position(115, 8);
		std::cout << "Please note that the lower the score the better.";
		go_to_console_position(115, 9);
		std::cout << "The score corresponds to number of squares that have not"
			<< " been used.";
		go_to_console_position(115, 10);
		std::cout << "Would you like to play again? [Y/N]  ";
		// take the answer from the players
		bool is_correct{ false };
		std::string input_string;
		while (!is_correct) {
			Blokus_board.erase_text(162, 10); // hide the answer
			go_to_console_position(162, 10); // go back to the previous position
			std::getline(std::cin, input_string);
			if (input_string[0] == 'Y' && input_string.size() == 1) {
				// the game will be played again
				is_correct = true;
				// erase the scores
				for (size_t i{}; i < 17; i++) {
					Blokus_board.erase_text(115, i + 1);
					Blokus_board.erase_text(145, i + 1);
					Blokus_board.erase_text(175, i + 1);
				}

			}
			else if (input_string[0] == 'N' && input_string.size() == 1) {
				// end of the game
				is_correct = true;
				is_end = true;
				// erase "Invalid input" if it appeared earlier
				Blokus_board.erase_text(115, 11); 
				go_to_console_position(0, 50); // go to the bottom of the screen
			}
			else {
				go_to_console_position(115, 11);
				std::cout << "Invalid input. Try again.";
			}
		}
	}
}