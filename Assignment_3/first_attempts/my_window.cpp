// IMPORTANT NOTE: Image objects are Shapes and NOT Widgets. 
// So hide, redraw() etc are not applicable for them.

// The NOGDI below is needed to prevent Windows from including wingdi.h which has a duplicate
// declaration of 'Polygon' and throws ambiguous error.
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define NOGDI
#endif

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "Player.h"
#include "Round.h"
#include <iostream>

using namespace Graph_lib;   // our graphics facilities are in Graph_lib
//------------------------------------------------------------------------------

// Helper functions

/*
 * Returns the point of a circle with center c, 
 * radius r, located at theta degrees relative to x axis.
*/
Point circle_point(Point c, int r, int theta) {
    float x_coord = r * cos(theta * M_PI / 180) + c.x;
    float y_coord = r * sin(theta * M_PI / 180) + c.y;

    return Point((int) x_coord, (int) y_coord);
}

/*
 * Returns an image object whose center is placed on Point p.
 * imx and imy are the size of the image in pixels
 * i_name is the name of the image.
*/
Image* image_center(Point p, string i_name, int imx, int imy) {
    return new Image(Point(p.x - imx/2, p.y - imy/2), i_name);
}

/* 
 * Find the alive player with most votes. 
 * In case of a tie, return the one found first.
*/
int most_votes(const vector<Player>& pl_vec) {
    int max = 0, max_id = 0;

    for (const Player& pl : pl_vec) {
        // Check only alive players
        if (pl.get_status() && (pl.get_cur_votes() > max)) {
            max = pl.get_cur_votes();
            max_id = pl.get_id();
        }
    }

    return max_id;
}

//------------------------------------------------------------------------------

struct Game_window : Graph_lib::Window {
    Game_window(Point xy, int w, int h, const string& title, vector<Player>& vec);
    
    private:
        bool is_day; // true if day phase
        void set_day(bool dday);

        int gang_pick, doc_pick; // for night phase
        int day_voters; // players still to vote

        // Center of window 
        Point win_center; 

        // Text inside window
        Text t;
        void set_text(const string&);

        // Vectors
        vector<Player>& pl_vec; // Players
        vector<Image*> pl_imgs; // Player images
        vector<Point> loc_imgs; // Location of the center of each image
        vector<Text*> t_ids; // Texts of ids
        vector<Text*> t_votes; // Texts of votes
        
        // Fill vectors
        void fill_pl_imgs(); // Fill with images.
        void fill_loc_imgs(Point c, int r); // Fill with points.
        void fill_t_ids(); // fill with texts of ids.
        void fill_t_votes(); // fill with texts of votes.

        // Images and ids
        void attach_imgs();
        void detach_imgs();
        void attach_ids();
        void detach_ids();

        // Put images and ids on top of the window
        void put_imgs_ids_on_top();

        // Votes
        void attach_votes();
        void detach_votes();
        void refresh_votes();

        // Remove player
        void remove_player(int id);

        // Background pic
        Image* background_img;

        // Submit 
        Button submit_but; // Widget
        In_box submit_box; // Widget
        static void cb_submit(Address, Address); // callback
        void submit();

        // Quit
        Button quit_but;
        static void cb_quit(Address, Address); // callback
        void quit() { hide(); } 
        
};

// Constructor. Game starts at night phase.
Game_window::Game_window(Point xy, int w, int h, \
                const string& title, vector<Player>& vec)
    :Graph_lib::Window(xy, w, h, title),
    is_day(false),
    gang_pick(-1),
    doc_pick(-1),
    day_voters(vec.size()),
    background_img(new Image(Point(1,1), "Night.jpg")),  
    submit_but(Point(x_max() - 100, y_max() - 35), 70, 25, "Submit", cb_submit),
    submit_box(Point(x_max() - 180, y_max() - 35), 70, 25, "Player ID"),
    quit_but(Point(1, y_max() - 35), 50, 20, "Quit", cb_quit),
    t(Point(100, 35), "Night Phase begins! Gangster pick a player..."),
    pl_vec(vec),
    win_center(x_max() / 2, y_max() / 2)
{
    // Setup text
    t.set_font(Graph_lib::Font::times_bold);
    t.set_font_size(18);
    t.set_color(Color::white);

    // Fill vectors. 
    fill_loc_imgs(win_center, 150); // location of image center
    fill_pl_imgs();                 // images 
    fill_t_ids();                   // text ids
    fill_t_votes();                 // text votes

    // Attach objects on window
    attach(*background_img);        // Background image
    attach(t);                      // Text
    attach(submit_but);             // Submit button
    attach(submit_box);             // Submit input box
    attach_imgs();                  // Player images
    attach_ids();                   // Text ids
    attach(quit_but);               // Quit button
}

