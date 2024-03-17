#include "town_of_salem.h"

int main(void) {
    vector<int> players(NUM_PLAYERS, 0);
    int last_loser = -1;
    int last_outcome = -1;
    initialization(players);

    if (info_menu(players, last_loser) == EOF_CODE) {
        return 1;
    }

    while (1) {
        
        /*----- NIGHT PHASE -----*/
        last_outcome = night_phase(players);
        if (last_outcome != -1) last_loser = last_outcome;
        if (is_over(players)) break;
        
        /*----- SHOW MENU -----*/
        if (info_menu(players, last_loser) == EOF_CODE) {
            return 1;
        }
        
        /*----- DAY PHASE -----*/
        last_outcome = day_phase(players);
        if (last_outcome != -1) last_loser = last_outcome;
        if (is_over(players)) break;

        /*----- SHOW MENU -----*/
        if (info_menu(players, last_loser) == EOF_CODE) {
            return 1;
        }
    }

    return 0;
}

/*
 * Checks if a string represents integer.
 * Ignores leading and trailing whitespaces.
*/
bool is_int(string s) {
    int i = 0;
    //Drop leading whitespaces.
    while(s[0] == ' ' || s[0] == '\t' || s[0]=='\n') {
        s = s.substr(1);
    }

    // Sign check
    if (s[0] == '+' || s[0] == '-') {
        s = s.substr(1);
    }
    // String containing only whitespaces or '+', '-' 
    // will be empty at this point (s.size() == 0).
    if (s.empty()) return false;
    
    // Scan string
    while(s[i] != '\0') {
        // Digit
        if ((s[i] >= '0' && s[i] <= '9')) { 
            i++;
            continue;
        }
        // Trailing whitespaces
        else if (s[i] == ' ' || s[i] == '\t') { 
            // scan until end of word
            while(s[i] != '\0') { 
                if(s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
                    return false; // Non-whitespace found
                }
                i++;
            }
            return true; // only trailing whitespaces found
        }
        // Not digit or whitespace.
        else {
            return false;
        }

        i++;
    }

    return true;
}

/*
 * Given the vector of players it checks if the game is over.
*/
bool is_over(const vector<int>& vec) {
    int count_players = 0;
    // Condition #1--> Gangster is out.
    if (!in_vector(GANG, vec)) {
        cout << "GAME OVER!\nGangster is out!\n" << endl;
        return true;
    }

    // Condition #2 -- > One player and the gangster.
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == CIT || vec[i] == DOC) {// count citizens and doctor
            count_players++;
        }
    }

    if (count_players == 1) {
        cout << "GAME OVER!\nGangster won!\n" << endl;
        return true;
    }

    return false;
}

void initialization(vector<int>& vec) {
    try {
    // Fill the vector with citizens.
    fill(vec.begin(), vec.end(), CIT);
    
    // Generate random integers in [0,7).
    srand(time(NULL)); // random seed
    int gang_idx = rand() % NUM_PLAYERS; // Random index for gangster.
    int doc_idx = rand() % NUM_PLAYERS; // Random index for doctor.
    
    // If the two indices are equal, generate a new index for doctor.
    while (doc_idx == gang_idx) {
        doc_idx = rand() % NUM_PLAYERS;
    }

    vec[doc_idx] = DOC; // Doctor
    vec[gang_idx] = GANG; // Gangster

    }
    catch (out_of_range) {// If vector has wrong size.
        vec.resize(NUM_PLAYERS);// resize to corerct size.
        fill(vec.begin(), vec.end(), CIT); // Fill with zerores.
        initialization(vec);
    }
}

/*
 * Implements the info menu.
 * Input: A vector with the players and the id of the last loser.
 * Returns 0 for success, otherwise EOF_CODE. 
*/
int info_menu(const vector<int>& vec, int loser_id) {
    int option_given = -1;

    show_options();

    while (1) { // Keep asking until valid input.
        try {
            option_given = get_option(); // get option from user  
            break;
        }
        catch (runtime_error &e) {
            cin.clear(); // Clean error flag.
            cerr << e.what() << " Please try again. >> ";
        }
        catch(EOF_error) {
            cin.clear();
            cerr << "EOF\n";
            return EOF_CODE;
        }
        catch(...) {
            cerr << "Error in menu. Please try again. >> ";
        }
    }

    print_request(option_given, vec, loser_id);
    return 0;
}

// Get an option from user and return it.
int get_option(void) {
    int n_option;
    string s_option; // string to handle more possible errors.

    cin >> ws; // Ignore leading whitespaces.
    getline(cin, s_option); // read a single line
    
    if (cin.eof()) { // Ctrl+D for Linux, Ctrl+Z for Windows. 
        throw EOF_error();
    }

    // Non integer given.
    if (is_int(s_option) == false) {
        error("Not an integer.");
    } 
    
    n_option = stoi(s_option);// string to int

    // Option is out of range.
    if (n_option < 1 || n_option > NUM_OPTIONS) {
        error("Option is out of range.");
    }

    return n_option;
}

// Shows all options available in a single line.
void show_options(void) {
    string s;
    s = "(1) Players | (2) Players & Roles | (3) Losers | (4) Last Loser";
    
    cout << "INFO MENU" << endl;
    dashed_message(s);
    cout << "Give option [1-4] >> ";
}


