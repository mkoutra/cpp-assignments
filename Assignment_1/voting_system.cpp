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
class Player_chose_himself_error{};
class Player_not_candidate_error{};

int get_player_number(vector<int>&, int);
int get_player_number(const vector<int>&, const int, const vector<int>&);
int get_vote(const vector<int>&, const int);
int get_vote(const vector<int>&, const int, const vector<int>&);
int voting_procedure(vector<int>&);
int get_vote(const vector<int>&, const int);
bool in_vector(const int&, const vector<int>&);
vector<int> find_winners (const vector<int>&);
void dashed_line(int size);

int main(void) {
    vector<int> test_players = {0, 0, 2, 1, -1, -1, -1};

    int winner = voting_procedure(test_players);

    if (winner != -1) {
        cout << "Winner is " << winner << "!" << endl;
    }
    else {
        cout << "No winner found" << endl;
    }

    return 0;
}

/* 
 * Implements the voting procedure. 
 * Input: A vector containing the players.
 * Returns: The number(#) of the winner or -1 if there is no winner.
*/
int voting_procedure(vector<int>& vec) {
    vector<int> ballot_box(NUM_PLAYERS, 0);// Count the votes for each player.
    int number_of_voters = 0; // Counts the players that vote.
    int voter_choice = -1;// The player's number(#) that the voter chooses.
    
    // First voting procedure.
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != -1) {// Losers don't vote.
            cout << "Player #" << (i + 1) << " vote: ";
            // Get input from user.
            voter_choice = get_vote(vec, i + 1);// get_vote() needs player's number(#) 
            // Count votes
            ballot_box[voter_choice - 1]++;// -1 to transform player's number(#) to index.
            // Count voters
            number_of_voters++;
        }
    }

    vector<int> election_winners = find_winners(ballot_box);

    if (election_winners.size() == 1) {// Only one winner.
        return election_winners[0];
    }
    else if (election_winners.size() == number_of_voters){// Tie among all players.
        return -1;
    }
    else {// Tie among some players.
        fill(ballot_box.begin(), ballot_box.end(), 0);// reset ballot box
        dashed_line(35);
        cout << "----- Second voting procedure -----" << endl;
        dashed_line(35);
        // Second voting procedure.
        for (int i = 0; i < vec.size(); ++i) {
            if (vec[i] != -1) {// Losers don't vote
                cout << "Player #" << (i + 1) << " vote: ";
                // Only players contained in election_winners can be voted.
                voter_choice = get_vote(vec, i + 1, election_winners);
                // Count votes.
                ballot_box[voter_choice - 1]++;// -1 to transform player's number(#) to index.                
            }
        }

        election_winners = find_winners(ballot_box);// Winners of the 2nd voting. 
        
        if (election_winners.size() == 1) {// Only one winner in 2nd voting.
            return election_winners[0];
        }
        else {// Second voting did not have a single winner.
            return -1;
        }
    }
}

/*
 * - Input: A vector of integers that represents the ballot box after voting.
 * - Returns: A vector with the player's that took the majority of votes.
 * - Careful: The return vector does NOT contain indices. It contains player's number(#) 
 *   which is equal to player's index plus 1.
*/
vector<int> find_winners (const vector<int>& vec) {
    int max = vec[0];
    vector<int> winners; // contains the players with most votes.
    
    // Find max & store the index to indices.
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] > max) {// new max found
            max = vec[i];
            winners.clear();// erase all elements that correspond to the old max.
        }

        if (vec[i] == max) {
            winners.push_back(i + 1);// Save player's number(#), not index.
        }
    }

    return winners;
}

/*
 * Reads and returns a player's number from standard input.
 * In case of invalid input, it throws an appropriate exception.
 * It is used in get_vote().
 * CAREFUL: It returns the player's number (#), NOT index.
*/
int get_player_number(const vector<int>& vec, const int self_number) {
    int player_chosen = -1;
    cin >> player_chosen;

    // Check if the user gave an integer.
    if (!cin) {
        throw Bad_input_type_error();
    }
    
    // Player's number is out of range.
    if (player_chosen < 1 || player_chosen > NUM_PLAYERS) {
        throw Player_out_of_range_error();
    }

    // The player chosen is already out.
    if (vec[player_chosen - 1] == -1) {
        throw Player_is_out_error();
    }

    // The player chose himself.
    if (player_chosen == self_number) {
        throw Player_chose_himself_error();
    }

    return player_chosen;
}

/* 
 * It throws exception if someone voted someone not included
 * in the candidates list. Candidates is a vector containing the 
 * player's number (#) that can be voted.
*/
int get_player_number(const vector<int>& vec, const int self_number, const vector<int>& candidates) {
    int player_chosen = get_player_number(vec, self_number);

    if (!in_vector(player_chosen, candidates)) {
        throw Player_not_candidate_error();
    }

    return player_chosen;
}

// Checks if a value is inside a vector.
bool in_vector(const int& val, const vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        if (val == vec[i]) return true;
    }
    return false;
}

/*
 * Gets vote from user. It catches exceptions. Keeps asking until valid input.
 * CAREFUL: Returns the player's number(#) not player's index.
*/
int get_vote(const vector<int>& vec, const int self_number) {
    int vote = -1;
    
    while (1) {// Keep asking the user until they give valid input.
        try {
            vote = get_player_number(vec, self_number);
            break;
        }
        catch (Bad_input_type_error) {
            cin.clear();// Clear cin's error flags.
            // Clear input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cerr << "Bad_input_type_error. Please try again.\n" << endl;
        }
        catch (Player_out_of_range_error) {
            cerr << "\nPlayer_out_of_range_error. Please try again." << endl;
        }
        catch (Player_is_out_error) {
            cerr << "\nPlayer_is_out_error. Please try again." << endl;
        }
        catch (Player_chose_himself_error) {
            cerr << "\nPlayer_chose_himself_error. Please try again." << endl;
        }
    }

    return vote;
}

/*
 * Same as get_vote() but it also takes a second vector as an argument.
 * Forbids user to give a number not included in the second vector.
*/
int get_vote(const vector<int>& vec, const int self_number, const vector<int>& candidates) {
    int vote = -1;
    
    while (1) {// Keep asking the user until they give valid input.
        try {
            vote = get_player_number(vec, self_number, candidates);
            break;
        }
        catch (Bad_input_type_error) {
            // Clear cin's error flags and input buffer.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cerr << "Bad_input_type_error. Please try again: ";
        }
        catch (Player_out_of_range_error) {
            cerr << "\nPlayer_out_of_range_error. Please try again:";
        }
        catch (Player_is_out_error) {
            cerr << "\nPlayer_is_out_error. Please try again:";
        }
        catch (Player_chose_himself_error) {
            cerr << "\nPlayer_chose_himself_error. Please try again:";
        }
        catch (Player_not_candidate_error) {
            cerr << "\nPlayer_not_candidate_error. Please try again:";
        }
    }

    return vote;
}

// Prints a dashed line and a newline with size given by user.
void dashed_line(int size) {
    while (size--) cout << '-';
    cout << '\n';
}