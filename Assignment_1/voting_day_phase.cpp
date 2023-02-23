// Implement the voting system.

#include "std_lib_facilities.h"
#include <limits.h>

#define NUM_PLAYERS 7
#define CIT 0
#define DOC 1
#define GANG 2
#define LOSER -1

void dashed_message(string s);
bool in_vector(const int&, const vector<int>&);

int get_player_id(vector<int>&);
int get_player_id(const vector<int>&, const vector<int>&);
int get_vote(const vector<int>&);
int get_vote(const vector<int>&,  const vector<int>&);

vector<int> find_winners(const vector<int>&);
int voting_procedure(vector<int>&);

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
 * Implements Day phase.
 * Input: The vector containg the players.
 * Returns the player that won the elections, else -1.
 * Calls voting_procedure() which modifies the vector as argument.
*/
int day_phase (vector<int>& vec) {
    cout << "--- Day phase begins ---" << endl;

    int player_to_kick = voting_procedure(vec);

    if (player_to_kick == -1) { // No winner found
        cout << "No winner" << endl;
    }
    else {// winner found
        cout << "Player #" << player_to_kick << " leaves." << endl; 
    }

    return player_to_kick;
}

/* 
 * Implements the voting procedure.
 * Input: A vector containing the players.
 * Returns: The id of the winner, else -1.
 * Modifies the vector that represents the players.
*/
int voting_procedure(vector<int>& vec) {
    int number_of_voters = 0; // Counts voters.
    int voter_choice = -1;// store id given by user.
    vector<int> ballot_box(NUM_PLAYERS, 0);// Count votes.
    vector<int> elec_winners;// Contains ids of election winners.
    
    dashed_message("Voting procedure");

    /*----- FIRST VOTING PROCEDURE-----*/

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != LOSER) {// Losers don't vote.
            cout << "Player #" << (i + 1) << " vote: ";
            voter_choice = get_vote(vec);// Get user input.
            ballot_box[voter_choice - 1]++;// Count votes
            number_of_voters++;// Count voters
        }
    }

    elec_winners = find_winners(ballot_box);// save the winners

    /*----- CHECK ELECTION OUTCOME-----*/

    // Clear Majority
    if (elec_winners.size() == 1) {
        vec[elec_winners[0] - 1] = LOSER;// Modify players' vector

        return elec_winners[0];// Return id of loser.
    }
    else if (elec_winners.size() == number_of_voters){
        // Same number of votes for all players.
        return -1;// no winner
    }
    else {// Tie among some players.
        fill(ballot_box.begin(), ballot_box.end(), 0);// Reset ballot box
        dashed_message("Second voting procedure");
        
        /*----- SECOND VOTING PROCEDURE-----*/

        for (int i = 0; i < vec.size(); ++i) {
            if (vec[i] != LOSER) {// Voter is not a loser.
                cout << "Player #" << (i + 1) << " vote: ";
                // Only players in elec_winners can be voted.
                voter_choice = get_vote(vec, elec_winners);
                ballot_box[voter_choice - 1]++;// Count votes.                
            }
        }

        // Overwrite the result of the 2nd election
        elec_winners = find_winners(ballot_box); 
        
        /*----- SECOND VOTING OUTCOME-----*/

        if (elec_winners.size() == 1) {// Clear Majority.
            vec[elec_winners[0] - 1] = LOSER;// Modify players' vector
            return elec_winners[0];
        }
        else {
            return -1; // no winner
        }
    }
}


/*
 * Input: A vector of integers that represents the ballot box.
 * Returns: A vector with players' ids that won the elections.
*/
vector<int> find_winners (const vector<int>& vec) {
    vector<int> winners; // contains the ids of election winners.
    int max = vec[0];
    
    // Find max & store the id to winners.
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] > max) {// new maximum value found
            max = vec[i];
            // delete all ids that correspond to the previous max value.
            winners.clear();
        }

        if (vec[i] == max) {
            winners.push_back(i + 1);// +1 to save id, not index.
        }
    }

    return winners;
}

// Reads a player's id from standard input and returns its value.
int get_player_id(const vector<int>& vec) {
    int id_given = -1;
    cin >> id_given;

    // Non integer given.
    if (!cin) error("Non valid input type.");
    
    // Player's id is out of range.
    if (id_given < 1 || id_given > NUM_PLAYERS) {
        error("Player chosen is out of range.");
    }
    
    // The player chosen is already out.
    if (vec[id_given - 1] == LOSER) {
        error("Player is out.");
    }

    return id_given;
}

/* 
 * It throws exception if someone voted someone not included
 * in the candidates list. Candidates is a vector containing the 
 * player's number (#) that can be voted.
*/
int get_player_id(const vector<int>& vec, const vector<int>& candidates) {
    int player_chosen = get_player_id(vec);

    if (!in_vector(player_chosen, candidates)) {
        error("Player chosen is not a candidate.");
    }

    return player_chosen;
}

// Read vote from user.
int get_vote(const vector<int>& vec) {
    int vote = -1;
    
    while (1) {// Keep asking the user until they give valid input.
        try {
            vote = get_player_id(vec);
            break;
        }
        catch (exception &e) {
            // Clean input buffer.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Print error message.
            cerr << e.what() << " Please try again. \n>> ";
        }
    }

    return vote;
}

/*
 * Same as get_vote() but it also takes a second vector as an argument.
 * Forbids user to give a number not included in the second vector.
*/
int get_vote(const vector<int>& vec, const vector<int>& candidates) {
    int vote = -1;
    
    while (1) {// Keep asking the user until they give valid input.
        try {
            vote = get_player_id(vec, candidates);
            break;
        }
        catch (exception &e) {
            // Clean input buffer.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Print error message.
            cerr << e.what() << " Please try again. \n>> ";
        }
    }

    return vote;
}

// Checks if a value is inside a vector.
bool in_vector(const int& val, const vector<int>& vec) {
    for (int i : vec) {
        if (val == i) return true;
    }
    return false;
}

// Prints a message between dashed lines.
void dashed_message(std::string s) {
    cout << string(s.size(), '-') << endl;
    cout << s << endl;
    cout << string(s.size(), '-') << endl;
}