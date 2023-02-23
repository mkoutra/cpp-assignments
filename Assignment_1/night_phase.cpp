// Implement the night phase.
#include "std_lib_facilities.h"
#include <limits.h>

#define NUM_PLAYERS 7
#define CIT 0
#define DOC 1
#define GANG 2
#define LOSER -1

void print_vec(const vector<int>&);
void dashed_line(int);
int get_player_id(const vector<int>&);
int get_doctor_save(const vector<int>&, int);
int night_phase(vector<int>& vec);

int main(void) {
    vector<int> players = {2, 0, -1, 0, 0, 0, -1};
    int loser_id = 7;

    night_phase(players);
    print_vec(players);

    return 0;
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