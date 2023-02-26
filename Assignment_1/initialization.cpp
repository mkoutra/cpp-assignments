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
 * Modifies the input vector by randomly choosing the role of each player. 
*/
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

void print_vec(vector<int>& vec) {
    for (int i = 0; i < vec.size(); ++i) {
        cout << vec[i] << ' ';
    }
    cout << '\n';
}