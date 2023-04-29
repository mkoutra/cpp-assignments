#include "std_lib_facilities.h"

#ifndef PLAYER_H
#define PLAYER_H
class EOF_error{};

class Player {
    public:
        // Constructors
        Player(string Name, bool isAlive, string Role);
        Player();

        // Voting procedure
        void increase_cur_votes();
        void decrease_cur_votes();
        
        void vote(vector<Player>&);
        void downvote(vector<Player>&);
        
        void go_out(vector<Player>&);

        // Setters
        void set_name(string);
        void set_status(bool);
        void set_role(string);
        void set_cur_votes(int);
        void set_cand(bool);// change the candidate status
        
        // Getters. Can't modify the object (const).
        string get_name() const { return name; }
        bool get_status() const { return alive; }
        string get_role() const { return role; }
        int get_cur_votes() const { return current_votes; }
        int get_id() const { return id; } 
        int get_n_players() const { return n_players; } // all players 
        bool get_cand() const { return candidate; }// candidate status
        
        string full_name() const;

    private:
        string name;
        bool alive;
        string role;
        int current_votes;

        int id; // Player's id
        static int n_players;// Number of players created
        bool candidate;// true if player can be voted.
};

// "put to" operator
ostream& operator<<(ostream& ost, Player& pl);

// Helper functions
bool is_int(string s);
string str_to_upper(string s);

// Initialization from file.
void init_from_file(vector<Player> &pl_vec, string fname);

// Functions that modify the vector containing all the players.
void reset_votes(vector<Player>& pl_vec);
void no_candidate(vector<Player>& pl_vec);
void all_candidates(vector<Player>& pl_vec);
int find_max(vector<Player>&);

// Take input from user.
int read_vote(const vector<Player>& pl_vec);
int read_valid_vote(const vector<Player>& pl_vec);

// Game phases.
int night_phase(vector<Player>& pl_vec);
int day_phase(vector<Player>& pl_vec);

#endif // PLAYER_H