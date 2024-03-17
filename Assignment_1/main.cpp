/*
 * Main function for assignment 1.
 * 
 * Michail E. Koutrakis
 * Email: m.koutrakis@physics.uoc.gr
 * Github: https://github.com/mkoutra
 * March 2023
*/

#include "town_of_salem.h"

int main(void) {
    vector<int> players(NUM_PLAYERS, CIT); 
    int last_loser = -1; // is always an id.
    int phase_outcome = -1; // isn't always an id. 

    // Initialization
    initialization(players);

    try {
        while(!is_over(players)) {    
            info_menu(players, last_loser);// Show the menu
            
            // Night phase. If someone leaves, update last_loser.
            phase_outcome = night_phase(players);
            if (phase_outcome != -1) last_loser = phase_outcome;
            
            // Check if the game is over.
            if (is_over(players)) break;

            // Day phase. If someone leaves, update last_loser.
            phase_outcome = day_phase(players);
            if (phase_outcome != -1) last_loser = phase_outcome;
        }
        return 0;
    }
    catch (EOF_error) {
        cerr << "EOF\n";
        return 1;
    }
}