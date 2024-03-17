/*
 * This file contains all the functions used in assignment 1 in main.cpp.
 * 
 * Michail E. Koutrakis
 * Email: m.koutrakis@physics.uoc.gr
 * Github: https://github.com/mkoutra
 * March 2023
*/

#include "town_of_salem.h"

/*
 *************************
 *** GENERAL FUNCTIONS ***
 *************************
*/

// Prints a string between dashed lines.
void dashed_message(string s) {
    cout << string(s.size(), '-') << endl;
    cout << s << endl;
    cout << string(s.size(), '-') << endl;
    cout << '\n';
}

// Checks if a value is inside a vector.
bool in_vector(const int& val, const vector<int>& vec) {
    for (int i : vec) {
        if (val == i) return true;
    }
    return false;
}

/*
 * Returns the role that corresponds to the integer given:
 * 0 --> Citizen, 1 --> Doctor, 2 --> Gangster, -1 --> Loser. 
*/
string role(int digit) {
    switch(digit) {
        case 0: return "Citizen";
        case 1: return "Doctor";
        case 2: return "Gangster";
        case -1: return "Loser";
        default: error("Non valid role number.");
    }
    return ""; // to avoid compiler's warning
}

/*
 * Checks if a string represents an integer,
 * ignoring leading and trailing whitespaces. 
*/
bool is_int(string s) {
    int i = 0;// for scanning

    //Drop leading whitespaces.
    while(s[0] == ' ' || s[0] == '\t' || s[0]=='\n') {
        s = s.substr(1);
    }

    // Sign check
    if (s[0] == '+' || s[0] == '-') {
        s = s.substr(1);
    }

    // Check if the string given had only whitespaces or '+', '-'.
    if (s.size() == 0) return false;
    
    // Scan string
    while(s[i] != '\0') {
        // Digit found
        if ((s[i] >= '0' && s[i] <= '9')) { 
            i++;
            continue;
        }
        // Trailing whitespaces
        else if (s[i] == ' ' || s[i] == '\t') { 
            // scan every character until the end of the word
            while(s[i] != '\0') { 
                if(s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
                    return false; // Not a whitespace found
                }
                i++;
            }
            return true; // only trailing whitespaces found
        }
        // Not a digit or whitespace.
        else {
            return false;
        }

        i++;
    }

    return true;
}

// Given the vector of players, it checks if the game is over.
bool is_over(const vector<int>& vec) {
    int still_active = 0;

    // Gangster is out.
    if (in_vector(GANG, vec) == false) {
        cout << "GAME OVER!\nGangster is out!\n\n";
        return true;
    }

    // Two players left with one being the gangster.
    for (int pl : vec) {
        if (pl != LOSER ) still_active++;
    }

    if (still_active == 2) {
        cout << "GAME OVER!\nGangster won!\n\n";
        return true;
    }

    return false;
}

/*
 ******************************
 ******* INITIALIZATION *******
 ******************************
*/

// Puts doctor, gangster and citizens randomly inside the vector given.
void initialization(vector<int>& vec) {
    // Set size equal to the number of players and fill with citizens. 
    vec.resize(NUM_PLAYERS);
    fill(vec.begin(), vec.end(), CIT);
    
    // Generate random indices for gangster & doctor in [0,7).
    srand(time(NULL));
    int gang_idx = rand() % NUM_PLAYERS;
    int doc_idx = rand() % NUM_PLAYERS;
    
    // If the indices are equal, generate a new index for doctor.
    while (doc_idx == gang_idx) {
        doc_idx = rand() % NUM_PLAYERS;
    }

    // Place gangster and doctor inside the vector.
    vec[doc_idx] = DOC;
    vec[gang_idx] = GANG;
}

/*
 *******************************
 ********* INFO MENU  **********
 *******************************
*/

/*
 * Implements the info menu. Takes the vector containing the players 
 * and the id of the last loser as input.
*/
void info_menu(const vector<int>& vec, int last_loser) {
    int option_given = -1;

    string s;
    s = "(1) Players | (2) Players & Roles | (3) Losers | (4) Last Loser";
    
    cout << "\nINFO MENU\n";
    dashed_message(s);
    cout << "Give option [1-4] >> ";

    // Get input from user. Keep asking if the input is not valid.
    while (1) {
        try {
            // get option from user  
            option_given = get_option(); 
            break;
        }
        catch (runtime_error &e) {
            cin.clear(); // Clean error flag.
            cerr << e.what() << " Please try again. >> ";
        }
        catch(EOF_error) { // Re-throw EOF_error
            throw EOF_error();
        }
        catch(...) {
            cerr << "Error in menu. Please try again. >> ";
        }
    }

    // Print the message that corresponds to the option given.
    print_request(option_given, vec, last_loser);
}