/* ----- SETTERS ----- */

// Change window text and redraw.
void Game_window::set_text(const string& s) {
    t.set_label(s);
    put_on_top(t);
    redraw();
}

// Changes between phases and redraws the appropriate window.
void Game_window::set_day(bool dday) {
    is_day = dday;
    
    // Change background picture and attach it on window.
    string img_fname;
    (dday) ? (img_fname = "Day.jpg") : (img_fname = "Night.jpg");
    delete background_img; // deallocate previous image
    background_img = new Image(Point(1, 1), img_fname);
    attach(*background_img);
    
    // Bring pl_images and ids back on top.
    put_imgs_ids_on_top();
    
    // Votes are displayed only at day_phase.
    (dday) ? (attach_votes()) : (detach_votes());
    
    redraw();
}

/* ----- FILL VECTORS ----- */ 

// Find the coordinates of points evenly spaced on circle(c,r).
void Game_window::fill_loc_imgs(Point c, int r) {
    for (int i = 0; i < pl_vec.size(); ++i) {
        loc_imgs.push_back(circle_point(c, r, i * 360 / pl_vec.size()));
    }
}

// Fill vector of ids.
void Game_window::fill_t_ids() {
    int id;
    Text* t_id; // Text of id.

    for (int i=0; i < pl_vec.size(); ++i) {
        id = pl_vec[i].get_id();
        t_id = new Text(Point(loc_imgs[i].x - 25, loc_imgs[i].y - 13), to_string(id));
        (*t_id).set_font(Graph_lib::Font::times_bold);
        (*t_id).set_font_size(14);
        t_ids.push_back(t_id);
    }
}

// Fill vector of number of votes.
void Game_window::fill_t_votes() {
    int num;
    Text* t_v; // Text of votes.

    for (int i=0; i < pl_vec.size(); ++i) {
        num = pl_vec[i].get_cur_votes();
        t_v = new Text(Point(loc_imgs[i].x + 15, loc_imgs[i].y - 13), to_string(num));
        (*t_v).set_font(Graph_lib::Font::times_bold);
        (*t_v).set_font_size(14);
        t_votes.push_back(t_v);
    }
}

// Fill the vector containing the image pointers with images. 
void Game_window::fill_pl_imgs() {
    string img_fname; // Image filename
    Image* ii;

    for (int i = 0; i < pl_vec.size(); ++i) {
        // Find the file that corresponds to each role.
        if (pl_vec[i].get_role() == "GANGSTER") img_fname = "Gangster.jpg";
        else if (pl_vec[i].get_role() == "DOCTOR") img_fname = "Doctor.jpg";
        else img_fname = "Civilian.jpg";

        // Create an image whose center is placed on loc_imgs[i]
        ii = image_center(loc_imgs[i], img_fname, 50, 50);
        
        // Fill the vector of pointers pl_imgs.
        pl_imgs.push_back(ii);
    }
}

/* ----- ATTACH / DETACH ----- */

// Attach images of alive players on window.
void Game_window::attach_imgs() {
    for (int i = 0; i < pl_imgs.size(); ++i) {
        if (pl_vec[i].get_status()) attach(*pl_imgs[i]);
    }
}

// Detach all player images from window.
void Game_window::detach_imgs() {
    for (int i = 0; i < pl_imgs.size(); ++i) detach(*pl_imgs[i]);
}

// Attach ids of alive players.
void Game_window::attach_ids() {
    for (int i = 0; i < t_ids.size(); ++i) {
        if (pl_vec[i].get_status()) attach(*t_ids[i]);
    }
}

// Detach ids.
void Game_window::detach_ids() {
    for (int i = 0; i < t_ids.size(); ++i) detach(*t_ids[i]);
}

