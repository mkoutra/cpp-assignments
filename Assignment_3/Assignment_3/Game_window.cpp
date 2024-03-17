/*
 * CS-150 - Game Window class for Assignment 3.
 * Michail E. Koutrakis
 * Email: m.koutrakis@physics.uoc.gr
 * Github: https://github.com/mkoutra
 * April 2023
*/

/* 
 * We create a GUI for just ONE round, NOT for the complete game.
 * Otherwise, we should've checked if doc was still alive at 
 * night phase as well as if the conditions for ending the game occur. 
 * Also, the rules for voting procedure are simplified, we don't care 
 * about ties among players.
*/

#include "Game_window.h"

// Constructor. Game starts at night phase (no votes attached).
Game_window::Game_window(Point xy, int w, int h, \
                const string& title, vector<Player>& vec)
    :Graph_lib::Window(xy, w, h, title),
    is_day(false),
    gang_pick(-1),
    doc_pick(-1),
    doc_id(-1),
    day_voters(vec.size()),
    cir_center(700/2, 410/2 + 15), // Background pic is 700*410 pixels
    t(Point(100, 20), "Night Phase begins! Gangster choose a player."),//35
    err_t(Point(70, y_max() - 20), ""),
    pl_vec(vec),
    background_img(new Image(Point(1,1), "Night.jpg")),  
    submit_but(Point(x_max() - 100, y_max() - 35), 70, 25, "Submit", cb_submit),
    submit_box(Point(x_max() - 180, y_max() - 35), 70, 25, "Player ID"),
    quit_but(Point(1, y_max() - 35), 50, 20, "Quit", cb_quit)
{
    // Setup text
    t.set_font(Graph_lib::Font::times_bold);
    t.set_font_size(18);
    t.set_color(Color::white);
    err_t.set_font(Graph_lib::Font::times_bold);
    err_t.set_font_size(12);
    err_t.set_color(Color::red);

    // Fill vectors. 
    fill_loc_imgs(cir_center, 165); // locations of image centers
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
    attach(err_t);                  // Error text

    // Find doctor's id
    doc_id = find_roles_id("DOCTOR", vec);
}

//Destructor. Deallocate all objects created with new.
Game_window::~Game_window() {
    delete background_img;
    for(int i = 0; i < pl_vec.size(); ++i) {
        delete pl_imgs[i];
        delete t_ids[i];
        delete t_votes[i];
    }
}

/* -------------- SETTERS -------------- */

// Change text at the top of window.
void Game_window::set_text(const string& s) {
    t.set_label(s);
    put_on_top(t);
    redraw();
}

// Change error text
void Game_window::set_err_t(const string& s) {
    err_t.set_label(s);
    put_on_top(err_t);
    redraw();
}

// Changes between phases and redraws.
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

/* -------------- FILL VECTORS -------------- */ 

// Find the coordinates of points evenly spaced on circle(c,r).
void Game_window::fill_loc_imgs(Point c, int r) {
    for (int i = 0; i < pl_vec.size(); ++i) {
        loc_imgs.push_back(circle_point(c, r, i * 360/pl_vec.size()));
    }
}

// Fill vector of ids. The caller is responsible for deallocation.
void Game_window::fill_t_ids() {
    int id;
    Text* t_id; // Text of id.

    for (int i=0; i < pl_vec.size(); ++i) {
        id = pl_vec[i].get_id();
        t_id = new Text(Point(loc_imgs[i].x - 26, loc_imgs[i].y - 13), 
                                                        "#" + to_string(id));
        (*t_id).set_font(Graph_lib::Font::times_bold);
        (*t_id).set_font_size(13);
        t_ids.push_back(t_id);
    }
}

// Fill vector of number of votes. The caller is responsible for deallocation.
void Game_window::fill_t_votes() {
    int num;
    Text* t_v; // Text of votes.

    for (int i=0; i < pl_vec.size(); ++i) {
        num = pl_vec[i].get_cur_votes();
        t_v = new Text(Point(loc_imgs[i].x + 15, loc_imgs[i].y - 13), 
                                                            to_string(num));
        (*t_v).set_font(Graph_lib::Font::times_bold);
        (*t_v).set_font_size(13);
        t_votes.push_back(t_v);
    }
}

