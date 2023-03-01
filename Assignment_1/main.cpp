#include "town_of_salem.h"

int main(void) {
    vector<int> players(NUM_PLAYERS, CIT); 
    int last_loser = -1; // always id
    int phase_outcome = -1; // not always an id 

    // Initialization
    initialization(players);

    try {
        while(is_over(players) == false) {    
            // Show menu
            info_menu(players, last_loser);
            
            // Night phase. If someone leaves, update last_loser.
            phase_outcome = night_phase(players);
            if (phase_outcome != -1) last_loser = phase_outcome;
            
            // Check if the game is over.
            if (is_over(players)) break;
            
            // Show menu
            info_menu(players, last_loser);

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