#include <algorithm>
#include <vector>
#include <string>
#include <map>

struct cards {
	int val, suit;
	cards(int val,int suit): val(val),suit(suit) {}
	
	//Создает карту заглушку
	cards invalid() {
		return cards(-1, '-');
	}

	//Конструктор из карт загрушел
	cards():val(invalid().val),suit(invalid().suit) {}
};

class player : public cards{
public:
	std::pair<cards, cards> hand;
	int place_from_dealer;
	int money;
	bool in_game;
	bool move_is_approved;
	void make_a_move(){
		
	}

	player() :
		hand({ cards::invalid(), cards::invalid() }),
		place_from_dealer(-1),
		money(1000),
		in_game(true) {}

};


class game {
public:
	//Словари перевода цифр в карты и наоборот
	std::map<int, std::string> cards_val;
	std::map<int, std::string> suits;
	std::map<std::string,int> cards_val_r;
	std::map<std::string, int> suits_r;
	//
	std::vector<cards> board;
	int cur_p;//turn_of_player_x
	int cur_bet;
	int bank;
	bool turn_is_active = true;
	bool show_down_required = false;
	std::pair<cards, cards> random_from_deck() {
		for(auto suit: suits ){
			for(auto val: cards_val){
				val.second;
			}
		}
	}
	game() : 
	cards_val({ {2, "2"},{3, "3"},{4, "4"},{5, "5"},{6, "6"},{7, "7"},{8, "8"},
	{9, "9"},{10, "10"},{11, "J"},{12, "Q"},{13, "K"},{14, "A"} }),
		suits({ {0,"c"},{1,"d"},{2,"h"},{3,"s"} }),
		cur_p(-1)
	{
		for (int i = 2; i <= 14; ++i) cards_val_r[cards_val[i]] = i;
		for (int i = 0; i <= 3; ++i)suits_r[suits[i]] = i;
	}
	std::map<int, player> players;
	void seat_the_players(std::map<int, player>& pl,int n) {
		for (int i = 0; i < n; ++i)
			pl[i] = player();
	}
	void deal_cards(std::map<int, player>& pl) {
		for (int i = 0; i < pl.size(); ++i)
			players[i].hand = random_from_deck();
	}
	//проверяет, не остался ли всего один игрок в игре
	bool one_left(){
		int count = 0;
		for(auto p :players)
			count += (p.second.money == 0);
		return (count == 1);
	}
	//Не финальный вариант перехода хода 
	void hand_over_turn(){
		cur_p++;
		cur_p%=players.size();
	}
	std::string fold() {
		players[cur_p].in_game = 0;

		return "success";
	}
	std::string call() {
		if (players[cur_p].money < cur_bet) {
			return "not enough money";
		}

		players[cur_p].money-=cur_bet;

		return "success";
	}
	std::string raise(int raise_money){
		if (raise_money > cur_bet && players[cur_p].money < raise_money) {
			return "not enough money";
		}
		players[cur_p].money -= raise_money;
		cur_p++;

		return "success";
	}
	void make_show_down(){
		
	}
	void ask_for_move(std::pair<const int,player> p){
		while(p.second.move_is_approved){

		}
	}

	void play_game(int number_of_players = 6) {
		seat_the_players(players, number_of_players);
		deal_cards(players);
		while(one_left()){
			while(turn_is_active){
				for(auto p: players){
					if(p.second.in_game == 0) continue;
					ask_for_move(p);

					{
						try{
							fold();
						}
						catch(std::string Error){}
					}
				}
			}

			if(show_down_required){
				make_show_down();
				show_down_required = false;
			}

		}
	}
private:
	std::vector<cards> deсk;
	class logger{
		private:
		public:
	};
};