// Implement the night phase.
#include "std_lib_facilities.h"

#define NUM_PLAYERS 7
#define CIT 0
#define DOC 1
#define GANG 2
#define LOSER -1

#define EOF_CODE -100

class EOF_error{};

bool in_vector(const int&, const vector<int>&);
void print_vec(const vector<int>&);
bool is_int(string);
// self_id is an optional argument.
int get_player_id(const vector<int>&, int self_id = -1);
int get_valid_id(const vector<int>&, int self_id = -1);
int night_phase(vector<int>& vec);

int main(void) {
    vector<int> players = {2, 0, -1, 1, 0, 0, -1};
    int loser_id = 7;

    night_phase(players);
    print_vec(players);

    return 0;
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


// Checks if a value is inside a vector.
bool in_vector(const int& val, const vector<int>& vec) {
    for (int i : vec) {
        if (val == i) return true;
    }
    return false;
}

// Print a vector.
void print_vec(const vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
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