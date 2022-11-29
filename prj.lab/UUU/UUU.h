#include <algorithm>
#include <vector>
#include <string>
#include <map>

struct cards;

struct player : public cards{
public:
	std::pair<cards, cards> hand;
	int place_from_dealer;
	int money;
	bool in_game;

	player() :
		hand({ cards::invalid(), cards::invalid() }),
		place_from_dealer(-1),
		money(1000),
		in_game(true) {}

};

class game_state {
public:
	std::map<int, std::string> cards_val;
	std::map<int, std::string> suits;
	std::map<std::string,int> cards_val_r;
	std::map<std::string, int> suits_r;
	std::vector<cards> board;
	int cur_p;//turn_of_player_x
	int cur_bet;
	int bank;
	std::vector<cards> deсk;

	std::pair<cards, cards> random_from_deck() {

	}

	
	game_state() : cards_val({ {2, "2"},{3, "3"},{4, "4"},{5, "5"},{6, "6"},{7, "7"},{8, "8"},{9, "9"},{10, "10"},{11, "J"},{12, "Q"},{13, "K"},{14, "A"} }),
		suits({ {0,"c"},{1,"d"},{2,"h"},{3,"s"} }),
		cur_p(-1)
	{
		for (int i = 2; i <= 14; ++i) cards_val_r[cards_val[i]] = i;
		for (int i = 0; i <= 3; ++i)suits_r[suits[i]] = i;
	}

	std::map<int, player> players;
private:
};



struct cards {
	int val, suit;
	cards(int val,int suit):
		val(val),suit(suit) {}
	cards invalid() {
		return cards(-1, '-');
	}
	cards():val(invalid().val),suit(invalid().suit) {}
};

class game_cycle : public  game_state {
	void seat_the_players(std::map<int, player>& pl,int n) {
		for (int i = 0; i < n; ++i)
			pl[i] = player();
	}
	void deal_cards(std::map<int, player>& pl) {
		for (int i = 0; i < pl.size(); ++i)
			players[i].hand = random_from_deck();
	}
	

	void game(int number_of_players) {
		game_state GAME = game_state();

		seat_the_players(GAME.players, number_of_players);
		deal_cards(GAME.players);
		
	}
};

class actions : public  game_cycle {
	std::string fold() {
		players[cur_p].in_game = 0;

		return "success";
	}
	std::string call() {
		if (players[cur_p].money < cur_bet) {
			return "not enough money";
		}
	}
};
