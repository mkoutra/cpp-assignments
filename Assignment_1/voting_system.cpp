/*
 * Implement the voting system.
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
int voting(vector<int>& vec);
int take_correct_input(const vector<int>& vec, const int self_number);

int main(void) {

    return 0;
}

// Implements voting and returns the player with the most votes.
// If no such a player exists it returns -1.
int voting(vector<int>& vec) {
    vector<int> ballot_box(NUM_PLAYERS, 0);
    int player_vote = -1;
    int number_of_voters = 0;

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != -1) {// losers do not vote
            player_vote = take_correct_input(vec, i);
            ballot_box[player_vote - 1]++;
            number_of_voters++;
        }
    }

    vector<int> most_votes = max_indices(ballot_box);

    if (most_votes.size() == 1) {
        return most_votes[0];
    }
    else if (most_votes.size() == number_of_voters){// same votes for all players.
        return -1;
    }
    else {// tie among some players. Voting procedure only for them.
        // Na kano mia read_input me argument tous swstous deiktes.
        // Na valw ena flag pou na to lene again se periptvsh 
        // pou erthei tie break (paizei k na min xreiazetai)
    }

}

/* SHITTY DOCUMENTATION I MUST CHANGE IT
 *
 * Input: A vector with integers.
 * Let's say that the maximum value is called max.
 * Returns: A vector that contains the indices of input vector 
 *          that contain the maximum value
 * What I like in this approach is that everything happens in a single scan.
*/
vector<int> max_indices (const vector<int>& vec) {
    int max = vec[0];
    vector<int> indices; // Indices of vec-elements with the maximum number
    
    // Find max & store the index to indices.
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] > max) {
            max = vec[i];
            indices.clear();// erase all elements from indices since we have a new max value
        }

        if (vec[i] == max) indices.push_back(i);
    }

    return indices;
}

/*
 * Reads and returns a player's number from standard input.
 * CAREFUL: It returns the number (#) NOT the index.
*/
int read_player_number(const vector<int>& vec, const int self_number) {
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

int take_correct_input(const vector<int>& vec, const int self_number) {
    int player_vote = -1;
    
    while (1) {
        try {
            player_vote = read_player_number(vec, self_number);
            break;
        }
        catch (Bad_input_type_error) {
            // Clear cin's error flags and input buffer.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cerr << "Bad_input_type_error. Please try again.\n" << endl;
        }
        catch (Player_out_of_range_error) {
            cerr << "\nPlayer_out_of_range_error. Please try again." << endl;
        }
        catch (Player_is_out_error) {
            cerr << "\nPlayer_is_out_error. Please try again." << endl;
        }
        catch (Player_himself_error) {
            cerr << "\nPlayer_himself_error. Please try again." << endl;
        }
    }

    return player_vote;
}