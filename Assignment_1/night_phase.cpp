/*
 * Implement the night phase.
 * 
 * Each player is represented as a vector element.
 * The value of each element represents the role of each player.
 * Citizen --> 0, Doctor --> 1, Gangster --> 2, Lost --> -1. 
*/
#include "std_lib_facilities.h"
#include <limits.h>

#define NUM_PLAYERS 7

class Bad_input_type_error{};
class Player_out_of_range_error{};
class Player_is_out_error{};
class Player_himself_error{};

int night_phase(vector<int>& vec);
int read_player_number(vector<int>& vec, int self_number);
void dashed_line(int size);
void print_vec(vector<int>& vec);

int main(void) {
    vector<int> players(7, 0);
    players[2] = 1;
    players[3] = 2;

    int loser_index = 6;
    players[loser_index] = -1;

    night_phase(players);

    print_vec(players);

    return 0;
}

/* 
 * Implements night phase. Returns the index of the 
 * player which lost. Returns -1 if there is no such a player.
*/
int night_phase(vector<int>& vec) {
    int gang_choice = -1, doc_choice = -1;
    int gang_number = -1, doc_number = -1; // Player's number, NOT index.
    
    cout << "--- Night phase ---" << endl;
    
    // Find the position of gangster and doctor.
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == 2) {// Gangster position
            gang_number = i + 1;
        }
        if (vec[i] == 1) {// Doctor position
            doc_number = i + 1;
        }
    }

    cout << "Gangster is Player #" << gang_number << endl;
    cout << "Doctor is Player #" << doc_number << endl;

    while (1) {
        try {
            cout << "Gangster, give the number of the player you want out: ";
            gang_choice = read_player_number(vec, gang_number);
            break;
        }
        catch (Bad_input_type_error) {
            // Clear cin's error flags and input buffer.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cerr << "Bad_input_type_error. Please try again.\n" << endl;
        }
        catch (Player_out_of_range_error) {
            cerr << "\nPlayer_out_of_range_error. Please try again." << endl;
        }
        catch (Player_is_out_error) {
            cerr << "\nPlayer_is_out_error. Please try again." << endl;
        }
        catch (Player_himself_error) {
            cerr << "\nPlayer_himself_error. Please try again." << endl;
        }
    }

    while (1) {
        try {
            cout << "Doctor, give the number of the player you want to save: ";
            doc_choice = read_player_number(vec, doc_number);
            break;
        }
        catch (Bad_input_type_error) {
            // Clear cin's error flags and input buffer.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cerr << "\nBad_input_type_error. Please try again:" << endl;
        }
        catch (Player_out_of_range_error) {
            cerr << "\nPlayer_out_of_range_error. Please try again:" << endl;
        }
        catch (Player_is_out_error) {
            cerr << "\nPlayer_is_out_error. Please try again:" << endl;
        }
        catch (Player_himself_error) {
            cerr << "\nPlayer_himself_error. Please try again." << endl;
        }
    }

    if (gang_choice == doc_choice) {
        return -1;
    }
    else {
        vec[gang_choice - 1] = -1; // Change the vector containing the players.
        return gang_choice - 1; // -1 because we want index.
    }

}

/*
 * Reads and returns a player's number from standard input.
 * CAREFUL: It returns the number (#) NOT the index.
*/
int read_player_number(vector<int>& vec, int self_number) {
    int player_chosen = -1;
    cin >> player_chosen;

    if (!cin) {// Check if the user gave an integer.
        throw Bad_input_type_error();
    }

    if (player_chosen < 1 || player_chosen > NUM_PLAYERS) {// Player's number is out of range.
        throw Player_out_of_range_error();
    }

    if (vec[player_chosen - 1] == -1) {// The player chosen is already out.
        throw Player_is_out_error();
    }

    if (player_chosen == self_number) {// The player chose himself.
        throw Player_himself_error();
    }

    return player_chosen;
}

// Prints a dashed line with size `size` and a new line character.
void dashed_line(int size) {
    while (size--) cout << '-';
    cout << '\n';
}

void print_vec(vector<int>& vec) {
    for (int i=0; i<vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
}