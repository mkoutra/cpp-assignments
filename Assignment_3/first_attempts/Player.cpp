#include "Player.h"

/*
 * Checks if a string represents an integer,
 * ignoring leading and trailing whitespaces. 
*/
bool is_int(string s) {
    int i = 0;// for scanning

    //Drop leading whitespaces.
    while(s[0] == ' ' || s[0] == '\t' || s[0]=='\n') {
        s = s.substr(1);
    }

    // Sign check
    if (s[0] == '+' || s[0] == '-') {
        s = s.substr(1);
    }

    // Check if the string given had only whitespaces or '+', '-'.
    if (s.size() == 0) return false;
    
    // Scan string
    while(s[i] != '\0') {
        // Digit found
        if ((s[i] >= '0' && s[i] <= '9')) { 
            i++;
            continue;
        }
        // Trailing whitespaces
        else if (s[i] == ' ' || s[i] == '\t') { 
            // scan every character until the end of the word
            while(s[i] != '\0') { 
                if(s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
                    return false; // Not a whitespace found
                }
                i++;
            }
            return true; // only trailing whitespaces found
        }
        // Not a digit or whitespace.
        else {
            return false;
        }

        i++;
    }

    return true;
}

// Transform a string to uppercase
string str_to_upper(string s) {
    for (int i = 0; i < s.size(); ++i) {
        s[i] = toupper(s[i]);
    }
    return s;
}

// Initialize static variable
int Player::n_players = 0;

// Constructor
Player::Player(string Name, bool isAlive, string Role)
        :name(Name), alive(isAlive), role(Role), 
            current_votes(0), candidate(true) {
            id = ++n_players; // first increase, then assign.
};

// Default constructor
Player::Player() 
    :name (""), alive(true), role ("Citizen"),
        current_votes(0), candidate(true) {
        id = ++n_players;
};

// Return full name in a format --> Player #id (username)
string Player::full_name() const {
    string s = "Player #" + to_string(id) + " (" + name + ")";
    return s; 
}

// Setters definitions
void Player::set_name(string n) { name = n; }
void Player::set_status(bool status) { alive = status; }
void Player::set_role(string rrole) { role = rrole; }
void Player::set_cur_votes(int num) { current_votes = num; }
void Player::set_cand(bool ccand) { candidate = ccand; }

// Increase by 1 the current votes of the player calling this method.
void Player::increase_cur_votes() { current_votes++; }

// Decrease by 1 the current votes of the player calling this method.
void Player::decrease_cur_votes() { current_votes--; }

/*
 * Players calling this function are asked to vote 
 * a player from the vector given as argument.
*/
void Player::vote(vector<Player> &pl_vec) {
    cout << "Player #" << id << "(" + name + ") vote. Give id >> ";
    int player_id = read_valid_vote(pl_vec); // get vote from user

    // Increase `current_votes` of the player given.
    pl_vec[player_id - 1].increase_cur_votes();
}

// Same as Player::vote, but it downvotes.
void Player::downvote(vector<Player> &pl_vec) {
    cout << "Player #" << id << "(" + name + ") vote. Give id >> ";
    int player_id = read_valid_vote(pl_vec); // get votefrom user.

    // Decrease `current_votes` of the player given.
    pl_vec[player_id - 1].decrease_cur_votes();
}

/* 
    * Send the player calling this method out.
    * Reset `current_votes` and `candidates` of players in pl_vec.
    * Prints message to cout.
*/
void Player::go_out(vector<Player>& pl_vec){
    alive = false; // Send player out.
    reset_votes(pl_vec); // Reset all votes to 0.
    all_candidates(pl_vec); // Reset all candidates to true.
    candidate = false; // Remove current player from candidate 
    
    cout << "Player #" << id << " (" << name << ')' << " goes out.\n";
}

// "put to" operator
ostream& operator<<(ostream& ost, Player& pl) {
    ost << "(Player #" << pl.get_id() << ' ' \
        << pl.get_name() \
        << ", " << "alive = " << pl.get_status() \
        << ", " << "role = " << pl.get_role() \
        << ", " << "c_votes = " << pl.get_cur_votes() \
        << ", " << "cand = " << pl.get_cand() << ")" \
        << endl;
    return ost;
}

