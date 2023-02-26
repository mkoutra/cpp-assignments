// Implement the voting system.

#include "std_lib_facilities.h"

#define NUM_PLAYERS 7
#define CIT 0
#define DOC 1
#define GANG 2
#define LOSER -1

bool in_vector(const int&, const vector<int>&);

int get_vote(const vector<int>&, const vector<int> vec = {});
int get_valid_vote(const vector<int>&,  const vector<int> vec = {});

vector<int> find_winners(const vector<int>&);
vector<int> elections(const vector<int>&, vector<int> candidates = {});
int voting_procedure(vector<int>& vec);

int day_phase(vector<int>&);

int main(void) {
    vector<int> test_players = {0, 0, 2, 1, -1, -1, -1};

    day_phase(test_players);

    return 0;
}

/* 
 * Implements Day phase.
 * Input: The vector containg the players.
 * Returns the player that won the elections, else -1.
 * Calls voting_procedure() which modifies the vector as argument.
*/
int day_phase(vector<int>& vec) {
    cout << "--- Day phase begins ---" << endl;

    int player_to_kick = voting_procedure(vec);

    if (player_to_kick == -1) { // No winner found
        cout << "\nNobody is leaving." << endl;
    }
    else {// winner found
        cout << "\nPlayer #" << player_to_kick << " is leaving." << endl; 
    }

    return player_to_kick;
}

/* 
 * Implementation of the voting system given.
 * Input: A vector containing the players.
 * Modifies the vector that represents the players. 
 * Returns the id of the winner. If there is no winner, it returns -1.
*/
int voting_procedure(vector<int>& vec) {
    int n_voters = 0; // number of voters.
    vector<int> winners_ids;

    cout << "\n----- Voting -----\n";

    for (int i : vec){
        if (i != -1) n_voters++; // count voters
    }

    winners_ids = elections(vec);// winners of 1st voting

    // Clear Majority
    if (winners_ids.size() == 1) { 
        vec[winners_ids[0] - 1] = LOSER; 
        return winners_ids[0];
    }
    // Equal votes for everyone
    else if (winners_ids.size() == n_voters){ 
        return -1;
    }
    // Tie among some players.
    else { 
        //dashed_message("Second voting");
        cout << "\n--- 2nd Voting ---\n";

        // Only the winners of the 1st voting can be voted now
        winners_ids = elections(vec, winners_ids); // winners of 2nd voting
        
        if (winners_ids.size() == 1) {// Clear Majority.
            vec[winners_ids[0] - 1] = LOSER;
            return winners_ids[0];
        }
        else {// No winner
            return -1;
        }
    }
}

/*
 * Implements a single voting procedure.
 * Returns a vector with the winners.
*/
vector<int> elections(const vector<int>& vec, vector<int> candidates) {
    int vote_id = -1;// id given by user.
    int n_voters = 0;// number of voters
    vector<int> ballot_box(NUM_PLAYERS, 0);// here we count votes
    vector<int> winners_ids;// contains the election winners

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != LOSER) {// Losers don't vote.
            cout << "Player #" << (i + 1) << " vote: ";

            vote_id = get_valid_vote(vec, candidates);
            ballot_box[vote_id - 1]++;
            n_voters++;

        }
    }

    winners_ids = find_winners(ballot_box);// save the winners_ids
    
    return winners_ids;
}

/*
 * Input: A vector of integers that represents the ballot box.
 * Returns: A vector with the ids that won the election.
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

/*
 * Reads and returns a player's id from standard input.
 * The second arg. is optional with default value {}. It should be used 
 * only when we have specific candidates (e.g. in second voting).
 * Throws and exception if the id is not valid.
*/
int get_vote(const vector<int>& vec, const vector<int> candidates) {
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

    // The playser chosen is not in candidates' list.
    if (!candidates.empty() && !in_vector(id_given, candidates)) {
        error("Player chosen is not a candidate.");
    }

    return id_given;
}

/*
 * Reads a player's vote using get_vote() and returns it. 
 * Handles errors and keeps asking for correct input.
 * Second arg. is optional. It should be used only when we have specific 
 * candidates (e.g. in second voting).
*/
int get_valid_vote(const vector<int>& vec, const vector<int> candidates) {
    int vote = -1;
    
    while (1) {// Keep asking the user until they give valid input.
        try {
            vote = get_vote(vec, candidates);
            break;
        }
        catch (runtime_error &e) {
            // Clean input buffer.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Print error message.
            cerr << e.what() << " Please try again. \n>> ";
        }
        catch(...) {
            cerr << "Error in day phase. Please try again.\n>> ";
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