// Gets an option from user and returns it.
int get_option(void) {
    int n_option;
    string s_option;

    // Read a single line ignoring leading whitespaces.
    cin >> ws;
    getline(cin, s_option);
    
    // EOF given by user (Ctrl+D / Ctrl+Z). 
    if (cin.eof()) { 
        throw EOF_error();
    }

    // Non integer given.
    if (is_int(s_option) == false) {
        error("Not an integer given.");
    } 
    
    // Transform string to int
    n_option = stoi(s_option);

    // Option is out of range.
    if (n_option < 1 || n_option > NUM_OPTIONS) {
        error("Option is out of range.");
    }

    return n_option;
}

// Prints the players that correspond to the option number given.
void print_request(int option_num, const vector<int>& vec, int last_loser) {
    string s = "|";// here concatenate the string to print.

    switch (option_num) {
        case 1: {
            cout << "\nPlayers\n";
            // Find active players.
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i] != LOSER) {
                    s += "#" + to_string(i + 1) + " |";
                }
            }
            break;
        }
        case 2: {
            cout << "\nPlayers & Roles\n";
            // Find active players.
            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i] != LOSER) {
                    s += "#" + to_string(i + 1) + " " + role(vec[i]) + "|";
                }
            }
            break;
        }
        case 3: {
            cout << "\nLosers\n";
            // Check if a loser exists.
            if (in_vector(LOSER, vec) == false) { // No loser found
                s += " NONE |";
                break;
            }
            else {
                // Find the losers.
                for (int i = 0; i < vec.size(); ++i) {
                    if (vec[i] == LOSER) {
                        s += "#" + to_string(i + 1) + " |";
                    }
                }
            }
            break;
        }
        case 4: {
            s =  "Last loser: | ";

            // Check if last_loser corresponds to an id.
            if (last_loser < 0 || last_loser > NUM_PLAYERS) {// Non valid id.
                s += "NONE |";
            }
            else {
                s += "#" + to_string(last_loser) + " |";
            }
            break;
        }
    }

    dashed_message(s);
}

/*
 *******************************
 ********* NIGHT PHASE *********
 *******************************
*/

/* 
 * Implements night phase. Takes the vector of players as input.
 * Sets the role of the player leaving to LOSER and returns his id. 
 * If no player leaves returns -1.
*/
int night_phase(vector<int>& vec) {
    int gangster_id = -1, doctor_id = -1; 
    int gangster_selection = -1, doctor_selection = -1;
    
    cout << "--- Night phase begins ---\n\n";

    // Find gangster's and doctor's id.
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == GANG) gangster_id = i + 1;
        if (vec[i] == DOC) doctor_id = i + 1;
    }

    // Gangster's input.
    cout << "Gangster (Player #" << gangster_id << ") select a player. >> ";
    gangster_selection = get_valid_id(vec); // get id from user.

    // Check if doctor is out.
    if (in_vector(DOC, vec) == false) {
        cout << "\nPlayer #" << gangster_selection << " is leaving.\n";
        
        vec[gangster_selection - 1] = LOSER; // gangster's pick leaves.
        return gangster_selection; // Return id of loser.
    }

    // Doctor's input
    cout << "Doctor (Player #" << doctor_id << ") save a player. >> ";
    doctor_selection = get_valid_id(vec, doctor_id);
    
    // Return
    if (gangster_selection == doctor_selection) {// Nobody is leaving.
        cout << "\nNobody is leaving.\n";
        return -1;
    }
    else {
        cout << "\nPlayer #" << gangster_selection << " is leaving.\n";

        vec[gangster_selection - 1] = LOSER;
        return gangster_selection;
    }
}

/*
 * Reads and returns a player's id from standard input.
 * The second arg. is optional with default value -1 and it should 
 * be used only when the player is not allowed to vote himself.
*/
int get_id(const vector<int>& vec, int self_id) {
    int id_given;
    string s_id_given;

    // Read a single line ignoring leading whitespaces.
    cin >> ws;
    getline(cin, s_id_given); 
    
    // EOF given by user (Ctrl+D / Ctrl+Z). 
    if (cin.eof()) { 
        throw EOF_error();
    }

    // Non integer given.
    if (is_int(s_id_given) == false) {
        error("Not an integer given.");
    } 
    
    // Transform string to int.
    id_given = stoi(s_id_given);

    // Player is out of range.
    if (id_given < 1 || id_given > NUM_PLAYERS) {
        error("ID is out of range.");
    }
    
    // The player chosen is already out.
    if (vec[id_given - 1] == LOSER) {
        error("This player is out.");
    }
    
    // Player chose himself
    if ((self_id != -1) && (id_given == self_id)) {
        error("You can't choose yourself.");
    }

    return id_given;
}

