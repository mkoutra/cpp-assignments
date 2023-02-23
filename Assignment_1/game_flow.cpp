#include "town_of_salem.h"

int main(void) {
    vector<int> players(NUM_PLAYERS, 0);
    int last_loser = -1;

    initialization(players);

    while (1) {
        info_menu(players, last_loser);
        
        /*----- NIGHT PHASE -----*/
        last_loser = night_phase(players);
        if (end_game(players)) break;
        info_menu(players, last_loser);
        
        /*----- DAY PHASE -----*/
        last_loser = day_phase(players);
        if (end_game(players)) break;
        info_menu(players, last_loser);
    }

    return 0;
}

bool end_game(const vector<int>& vec) {
    int count_players = 0;
    // Condition #1--> Gangster is out.
    if (!in_vector(2, vec)) {
        cout << "Gangster is out !" << endl;
        return true;
    }

    // Condition #2 -- > One player and the gangster.
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != 2 && vec[i] != -1) {// count citizens and doctor
            count_players++;
        }
    }

    if (count_players == 1) {
        cout << "Gangster won" << endl;
        return true;
    }

    return false;
}

/* 
 * Implements night phase.
 * Input: A vector containing the players.
 * Returns the id of the player selected, else -1.
 * Modifies the vector that represents the players.
*/
int night_phase(vector<int>& vec) {
    int gangster_id = -1, doctor_id = -1; 
    int gangster_selection = -1, doctor_selection = -1;
    
    cout << "--- Night phase begins ---" << endl;
    
    /*----- GANGSTER'S AND DOCTOR'S ID -----*/

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == GANG) gangster_id = i + 1;
        if (vec[i] == DOC) doctor_id = i + 1;// +1 because we need id.
    }

    /*----- GANGSTER'S INPUT -----*/

    while (1) {// Keep asking until valid input.
        cout << "Gangster --> Player #" << gangster_id;
        cout << ", select a player. >> ";
        try {
            gangster_selection = get_player_id(vec);
            break;// exit while-loop.
        }
        catch (exception &e) {
            // Clean input buffer.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Print error message.
            cerr << e.what() << " Please try again. \n>> ";
        }
    }

    /*----- CHECK IF DOCTOR EXISTS -----*/

    if (doctor_id == -1) { // No doctor available
        // Set the player selected into a loser.
        vec[gangster_selection - 1] = LOSER;

        // Return id, not index.
        return gangster_selection; 
    }

    /*----- DOCTOR'S INPUT -----*/

    while (1) {// Keep asking until valid input.
        cout << "Doctor --> Player #" << doctor_id;
        cout << ", save a player. >> ";
        try {
            doctor_selection = get_doctor_save(vec, doctor_id);
            break;// exit while-loop.
        }
        catch (exception &e) {
            // Clean input buffer.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            // Print error message.
            cerr << e.what() << " Please try again. \n>> ";
        }
    }

    /*----- RETURN -----*/

    if (gangster_selection == doctor_selection) {// No player leaves.
        return -1;
    }
    else {
        vec[gangster_selection - 1] = LOSER;// Gangster's selection leaves.
        return gangster_selection;// Return id, not index.
    }
}

/*
 * Reads and returns a player's id from standard input.
 * CAREFUL: It returns the id (#) NOT the index.
*/
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
 * Read and return the id of the player saved by the doctor.
 * Throws an exception if the doctor peaked himself.
 * Calls get_player_id(). 
*/
int get_doctor_save(const vector<int>& vec, int doc_id) {
    int save_id = get_player_id(vec);
    // Doctor can't save himself
    if (save_id == doc_id) error("Doctor can't save himself.");
    return save_id;
}

// Prints a dashed line with the given size.
void dashed_line(int size) {
    cout << string(size, '-') << endl;
}

// Print a vector.
void print_vec(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
}


/*
 * Implements the info menu.
 * Input: A vector with the players and the id of the last loser.
*/
void info_menu(const vector<int>& vec, int loser_id) {
    show_options();

    while (1) {// Keep asking until valid input.
        try {
            int option_given = get_option(); // read option from user
            
            print_request(option_given, vec, loser_id);
            
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
}


// Get option from user.
int get_option(void) {
    int option = 0;
    // Check if option is an integer and if it is 1 - 4 
    if ( !(cin >> option) || option < 1 || option > 4) {
        error("Non valid option.");
    };

    return option;
}

// Show all options available.
void show_options(void) {
    string s;
    s = "(1) Players | (2) Players & Roles | (3) Losers | (4) Last Loser";
    
    cout << "INFO MENU" << endl;

    dashed_line(s.size());
    cout << s << endl;
    dashed_line(s.size());
    
    cout << "Give option [1-4] >> ";
}


/*
 * Prints the players that correspond to the option number given.
 * The players are printed between two dashed lines.
*/
void print_request(int option_num, const vector<int>& vec, int loser_id) {
    string s = ""; //string in order to use .size() in dashed_line()

    switch (option_num) {
        case 1: {
            s = "Players: | ";
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i] != LOSER) {// Ignore losers
                    s += "#" + to_string(i + 1) + " | ";
                }
            }
            break;
        }
        case 2: {
            s = "Players & Roles: | ";
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i] != LOSER) {// Ignore losers
                    s += "#" + to_string(i + 1) + " " + role(vec[i]) + " |";
                }
            }
            break;
        }
        case 3: {
            s = "Losers: | ";
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i] == LOSER) {// -1 for losers
                    s += "#" + to_string(i + 1) + " |";
                }
            }            
            break;
        }
        case 4:
            s = "Last loser: | #" + to_string(loser_id) + " |";
            break;
    }
    // Print output between two dashed lines.
    dashed_line(s.size());// same size as s.
    cout << s << endl;
    dashed_line(s.size());
}

/*
 * Returns the role that corresponds to the integer given:
 * 0 --> Citizen, 1 --> Doctor, 2 --> Gangster, -1 --> Loser. 
 */
string role(int digit) {
    switch(digit) {
        case 0: 
            return "Citizen";
        case 1:
            return "Doctor";
        case 2:
            return "Gangster";
        case -1:
            return "Loser";
        default:
            error("Non valid role number.");
    }

    return "";// avoid compiler's warning
}

/*
 * Input: A vector that represents the players.
 * Chooses the role of each player randomly.
*/
void initialization(vector<int>& vec) {
    try {
    fill(vec.begin(), vec.end(), 0);// Fill vec with zerores.
    
    // Generate random integers from [0,7).
    srand(time(NULL)); // random seed
    int gang_idx = rand() % NUM_PLAYERS; // index for gangster.
    int doc_idx = rand() % NUM_PLAYERS; // index for doctor.
    
    // If doc_idx != gang_idx generate a new int for doc_idx.
    while (doc_idx == gang_idx) {
        doc_idx = rand() % NUM_PLAYERS;
    }

    vec[doc_idx] = DOC; // Doctor
    vec[gang_idx] = GANG; // Gangster

    }
    catch (out_of_range) {// In vector has wrong size.
        vec.resize(NUM_PLAYERS);// resize to corerct size.
        fill(vec.begin(), vec.end(), 0); // Fill with zerores.

        initialization(vec);// call initialization again
    }
}

void print_vec(vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
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