/* 
 * Fill the vector containing the image pointers with images.
 * The caller is responsible for deallocation.
*/
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

/* -------------- ATTACH / DETACH -------------- */

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

//Refresh t_votes and reattach them on the window.
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

/* -------------- CALLBACK FUNCTIONS -------------- */

/* 
 * Check validity of the vote given by user, returns 0 means success.
 * Input box method .get_int() always returns an integer 
 * (for non valid input it returns -999999).
*/
int Game_window::check_validity(int id_given) {
    
    // Round is over.
    if (day_voters == 0) {
        set_err_t("The round is over.");
        return -1;
    }

    // Not valid input
    if (id_given <= 0) {
        set_err_t("Invalid input.");
        return -1;
    }

    // Out of range
    if (id_given > pl_vec.size()) {
        set_err_t("ID is out of range.");
        return -1;
    }

    // Dead player was chosen
    if (pl_vec[id_given - 1].get_status() == false) {
        set_err_t("ID of dead player.");
        return -1;
    }

    return 0;
}

// Callback for submit button.
void Game_window::cb_submit(Address, Address pw) {
    reference_to<Game_window>(pw).submit();
}

// Callback for quit button.
void Game_window::cb_quit(Address, Address pw) {
    reference_to<Game_window>(pw).quit();
}

// What happens when submit is pressed.
void Game_window::submit(void) {
    int vote_id = submit_box.get_int();
    // Check vote validity
    if (check_validity(vote_id) == -1) return ; 
    else set_err_t("");

    // Night phase
    if (!is_day) {
        // Gangster votes
        if (gang_pick == -1) {
            gang_pick = vote_id;
            set_text("Doctor, its your turn to choose.");
            return ;
        }

        // Doctor votes only if gangster has already voted.
        if (gang_pick != -1 && doc_pick == -1) {
            // Doctor cannot vote himself.
            if (vote_id == doc_id) {
                set_err_t("Doctor cannot vote himself.");
                return ;
            }
            doc_pick = vote_id;
        }

        // Both have voted
        if (gang_pick != -1 && doc_pick != -1) {
            // Gangster's choice leaves
            if (gang_pick != doc_pick) { 
                remove_player(gang_pick); // kick player out
                day_voters--; // the player kicked won't vote at day phase

                string msg_n_to_d = "Day phase begins! Player #" + \
                                     to_string(gang_pick) + " left at night.";
                set_day(true);
                set_text(msg_n_to_d);
            }
            // Nobody leaves
            else { 
                set_day(true);
                string msg_n_to_d = "Day phase begins! Doctor saved Player #" + \
                                     to_string(gang_pick) + ".";
                set_text(msg_n_to_d);
            }
        }

    }
    // Day phase
    else {
        static int voter = 1; // Player voted at previous phase
        pl_vec[vote_id -1].increase_cur_votes(); // increase vote of player picked
        refresh_votes(); // refresh votes on window
        day_voters--; // One less player to vote

        // If (voter's id) == (id of the player left at night) --> increase id
        if ((gang_pick != doc_pick) && (voter == gang_pick)) ++voter;

        string msg_day = "Player #" + to_string(voter++) + \
                         " voted Player #" + to_string(vote_id) + ".";
        set_text(msg_day);

        if (day_voters == 0) { // No player left to vote
            int out_id = most_votes(pl_vec);
            string msg_end_of_round = "Round is Over! Player #" \
                                       + to_string(out_id) + " left.";
            set_text(msg_end_of_round);
            remove_player(out_id);
        }
    }

    redraw();
}


/* ----- HELPER FUNCTIONS ----- */

/*
 * Returns the point of a circle with center c (x0, y0), 
 * radius r, located at theta degrees relative to x axis.
 * Parametric equation :
 * [x, y] = [x0, y0] + r * [cos(theta), sin(theta)]
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
 * The caller is responsible for deallocation.
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

/* 
 * Returns the id of the player with the role given, otherwise -1.
 * WARNING: s_role must be given in uppercase only. 
*/
int find_roles_id(const string& s_role, const vector<Player>& pl_vec) {
    for (const Player& pl : pl_vec) {
        if (pl.get_role() == s_role) return pl.get_id();
    }
    return -1;
}
