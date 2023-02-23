#include "std_lib_facilities.h"
#include <limits.h>

#define NUM_PLAYERS 7 // Number of players
#define CIT 0 // Citizen
#define DOC 1 // Doctor 
#define GANG 2 // Gangster
#define LOSER -1 // Loser

/*----- GENERAL FUNCTIONS -----*/
void dashed_line(int size);
void print_vec(const vector<int>&);
void dashed_message(string s);
bool in_vector(const int&, const vector<int>&);

/*----- INITIALIZATION -----*/
void initialization(vector<int>&);

/*----- INFO MENU -----*/
string role(int);
int get_option(void);
void show_options(void);
void print_request(int, const vector<int>&, int);
void info_menu(const vector<int>&, int);

/*----- NIGHT PHASE -----*/
int get_player_id(const vector<int>&);
int get_doctor_save(const vector<int>&, int);
int night_phase(vector<int>&);

/*----- VOTING & DAY PHASE -----*/
int get_player_id(const vector<int>&, const vector<int>&);
int get_vote(const vector<int>&);
int get_vote(const vector<int>&,  const vector<int>&);
vector<int> find_winners(const vector<int>&);
int voting_procedure(vector<int>&);
int day_phase(vector<int>& vec);

/*----- GAME FLOW -----*/
bool end_game(const vector<int>& );