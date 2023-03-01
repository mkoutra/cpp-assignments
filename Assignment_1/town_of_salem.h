#ifndef TOWN_OF_SALEM_H // include guard
#define TOWN_OF_SALEM_H
#include "std_lib_facilities.h"

#define NUM_PLAYERS 7 // Number of players
#define NUM_OPTIONS 4 // Number of available options in menu
#define CIT 0 // Citizen
#define DOC 1 // Doctor 
#define GANG 2 // Gangster
#define LOSER -1 // Loser

// In case user gives eof.
class EOF_error{};

/*----- GENERAL FUNCTIONS -----*/
void dashed_message(string);
bool in_vector(const int&, const vector<int>&);
string role(int);
bool is_int(string s);
bool is_over(const vector<int>&);

/*----- INITIALIZATION -----*/
void initialization(vector<int>&);

/*----- INFO MENU -----*/
int get_option(void);
void print_request(int, const vector<int>&, int);
void info_menu(const vector<int>&, int);

/*----- NIGHT PHASE -----*/
int get_id(const vector<int>&, int self_id = -1);
int get_valid_id(const vector<int>&, int self_id = -1);
int night_phase(vector<int>&);

/*----- VOTING & DAY PHASE -----*/
int get_vote(const vector<int>&, const vector<int> candidates = {});
int get_valid_vote(const vector<int>&,  const vector<int> candidates = {});
vector<int> find_winners(const vector<int>&);
vector<int> elections(const vector<int>&, vector<int> candidates = {});
int voting_procedure(vector<int>& vec);
int day_phase(vector<int>&);

#endif// TOWN_OF_SALEM_H