/*
 * Reads a player's id using get_id() and returns it. 
 * Handles errors and keeps asking for correct input.
 * Second arg. is optional and should be used only when 
 * the player is not allowed to vote himself.
*/
int get_valid_id(const vector<int>& vec, int self_id) {
    int id_given = -1;

    // Keeps asking until user gives valid input.
    while (1) { 
        try {
            id_given = get_id(vec, self_id);
            break;
        }
        catch (runtime_error &e) {
            cin.clear(); // Clean error flag.
            cerr << e.what() << " Please try again. >> ";
        }
        catch(EOF_error) { // Re-throw EOF_error.
            throw EOF_error(); 
        }
        catch(...) {
            cerr << "Error in night phase. Please try again. >> ";
        }
    }
    return id_given;
}

/*
 *****************************
 ********* DAY PHASE *********
 *****************************
*/

/* 
 * Implements Day phase. Takes the vector of players as input.
 * Calls voting_procedure() and returns the id of the player leaving.
 * If no player leaves, returns -1.
*/
int day_phase(vector<int>& vec) {
    cout << "\n--- Day phase begins ---\n";

    int player_leaving = voting_procedure(vec);

    if (player_leaving == -1) { // No player leaves
        cout << "\nNobody is leaving.\n\n";
    }
    else {// Someone is leaving.
        cout << "\nPlayer #" << player_leaving << " is leaving.\n\n"; 
    }

    return player_leaving;
}

/*
 ****************************
 ***** VOTING PROCEDURE *****
 ****************************
*/

/* 
 * Implementation of the voting system. Takes the vector of players as input.
 * Sets the role of the player taking the majority to LOSER and returns 
 * his id. If no such a player exists, returns -1.
*/
int voting_procedure(vector<int>& vec) {
    int n_voters = 0; // number of voters.
    vector<int> winners_ids;

    cout << "\n----- Voting -----\n";

    // Count voters
    for (int i : vec){
        if (i != LOSER) n_voters++; 
    }

    // Winners of 1st voting
    winners_ids = elections(vec);

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
        cout << "\nTie among Players ";
        for (int i : winners_ids) cout << "#" + to_string(i) + " ";
        cout << "\n--- 2nd Voting ---\n";

        // Only the winners of the 1st voting can be voted now
        winners_ids = elections(vec, winners_ids); // winners of 2nd voting
        
        // Clear Majority.
        if (winners_ids.size() == 1) {
            vec[winners_ids[0] - 1] = LOSER;
            return winners_ids[0];
        }
        else {
            return -1;
        }
    }
}

/* 
 * Implements a single voting procedure. Returns a vector with the winners.
 * The first arg, is the vector of the players. 
 * The second arg. is optional and contains a vector with the candidates.
 * This arg. should be used only if a second voting occurs where 
 * the candidates are those that tied at first voting. 
*/
vector<int> elections(const vector<int>& vec, vector<int> candidates) {
    int vote_id = -1;// the id given by user.
    int n_voters = 0;// number of voters
    vector<int> ballot_box(NUM_PLAYERS, 0);// here we count the votes
    vector<int> winners_ids;// here we put the election winners

    // Take the vote of every active player.
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != LOSER) {
            cout << "Player #" << (i + 1) << " vote: ";

            vote_id = get_valid_vote(vec, candidates);
            ballot_box[vote_id - 1]++;
            n_voters++;
        }
    }

    // save the winners_ids
    winners_ids = find_winners(ballot_box);
    
    return winners_ids;
}

/*
 * Given the ballot box vector, it returns the 
 * ids of the players that won the elections.
*/
vector<int> find_winners (const vector<int>& vec) {
    vector<int> winners;
    int max = vec[0];
    
    // Find max and store the corresponding ids to winners.
    // NOTE: If the first condition is true, the second is true as well.
    for (int i = 0; i < vec.size(); ++i) {
        // new maximum value
        if (vec[i] > max) {
            max = vec[i];
            winners.clear(); // New max value --> new winners.
        }
        // Tie or first occurence
        if (vec[i] == max) {
            winners.push_back(i + 1);
        }
    }
    return winners;
}

/*
 * Reads and returns a player's id from standard input. Calls get_id().
 * The second arg. is optional with default value {} and it should be used 
 * only when we have specific candidates (e.g. in second voting).
*/
int get_vote(const vector<int>& vec, const vector<int> candidates) {
    int id_given = get_id(vec);
    
    // The player chosen is not in candidates list.
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
    
    // Keep asking the user until they give valid input.
    while (1) {
        try {
            vote = get_vote(vec, candidates);
            break;
        }
        catch (runtime_error &e) {
            cin.clear(); // Clean error flag.
            cerr << e.what() << " Please try again. >> ";
        }
        catch(EOF_error) { // Re-throw EOF_error
            throw EOF_error();
        }
        catch(...) {
            cerr << "Error in voting. Please try again. >> ";
        }
    }

    return vote;
}