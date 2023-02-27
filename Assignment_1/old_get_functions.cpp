/*----- INFO MENU -----*/

// Get an option from user and return it.
int get_option(void) {
    double option = 0;
    cin >> option;
    // Non integer given.
    if (!cin) error("Non valid input type.");
    
    // Number given is not integer.
    if (option != (int)option) {
        error("Not an integer.");
    }

    // Option is out of range.
    if (option < 1 || option > NUM_OPTIONS) {
        error("Option is out of range.");
    }

    return (int)option;
}

/*----- NIGHT PHASE -----*/
/*
 * Reads and returns a player's id from standard input.
 * The second arg. is optional with default value -1. 
 * Should be used only when the player is not allowed to vote himself.
 * Throws and exception if the id is not valid.
*/
int get_player_id(const vector<int>& vec, int self_id) {
    double id_given = -1;
    cin >> id_given;

    // Not a number given.
    if (!cin) error("Non valid input type.");
    
    // Number given is not integer.
    if (id_given != (int)id_given) {
        error("Not an integer.");
    }

    // Player's id is out of range.
    if (id_given < 1 || id_given > NUM_PLAYERS) {
        error("Player chosen is out of range.");
    }
    
    // The player chosen is already out.
    if (vec[(int)id_given - 1] == LOSER) {
        error("Player is out.");
    }
    
    // Player chose himself
    if ((self_id != -1) && ((int)id_given == self_id)) {
        error("Cannot vote yourself.");
    }

    return (int)id_given;
}

/*----- DAY PHASE -----*/

/*
 * Reads and returns a player's id from standard input.
 * The second arg. is optional with default value {}. It should be used 
 * only when we have specific candidates (e.g. in second voting).
 * Throws and exception if the id is not valid.
*/
int get_vote(const vector<int>& vec, const vector<int> candidates) {
    double id_given = -1;
    cin >> id_given;

    // Not a number given.
    if (!cin) error("Non valid input type.");
    
    // Number given is not integer.
    if (id_given != (int)id_given) {
        error("Not an integer.");
    }

    // Player's id is out of range.
    if (id_given < 1 || id_given > NUM_PLAYERS) {
        error("Player chosen is out of range.");
    }
    
    // The player chosen is already out.
    if (vec[(int)id_given - 1] == LOSER) {
        error("Player is out.");
    }

    // The playser chosen is not in candidates' list.
    if (!candidates.empty() && !in_vector((int)id_given, candidates)) {
        error("Player chosen is not a candidate.");
    }

    return (int)id_given;
}