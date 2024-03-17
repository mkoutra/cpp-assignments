/*
 * CS-150 - Header file for Assignment 3.
 * Michail E. Koutrakis
 * Email: m.koutrakis@physics.uoc.gr
 * Github: https://github.com/mkoutra
 * April 2023
*/

// The struct for the game window for our SINGLE round game.

#ifndef GAME_WINDOW_H
#define GAME_WINDOW_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#define NOGDI
#endif

#include "Simple_window.h"    // get access to our window library
#include "Graph.h"            // get access to our graphics library facilities
#include "Player.h"
#include "Round.h"
//#include <iostream>

using namespace Graph_lib;   // our graphics facilities are in Graph_lib

struct Game_window : Graph_lib::Window {
    Game_window(Point xy, int w, int h, const string& title, vector<Player>& vec);
    ~Game_window(); // destructor
    private:
        bool is_day; // true for day phase
        void set_day(bool dday);

        int gang_pick, doc_pick, doc_id; // for night phase
        int day_voters; // players still to vote

        // Center of circle
        Point cir_center; 

        // Text inside window
        Text t;
        void set_text(const string&);
        Text err_t;
        void set_err_t(const string&);

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
        int check_validity(int id_given); // check input validity
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

    // Destructor
        
};

// Helper functions

Point circle_point(Point c, int r, int theta);
Image* image_center(Point p, string i_name, int imx, int imy);
int most_votes(const vector<Player>& pl_vec);
int find_roles_id(const string& s_role, const vector<Player>& pl_vec);

#endif // GAME_WINDOW_H