/*
    * Initialize from a file a vector of Players.
    * It transforms roles to uppercase strings.
*/
void init_from_file(vector<Player> &pl_vec, string fname) {
    ifstream ist(fname);
    if (!ist) error("Cannot open file" + fname + "\n");

    string username, init_role;

    while (ist >> username >> init_role) {
        pl_vec.push_back(Player(username, true, str_to_upper(init_role)));
    }
}

// Set `current_votes` equal to zero for every player in vector.
void reset_votes(vector<Player>& pl_vec) {
    for(Player& pl : pl_vec) pl.set_cur_votes(0);
}

// Set `candidate` to false for every player in vector.
void no_candidate(vector<Player>& pl_vec) {
    for(Player& pl : pl_vec) pl.set_cand(false);
}

// Set `candidate` to true for all alive players in vector.
void all_candidates(vector<Player>& pl_vec) {
    for (Player &pl : pl_vec) {
        if (pl.get_status() == true)
            pl.set_cand(true);
    }
}

// Read id from user. Throw appropriate errors.
int read_vote(const vector<Player>& pl_vec) {
    int id_given;
    string s_id_given;

    // Read a single line ignoring leading whitespaces.
    cin >> ws;
    getline(cin, s_id_given); 
    
    // EOF given by user (Ctrl+D / Ctrl+Z). 
    if (cin.eof()) { 
        throw EOF_error();
    }

    // Non integer given.
    if (is_int(s_id_given) == false) {
        error("Not an integer given.");
    } 
    
    // Transform string to int.
    id_given = stoi(s_id_given);

    // Player is out of range.
    if (id_given < 1 || id_given > pl_vec.size()) {
        error("ID is out of range.");
    }
    
    // The player chosen is already out.
    if (pl_vec[id_given - 1].get_status() == false) {
        error("This player is out.");
    }

    /* 
        * Although the player chosen is alive, he cannot be voted.
        * (1) Night phase to forbid doctor from voting himself.
        * (2) Second voting, where candidates are only those who tied.
    */
    if (pl_vec[id_given - 1].get_cand() == false) {
        error("This player cannot be voted.");
    }

    return id_given;
}

/*
    * Reads a player's vote using read_vote() and returns it. 
    * Handles errors and keeps asking for correct input.
*/
int read_valid_vote(const vector<Player>& pl_vec) {
    int id_given = -1;

    // Keeps asking until user gives valid input.
    while (1) { 
        try {
            id_given = read_vote(pl_vec);
            break;
        }
        catch (runtime_error &e) {
            cin.clear(); // Clean error flag.
            cerr << e.what() << " Please try again. >> ";
        }
        catch(EOF_error) { // Re-throw EOF_error.
            throw EOF_error(); 
        }
        catch(...) {
            cerr << "Error in reading vote. Please try again. >> ";
        }
    }
    return id_given;
}

/* 
    * Finds max and modifies `candidate` in a way that 
    * only players with maximum votes have `candidate` = true.
    * Returns: 
    * The id of the player with max value. If not such a player exists,
    * -1 if max == 0 or if all players share the same value.
    * -2 if some players tied.
*/
int find_max(vector<Player>& pl_vec) {
    // set `candidate` = false for every player.
    no_candidate(pl_vec); 

    int max = pl_vec[0].get_cur_votes();
    int max_counter = 0; // count occurences of max
    int max_id = 1; // id of player with max votes
    
    int count_alive = 0; // count alive players.
    // Scan alive players.
    for (Player &pl : pl_vec) {
        if (pl.get_status() == true) {
            count_alive++;

            // New max found.
            if (pl.get_cur_votes() > max) {
                // set all players to NOT candidates
                no_candidate(pl_vec); 
                
                max = pl.get_cur_votes();
                max_counter = 1;
                max_id = pl.get_id();

                // set `candidate` = true max holder.
                pl.set_cand(true); 
            }
            // Same max found more than once.
            else if (pl.get_cur_votes() == max) { 
                max_counter++;
                pl.set_cand(true);
            }
        }
    }
    // Maximum value is zero, or all players have the same value. 
    if (max == 0 || max_counter == count_alive) return -1; 
    // One player with a maximum value.
    if (max_counter == 1) return max_id; 
    // Tie among some players. 
    if (max_counter > 1) return -2;

    return -3; // To silence compiler. Unexpected behavior.
}