/*
 * Prints the players that correspond to the option number given.
 * The players are printed between two dashed lines.
*/
void print_request(int option_num, const vector<int>& vec, int loser_id) {
    string s = "|";// here concatenate the string to print.

    switch (option_num) {
        case 1: {
            cout << "\nPlayers\n";

            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i] != LOSER) { // Ignore losers
                    s += "#" + to_string(i + 1) + " |";
                }
            }
            break;
        }
        case 2: {
            cout << "\nPlayers & Roles\n";

            for (int i = 0; i < vec.size(); ++i) {
                if (vec[i] != LOSER) { // Ignore losers
                    s += "#" + to_string(i + 1) + " " + role(vec[i]) + "|";
                }
            }
            break;
        }
        case 3: {
            cout << "\nLosers\n";

            if (in_vector(LOSER, vec) == false) { // Nobody is a loser
                s += " NONE |";
                break;
            }
            else {
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

            if (loser_id < 0 || loser_id > NUM_PLAYERS) { // out of range
                s += "NONE |";
                break;
            }
            else {
                s += "#" + to_string(loser_id) + " |";
                break;
            }
        }
    }

    dashed_message(s);
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

    return "";// to avoid compiler's warning
}

// Prints a message between dashed lines.
void dashed_message(string s) {
    cout << string(s.size(), '-') << endl;
    cout << s << endl;
    cout << string(s.size(), '-') << endl;
}

/* 
 * Implements night phase.
 * Input: A vector containing the players.
 * Modifies the input vector and returns the id of the player leaving, 
 * otherwise returns -1.
*/
int night_phase(vector<int>& vec) {
    int gangster_id = -1, doctor_id = -1; 
    int gangster_selection, doctor_selection;
    
    cout << "--- Night phase begins ---" << endl;

    /*----- FIND GANGSTER'S AND DOCTOR'S ID -----*/
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == GANG) gangster_id = i + 1;
        if (vec[i] == DOC) doctor_id = i + 1;// +1 for id
    }

    /*----- GANGSTER'S INPUT -----*/
    cout << "Gangster (Player #" << gangster_id << ") select a player. >> ";
    gangster_selection = get_valid_id(vec); // get id from user.

    /*----- CHECK IF DOCTOR IS OUT -----*/
    if (in_vector(DOC, vec) == false) { // No doctor available
        cout << "\nPlayer #" << gangster_selection << " is leaving." << endl;
        
        vec[gangster_selection - 1] = LOSER; // gangster's pick leaves.
        return gangster_selection; // Return id of loser.
    }

    /*----- DOCTOR'S INPUT -----*/
    cout << "Doctor (Player #" << doctor_id << ") save a player. >> ";
    doctor_selection = get_valid_id(vec, doctor_id);
    
    /*----- RETURN -----*/
    if (gangster_selection == doctor_selection) {// Nobody is leaving.
        cout << "\nNobody is leaving." << endl;

        return -1;
    }
    else {
        cout << "\nPlayer #" << gangster_selection << " is leaving." << endl;

        vec[gangster_selection - 1] = LOSER;
        return gangster_selection;
    }
}

/*
 * Reads and returns a player's id from standard input.
 * The second arg. is optional with default value -1. 
 * Should be used only when the player is not allowed to vote himself.
 * Throws and exception if the id is not valid.
*/
int get_player_id(const vector<int>& vec, int self_id) {
    int id_given;
    string s_id_given; // string to handle more possible errors.

    cin >> ws; // Ignore leading whitespaces.
    getline(cin, s_id_given); // read a single line
    
    if (cin.eof()) { // Ctrl+D for Linux, Ctrl+Z for Windows. 
        throw EOF_error();
    }

    // Non integer given.
    if (is_int(s_id_given) == false) {
        error("Not an integer.");
    } 
    
    id_given = stoi(s_id_given);// string to int

    // Player is out of range.
    if (id_given < 1 || id_given > NUM_PLAYERS) {
        error("Player's id is out of range.");
    }
    
    // The player chosen is already out.
    if (vec[id_given - 1] == LOSER) {
        error("Player is out.");
    }
    
    // Player chose himself
    if ((self_id != -1) && (id_given == self_id)) {
        error("Cannot choose yourself.");
    }

    return id_given;
}

/*
 * Reads a player's id using get_player_id() and returns it. 
 * Handles errors and keeps asking for correct input.
 * Second arg. is optional. Should be used only when the player is 
 * not allowed to vote himself.
*/
int get_valid_id(const vector<int>& vec, int self_id) {
    int id_given = -1;

    while (1) { // Keep asking until user gives valid input.
        try {
            id_given = get_player_id(vec, self_id);
            break;// exit while-loop.
        }
        catch (runtime_error &e) {
            cin.clear(); // Clean error flag.
            cerr << e.what() << " Please try again. \n>> ";
        }
        catch(EOF_error) {
            cin.clear();
            cerr << "EOF\n";
            return EOF_CODE;
        }
        catch(...) {
            cerr << "Error in menu. Please try again. >> ";
        }
    }
    return id_given;
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
    int id_given;
    string s_id_given; // string to handle more possible errors.

    cin >> ws; // Ignore leading whitespaces.
    getline(cin, s_id_given); // read a single line
    
    if (cin.eof()) { // Ctrl+D for Linux, Ctrl+Z for Windows. 
        throw EOF_error();
    }

    // Non integer given.
    if (is_int(s_id_given) == false) {
        error("Not an integer.");
    } 
    
    id_given = stoi(s_id_given);// string to int

    // Player's id is out of range.
    if (id_given < 1 || id_given > NUM_PLAYERS) {
        error("Player's id is out of range.");
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
            cin.clear(); // Clean error flag.
            cerr << e.what() << " Please try again. \n>> ";
        }
        catch(EOF_error) {
            cin.clear();
            cerr << "EOF\n";
            return EOF_CODE;
        }
        catch(...) {
            cerr << "Error in menu. Please try again. >> ";
        }
    }

    return vote;
}