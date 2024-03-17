/*
 * CS150 - Header file for Assignment 2 - March 2023
 * Michail E. Koutrakis
 * Email: m.koutrakis@physics.uoc.gr
 * Github: https://github.com/mkoutra
*/
#include "Round.h"

// Constructors
Round::Round (int nn, string night_name, string day_name)
     :n_round(nn), pl_night(night_name), pl_day(day_name) {};

Round::Round (int nn):n_round(nn), pl_night(" "), pl_day(" ") {};

Round::Round ():n_round(1), pl_night(" "), pl_day(" ") {};
// Setters
void Round::set_round(int rround) {
    n_round = rround;
}

void Round::set_pl_night(string ppl_night) {
    pl_night = ppl_night;
}

void Round::set_pl_day(string ppl_day) {
    pl_day = ppl_day;
}

// "put to" operator
ostream& operator<<(ostream &ost, Round& rr) {
    ost << "Round #" << rr.get_round() << ": " \
        << rr.get_pl_night() << ", " \
        << rr.get_pl_day() << '\n';
    
    return ost;
}

// Given the vector of players, it checks if the game is over.
bool is_over(const vector<Player>& pl_vec) {
    int gang_id = -1;
    int still_active = 0; // count alive players
    
    // Find gangster's id
    for(const Player &pl : pl_vec) {
        if (pl.get_role() == "GANGSTER") {
            gang_id = pl.get_id();
            break;
        }
    }

    // Check if gangster is out.
    if (pl_vec[gang_id - 1].get_status() == false) {
        cout << "GAME OVER!\nGangster is out!\n\n";
        return true;
    }

    for (const Player &pl : pl_vec) {
        if (pl.get_status() == true) still_active++;
    }

    // Two players left with one being the gangster.
    if (still_active == 2) {
        cout << "GAME OVER!\nGangster won!\n\n";
        return true;
    }

    return false;
}

// MENU FUNCTIONS

// Prints a string between dashed lines.
void dashed_message(string s) {
    cout << string(s.size(), '-') << endl;
    cout << s << endl;
    cout << string(s.size(), '-') << endl;
    cout << '\n';
}

// "Underline" a string with a dashed line
void underline_message(string s) {
    cout << s << endl;
    cout << string(s.size(), '-') << endl;
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
void print_request(int option_num, const vector<Player>& pl_vec, const int last_loser) {
    bool loser_found = false; // flag to use if we found at least one loser
    
    switch (option_num) {
        case 1: {
            underline_message("Still alive");

            // Find alive players.
            for (const Player &pl : pl_vec) {
                if (pl.get_status() == true) {
                    cout << pl.full_name() << '\n';
                }
            }
            break;
        }
        case 2: {
            underline_message("Players & Roles");
            // Find alive players.
            for (const Player &pl : pl_vec) {
                if (pl.get_status() == true) {
                    cout << pl.full_name() << " | " \
                         << pl.get_role() << '\n' ;
                }
            }
            break;
        }
        case 3: {
            underline_message("Losers");
            // Find the losers.
            for (const Player &pl: pl_vec) {
                if (pl.get_status() == false) {
                    loser_found = true;
                    cout << pl.full_name() << '\n';
                }
            }
            // In case a loser does not exist.
            if (loser_found == false) { // No loser found
                cout << " NONE\n";
            }
            break;
        }
        case 4: {
            underline_message("Last loser");

            // Check if last_loser corresponds to a valid id.
            if (last_loser < 1 || last_loser > pl_vec[0].get_n_players()) {
                // Non valid id.
                cout << "NONE\n";
            }
            else {
                cout << pl_vec[last_loser - 1].full_name() << '\n';
            }
            break;
        }
    }
}

/*
 * Implements the info menu. Takes the vector containing the players 
 * and the id of the last loser as input.
*/
void info_menu(const vector<Player>& pl_vec, int last_loser) {
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
    print_request(option_given, pl_vec, last_loser);
}
