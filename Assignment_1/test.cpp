#include "std_lib_facilities.h"

#define NUM_PLAYERS 7

class Bad_input_type_error{};
class Player_out_of_range_error{};
class Player_is_out_error{};
class Player_himself_error{};
class Player_not_candidate_error{};

int read_player_number(const vector<int>& vec, const int self_number, const vector<int>& candidates);
bool in_vector(const int& val, const vector<int>& vec);

int main(void) {
    vector<int> test = {0, -1, 0, 0, 2, 1, -1};

    vector<int> cand = {4, 3};
    
    int vote;
    
    while(1) {
        vote = read_player_number(test, 1, cand);
    }

    cout << vote << endl;

    return 0;
}

int read_player_number(const vector<int>& vec, const int self_number, const vector<int>& candidates) {
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

    if (!in_vector(player_chosen, candidates)) {
        throw Player_not_candidate_error();
    }

    return player_chosen;
}

bool in_vector(const int& val, const vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (val == vec[i]) return true;
    }
    return false;
}