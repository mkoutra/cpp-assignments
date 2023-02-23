/*
 * Create a function that initializes the players assigning the gangster 
 * and the doctor randomly.
 * 
 * Each player is represented as a vector element.
 * The value of each element represents the role of each player.
 * Citizen --> 0, Doctor --> 1, Gangster --> 2. 
*/
#include "std_lib_facilities.h"

#define NUM_PLAYERS 7
#define CIT 0
#define DOC 1
#define GANG 2

void initialization(vector<int>& vec);
void print_vec(vector<int>& vec);

int main(void) {
    //vector<int> players(NUM_PLAYERS, 0); // 7 places full of zeroes
    vector <int> players(NUM_PLAYERS);

    initialization(players);
    print_vec(players);

    return 0;
}

/*
 * Input: A vector that represents the players.
 * Chooses the role of each player randomly.
*/
void initialization(vector<int>& vec) {
    try {
    fill(vec.begin(), vec.end(), 0);// Fill vec with zerores.
    
    // Generate random integers from [0,7).
    srand(time(NULL)); // random seed
    int gang_idx = rand() % NUM_PLAYERS; // index for gangster.
    int doc_idx = rand() % NUM_PLAYERS; // index for doctor.
    
    // If doc_idx != gang_idx generate a new int for doc_idx.
    while (doc_idx == gang_idx) {
        doc_idx = rand() % NUM_PLAYERS;
    }

    vec[doc_idx] = DOC; // Doctor
    vec[gang_idx] = GANG; // Gangster

    }
    catch (out_of_range) {// In vector has wrong size.
        vec.resize(NUM_PLAYERS);// resize to corerct size.
        fill(vec.begin(), vec.end(), 0); // Fill with zerores.

        initialization(vec);// call initialization again
    }
}

void print_vec(vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
}