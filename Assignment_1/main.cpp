#include "town_of_salem.h"

int main(void) {
    vector<int> players(NUM_PLAYERS, CIT); 
    int last_loser = -1; // always id
    int phase_outcome = -1; // not always an id 

    // Initialization
    initialization(players);

    /*----- SHOW MENU -----*/
    if (info_menu(players, last_loser) == EOF_CODE) {
        return 1;
    }

    for(;;) {    
        /*----- NIGHT PHASE -----*/
        phase_outcome = night_phase(players);
        if (phase_outcome != -1) last_loser = phase_outcome;
        if (is_over(players)) break;
        
        /*----- SHOW MENU -----*/
        if (info_menu(players, last_loser) == EOF_CODE) {
            return 1;
        }
        
        /*----- DAY PHASE -----*/
        phase_outcome = day_phase(players);
        if (phase_outcome != -1) last_loser = phase_outcome;
        if (is_over(players)) break;

        /*----- SHOW MENU -----*/
        if (info_menu(players, last_loser) == EOF_CODE) {
            return 1;
        }
    }

    return 0;
}