#include "std_lib_facilities.h"
#include "Player.h"

#ifndef ROUND_H
#define ROUND_H

#define NUM_OPTIONS 4
class Round {
    public:
        Round(int, string, string);
        Round(int);
        Round();

        // Setters
        void set_round(int);
        void set_pl_night(string);
        void set_pl_day(string);

        // Getters
        int get_round() const { return n_round; }
        string get_pl_night() const { return pl_night; }
        string get_pl_day() const { return pl_day; }

    private:
        int n_round; // number of round.
        string pl_night; // id of player sent out at night phase.
        string pl_day; // id of player sent out at day phase.

};

// "put to" operator
ostream& operator<<(ostream &ost, Round& rr);

// Check if game is over
bool is_over(const vector<Player>& pl_vec);

// Menu functions
void dashed_message(string);
void underline_message(string);
bool is_int(string);
int get_option(void);
void print_request(int, const vector<Player>&, const int);
void info_menu(const vector<Player>& , int );

#endif // ROUND_H