// Attach votes of alive players.
void Game_window::attach_votes() {
    for (int i = 0; i < t_votes.size(); ++i) {
        if (pl_vec[i].get_status()) attach(*t_votes[i]);
    }
}

// Detach votes.
void Game_window::detach_votes() {
    for (int i = 0; i < t_votes.size(); ++i) detach(*t_votes[i]);
}

/*
 * Refresh t_votes and reattach them on the window.
*/
void Game_window::refresh_votes() {
    // Detach votes and deallocate memory
    for (int i = 0; i < t_votes.size(); ++i) {
        detach(*t_votes[i]);
        delete t_votes[i];
    }
    // Still, t_votes.size() == pl_vec.size().

    //Bring t_votes to initial state with zero length.
    // Necessary because fill_t_votes() uses .push_back().
    t_votes.resize(0);
    
    // Refill t_votes with (probably) new votes.
    fill_t_votes();

    // Attach the new votes
    attach_votes();
}

// Bring images and ids of alive players on top.
void Game_window::put_imgs_ids_on_top() {
    for (int i=0; i < pl_vec.size(); ++i) {
        if (pl_vec[i].get_status() == true) {
            put_on_top(*pl_imgs[i]);
            put_on_top(*t_ids[i]);
        }
    }
}

// Kill the player, detach its info and redraw.
void Game_window::remove_player(int id) {
    // Detach image, id, votes
    detach(*pl_imgs[id-1]);
    detach(*t_ids[id-1]);
    detach(*t_votes[id-1]);

    // kill the player
    pl_vec[id-1].set_status(false); 

    redraw();
}

/* ----- CALLBACK FUNCTIONS ----- */
void Game_window::cb_submit(Address, Address pw) {
    reference_to<Game_window>(pw).submit();
}

// NOTE: For this assignment we need just one round. 
// Differently, we should've checked if doc was still alive.
void Game_window::submit(void) {
    int vote_id = submit_box.get_int();
    // Night phase
    if (!is_day) {
        // Gangster votes
        if (gang_pick == -1) {
            // TODO: check validity of id
            gang_pick = vote_id;
            set_text("Gangster has chosen. Doctor, its your turn to pick...");
            return ;
        }

        // Doctor votes only if gangster has voted.
        if (gang_pick != -1 && doc_pick == -1) {
            // TODO: Check validity (doc cant vote himself)
            doc_pick = vote_id;
        }

        // Both have voted
        if (gang_pick != -1 && doc_pick != -1) {
            if (gang_pick != doc_pick) { // Gangster's choice leaves
                remove_player(gang_pick); // kick player out
                day_voters--; // the player kicked won't vote

                string msg_n_to_d = "Day phase begins! Player #" + \
                                     to_string(gang_pick) + " left at night.";
                set_day(true);
                set_text(msg_n_to_d);
            }
            else { // Nobody leaves
                set_day(true);
                set_text("Day phase begins! Nobody left at night.");
            }
        }

    }
    // Day phase
    else {
        if (day_voters == 0) {
            set_text("Round is over!");
            return;
        }
        // TODO: check validity

        pl_vec[vote_id -1].increase_cur_votes();
        refresh_votes();
        day_voters--; 

        // Text stuff
        static int voter = 1;
        if ((gang_pick != doc_pick) && (voter == gang_pick)) ++voter;
        string msg_day = "Player #" + to_string(voter++) + \
                         " voted Player #" + to_string(vote_id) + ".";
        set_text(msg_day);

        // When all alive players have voted.
        if (day_voters == 0) remove_player(most_votes(pl_vec));
    }

    redraw();
}

// Callback functions
void Game_window::cb_quit(Address, Address pw) {
    reference_to<Game_window>(pw).quit();
}

/* ----- GAME -----*/
int game() {
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
        std::cerr << "EOF\n";
        return 1;
    }
}

int main()
{
    string input_fname = "Players.txt"; 
    
    vector<Player> players; 
    // Initialization
    init_from_file(players, input_fname);
    
    Game_window gwin(Point(100, 100), 700, 450, "Single round", players);
    gui_main();

    // Reset votes and alive status
    reset_votes(players);
    for (Player& pl : players) pl.set_status(true);
    
    /* ---------- GAME FROM ASSIGNMENT 2 ----------*/

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
