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

#define EOF_CODE -100

class EOF_error{};

void dashed_message(string);
bool in_vector(const int&, const vector<int>&);
string role(int);

bool is_int(string s);
int get_option(void);
void show_options(void);
void print_request(int, const vector<int>&, int);
int info_menu(const vector<int>&, int);

int main(void) {
    vector<int> players = {2, 0, -1, 0, -1, 0, 1};
    int loser_id = -1;
    for(;;)
        if (info_menu(players, loser_id) == EOF_CODE) {
            return 1;
        }

    return 0;
}

/*
 * Implements the info menu.
 * Input: A vector with the players and the id of the last loser.
 * Returns 0 for success otherwise EOF_CODE. 
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