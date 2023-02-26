/*
 * Create a menu that will appear before the start of each cycle.
 * 
 * Each player is represented as a vector element.
 * The value of each element represents the role of each player.
 * Citizen --> 0, Doctor --> 1, Gangster --> 2, Lost --> -1. 
*/
#include "std_lib_facilities.h"

#define NUM_PLAYERS 7
#define NUM_OPTIONS 4
#define CIT 0
#define DOC 1
#define GANG 2
#define LOSER -1

void dashed_message(string);
bool in_vector(const int&, const vector<int>&);
string role(int);

int get_option(void);
void show_options(void);
void print_request(int, const vector<int>&, int);
void info_menu(const vector<int>&, int);

int main(void) {
    vector<int> players = {2, 0, -1, 0, -1, 0, 1};
    int loser_id = -1;
    for(;;)
        info_menu(players, loser_id);

    return 0;
}

/*
 * Implements the info menu.
 * Input: A vector with the players and the id of the last loser.
*/
void info_menu(const vector<int>& vec, int loser_id) {
    int option_given = -1;

    show_options();

    while (1) { // Keep asking until valid input.
        try {
            option_given = get_option(); // get option from user  
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
            cerr << "Error in menu. Try again:\n >> ";
        }
    }

    print_request(option_given, vec, loser_id);
}

// Get an option from user and return it.
int get_option(void) {
    int option = 0;
    cin >> option;
    // Non integer given.
    if (!cin) error("Non valid input type.");
    
    // Player's id is out of range.
    if (option < 1 || option > NUM_OPTIONS) {
        error("Player chosen is out of range.");
    }

    return option;
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