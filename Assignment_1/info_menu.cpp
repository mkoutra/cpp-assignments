/*
 * Create a menu that will appear before the start of each cycle.
 * 
 * Each player is represented as a vector element.
 * The value of each element represents the role of each player.
 * Citizen --> 0, Doctor --> 1, Gangster --> 2, Lost --> -1. 
*/
#include "std_lib_facilities.h"

#define NUM_PLAYERS 7

class Bad_menu_input{};

void info_menu(vector<int>& vec, int loser_idx);
void show_options(void);
int get_option(void);

void print_still_playing(vector<int>& vec);
void print_playing_roles (vector<int>& vec);
void print_losers (vector<int>& vec);
void print_last_loser(vector<int> vec, int loser_idx);

string role(int digit);
void dashed_line(int size);

int main(void) {
    vector<int> players(7, 0);
    players[2] = 1;
    players[0] = 2;

    int loser_index = 6;
    players[loser_index] = -1;
    
    info_menu(players, loser_index);

    return 0;
}


void info_menu(vector<int>& vec, int loser_idx) {
    show_options();

    int choice = 0;

    while (1) {// Keep asking user until they give valid input.
        try {
            choice = get_option();
            break;
        }
        catch (Bad_menu_input) {
            cerr << "Bad_menu_input. Please try again. ";
        }
    }

    switch(choice) {
        case 1: 
            print_still_playing(vec);
            break;
        case 2: 
            print_playing_roles(vec);
            break;
        case 3: 
            print_losers(vec);
            break;
        case 4: 
            print_last_loser(vec, loser_idx);
            break;
        default:
            cerr << "Please enter a valid digit: ";
    }

}

// Shows the menu options.
void show_options(void) {
    dashed_line(9); // 9 is the length of "INFO MENU"
    cout << "INFO MENU" << endl;
    dashed_line(9);

    cout << "1. Players in the game." << endl;
    cout << "2. Players in the game and their roles." << endl;
    cout << "3. Players that have lost." << endl;
    cout << "4. Last player that lost." << endl;
    cout << "\nType the number of your option [1-4] and press [Enter]: ";
}

// Get menu-option from user.
int get_option(void) {
    int option = 0;

    if ( !(cin >> option) || option < 1 || option > 4) {
        cerr << "\nBad input in menu. Please try again.\n";
        throw Bad_menu_input();
    };

    return option;
}

/*
 * Prints a line with the players that are still 
 * in the game with two dashed lines above and below.
 */
void print_still_playing (vector<int>& vec) {
    /* 
     * Save the whole output-line in a string.
     * With .size() the correct input to the dashed_line() is given.
    */
    string s = "Players still playing: | "; 
    
    // Concatenate
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != -1) {
            s += "#" + to_string(i + 1) + " | ";
        }
    }

    // Print output
    dashed_line(s.size());
    cout << s << endl;
    dashed_line(s.size());
}

/*
 * Prints a line with the roles of each player that is still 
 * in the game. Also, prints one dashed line above and below the main line.
 */
void print_playing_roles (vector<int>& vec) {
    /* 
     * Save the whole output-line in a string.
     * With .size() the correct input to the dashed_line() is given.
    */
    string s = "Players & Roles: | ";

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] != -1) {
            s += "#" + to_string(i + 1) + " " + role(vec[i]) + " |";
        }
    }

    // Print output
    dashed_line(s.size());
    cout << s << endl;
    dashed_line(s.size());
}

/*
 * Prints a line with the losers. 
 * Also, prints one dashed line above and below the main line.
 */
void print_losers (vector<int>& vec) {
    /* 
     * Save the whole output-line in a string.
     * With .size() the correct input to the dashed_line() is given.
    */
    string s = "Players out of the game: | ";

    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] == -1) {
            s += "#" + to_string(i + 1) + " |";
        }
    }

    // Print output
    dashed_line(s.size());
    cout << s << endl;
    dashed_line(s.size());
}

/*
 * Prints a line with the last player that lost. 
 * Also, it prints one dashed line above and below.
 */
void print_last_loser(vector<int> vec, int loser_idx) {
    string s = "Last Player that lost: | #" + to_string(loser_idx + 1) + " |";

    // Print output
    dashed_line(s.size());
    cout << s << endl;
    dashed_line(s.size());
}

/*
 * Returns the role that corresponds to the integer given:
 * 0 --> Citizen, 1 --> Doctor, 2 --> Gangster, -1 --> Lost. 
 */
string role(int digit) {
    switch(digit) {
        case 0: 
            return "Citizen";
            break;
        case 1:
            return "Doctor";
            break;
        case 2:
            return "Gangster";
            break;
        case -1:
            return "Lost";
            break;
        default:
            throw out_of_range("print_role() out of range.\n");
    }
}

// Prints a dashed line with size `size` and a new line character.
void dashed_line(int size) {
    while (size--) cout << '-';
    cout << '\n';
}