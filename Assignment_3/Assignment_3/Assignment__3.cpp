/*
 * CS-150 - Main for Assignment 3.
 * Michail E. Koutrakis
 * Email: m.koutrakis@physics.uoc.gr
 * Github: https://github.com/mkoutra
 * April 2023
*/

#include "Game_window.h"

int main()
{
    string input_fname = "Players.txt"; 

    // Define and initialize players.    
    vector<Player> players; 
    init_from_file(players, input_fname);
    
    // Create the game window for a single round.
    Game_window gwin(Point(100, 100), 700, 450, "Single round", players);
    gui_main();

    // Reset votes and alive status for all players
    reset_votes(players);
    for (Player& pl : players) pl.set_status(true);
    
    /* ---------- GAME AS IN ASSIGNMENT 2 ----------*/

    string output_fname = "TownOfSalem_output.txt";

    int night_id = -1, day_id = -1; // id of players left at each phase
    int num_round = 1; // number of round
    
    ofstream ofst(output_fname); // Output file
    
    ofst << "Round #, Player left at Night phase, Player left at Day phase\n";
    ofst << string(62, '-') << '\n';// 62 is the size of the above string.

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
        std::cerr << "EOF\n";
        return 1;
    }
}
