/*
 * Implement the night phase.
 * 
 * Each player is represented as a vector element.
 * The value of each element represents the role of each player.
 * Citizen --> 0, Doctor --> 1, Gangster --> 2, Lost --> -1. 
*/
#include "std_lib_facilities.h"
#include <limits.h>

#define NUM_PLAYERS 7

class Bad_input_type_error{};
class Player_out_of_range_error{};
class Player_is_out_error{};
class Player_himself_error{};

int read_player_number(vector<int>& vec, int self_number);
void voting(vector<int>& vec);

int main(void) {

    return 0;
}

void voting(vector<int>& vec) {
    vector<int> in_game_players;
    for(int i = 0; i < vec.size(); ++i) {
        if (vec[i] != -1) {// Ignore lost players 
            in_game_players.push_back(i + 1);// +1 because we want number not index
        }
    }
    // Ballot box with the size of the in-game players.
    vector<int> ballot_box(in_game_players.size(), 0);// Initialize with 0

}

/*
 * Reads and returns a player's number from standard input.
 * CAREFUL: It returns the number (#) NOT the index.
*/
int read_player_number(vector<int>& vec, int self_number) {
    int player_chosen = -1;
    cin >> player_chosen;

    if (!cin) {// Check if the user gave an integer.
        throw Bad_input_type_error();
    }

    if (player_chosen < 1 || player_chosen > NUM_PLAYERS) {// Player's number is out of range.
        throw Player_out_of_range_error();
    }

    if (vec[player_chosen - 1] == -1) {// The player chosen is already out.
        throw Player_is_out_error();
    }

    if (player_chosen == self_number) {// The player chose himself.
        throw Player_himself_error();
    }

    return player_chosen;
}