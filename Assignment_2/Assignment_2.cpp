/*
 * CS150 - Main function for Assignment 2 - March 2023
 * Michail E. Koutrakis
 * Email: m.koutrakis@physics.uoc.gr
 * Github: https://github.com/mkoutra
*/

#include "std_lib_facilities.h"
#include "Player.h"
#include "Round.h"

int main(void) {
    string input_fname = "Players.txt";
    string output_fname = "TownOfSalem_output.txt";

    int night_id = -1, day_id = -1; // id of players left at each phase
    int num_round = 1; // number of round
    
    vector<Player> players; // vector containg all the players. 
    
    ofstream ofst(output_fname); // Output file
    
    ofst << "Round #, Player left at Night phase, Player left at Day phase\n";
    ofst << string(62, '-') << '\n';// 62 is the size of the above string.
    
    // Initialization
    init_from_file(players, input_fname);
    
    try {
        while(1) {
            Round rround(num_round++);
            // Show menu
            info_menu(players, day_id); 
            
            // Night phase. Update rround with the name of the player leaving.
            night_id = night_phase(players);
            if (night_id == -1) { // No player leaves
                rround.set_pl_night(" ");
            } else {
                rround.set_pl_night(players[night_id -1].full_name());
            }
            // Check if the game is over
            if (is_over(players)) {
                ofst << rround << "GAME OVER!\n";
                break;
            }

            // Day phase. Update rround with the name of the player leaving.
            day_id = day_phase(players);
            if (day_id == -1) { // No player leaves
                rround.set_pl_day(" ");
            } else {
                rround.set_pl_day(players[day_id -1].full_name());
            }
            // Check if the game is over
            if (is_over(players)) {
                ofst << rround << "GAME OVER!\n";
                break;
            }

            // Write to file
            ofst << rround;
        }
        return 0;
    }
    catch (EOF_error) {
        cerr << "EOF\n";
        return 1;
    }

    return 0;
}

