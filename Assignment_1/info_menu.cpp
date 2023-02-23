/*
 * Create a menu that will appear before the start of each cycle.
 * 
 * Each player is represented as a vector element.
 * The value of each element represents the role of each player.
 * Citizen --> 0, Doctor --> 1, Gangster --> 2, Lost --> -1. 
*/
#include "std_lib_facilities.h"
#include <limits.h>

#define NUM_PLAYERS 7
#define CIT 0
#define DOC 1
#define GANG 2
#define LOSER -1

void dashed_line(int size);
string role(int digit);
int get_option(void);
void show_options(void);
void print_request(int, const vector<int>&, int);
void info_menu(const vector<int>&, int);

int main(void) {
    vector<int> players = {2, 0, 1, 0, 0, 0, -1};
    int loser_id = 7;

    info_menu(players, loser_id);

    return 0;
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

// Prints a dashed line with the given size.
void dashed_line(int size) {
    cout << string(size, '-') << endl;
}