/* 
    * Implements night_phase. 
    * Returns the id of the player leaving, otherwise -1. 
*/
int night_phase(vector<Player>& pl_vec) {
    int id_to_kick = -1; // id of player to send out.
    reset_votes(pl_vec); // Reset all votes to 0.

    cout << "\n--- Night phase begins ---\n\n";

    // Find Gangster and ask him to vote.
    for(Player &pl : pl_vec) {
        if (pl.get_role() == "GANGSTER") {
            cout << "Gansgster's pick.\n";
            pl.vote(pl_vec);
        }
    }

    // Find doctor and ask him to downvote (if he is still alive).
    for(Player &pl : pl_vec) {
        if (pl.get_role() == "DOCTOR" && pl.get_status() == true) {
            pl.set_cand(false); // Forbid doctor to vote himself.
            
            cout << "Doctor's pick.\n";
            pl.downvote(pl_vec);            
            
            pl.set_cand(true); // Set doctor back to candidate. 
        }
    }

    id_to_kick = find_max(pl_vec); // player with most votes.
    
    // Doctor saved gangster's pick. No player leaves.
    if (id_to_kick == -1) {
        reset_votes(pl_vec); // Not necessary. For safety.
        all_candidates(pl_vec); // Set all alive players to candidates
        cout << "Nobody is leaving!\n";
        return -1;
    }
    // Gangster's choice is sent out of the game.
    else {
        pl_vec[id_to_kick - 1].go_out(pl_vec);
        return id_to_kick; // id of the player leaving.
    }

}

/* 
    * Implements day phase. 
    * Returns the id of the player leaving, otherwise -1. 
*/
int day_phase (vector<Player>& pl_vec) {
    cout << "\n--- Day phase begins ---\n";
    int id_to_kick = -1; // id of player to send out.
    
    // 1st Voting
    for (Player &pl : pl_vec) {
        if (pl.get_status() == true) {
            pl.vote(pl_vec);
        }
    }

    id_to_kick = find_max(pl_vec); // result of 1st voting

    // Clear Majority
    if (id_to_kick > 0) {
        pl_vec[id_to_kick - 1].go_out(pl_vec);
    
        return id_to_kick; // id of player leaving.
    }
    // Equal votes for everyone 
    if (id_to_kick == -1) { 
        // Reset `current_votes` and `candidate`.
        reset_votes(pl_vec);
        all_candidates(pl_vec);
        cout << "Nobody is leaving!\n";
        return -1;
    }
    // Tie among some players
    if (id_to_kick == -2) {
        reset_votes(pl_vec);

        // Print those that tied.
        cout << "\nTie among Players ";
        for (Player &pl : pl_vec) {
            if (pl.get_cand() == true)
                cout << "#" << pl.get_id() << ' ';
        }

        // Second Voting
        cout << "\n--- 2nd Voting ---\n";

        for (Player &pl : pl_vec) {
            if (pl.get_status() == true) {
                pl.vote(pl_vec);
            }
        }

        id_to_kick = find_max(pl_vec); // result of 2nd voting

        // No election winner.
        if (id_to_kick < 1) {
            // Reset `current_votes` and `candidate`.
            reset_votes(pl_vec);
            all_candidates(pl_vec);
            cout << "Nobody is leaving!\n";
            return -1;
        }
        // Clear Majority
        else {
        pl_vec[id_to_kick - 1].go_out(pl_vec);
        return id_to_kick; // id of player leaving.
        }
    }
    return -3; // Silence the compiler.
}