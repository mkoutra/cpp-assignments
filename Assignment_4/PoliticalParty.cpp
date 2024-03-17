/* 
 * CS150 - Political Party class for Assignment 4
 * Michail E. Koutrakis
 * Email: m.koutrakis@physics.uoc.gr
 * Github: https://github.com/mkoutra
 * June 2023
*/
#include "std_lib_facilities.h"
#include "PoliticalParty.h"

// Nominee constructor 
Nominee::Nominee(string nname, int vvotes):
    Name(nname), Votes(vvotes) {};

// Setters
void PoliticalParty::SetPartyInfo(Info partyInfo) { 
    this->partyInfo = partyInfo; 
}

void PoliticalParty::SetNominees(vector<Nominee> noms) {
    Nominees = noms;
}

void PoliticalParty::IncreaseVote(int idx) {
    Nominees[idx].Votes++;
}

string PoliticalParty::GetAllInfo() {
    string s;
    Info p_info = GetPartyInfo();
    vector<string> sorted_nominees = GetNomineesVotes();

    s = "Political Party: " + Name +\
        "\nFounded: " + to_string(p_info.foundedYear) +\
        "\nChairman Name: " + p_info.chairmanName +\
        "\nIdeology: " + p_info.Ideology +\
        "\nScore: " + to_string(GetTotalScore()) +\
        "\nNominees:\n";
    
    for (int i = 0; i < sorted_nominees.size(); ++i) {
        s += "[" + to_string(i) + "]: " + sorted_nominees[i] + "\n";
    }

    return s;
}

// Blue Party constructor
BlueParty::BlueParty(vector<Nominee> noms) {
    partyInfo.foundedYear = 2020;
    partyInfo.chairmanName = "Blue Captain";
    partyInfo.Ideology = "We like blue.";
    Name = "Blue Party";
    Nominees = noms;
}

// Red Party constructor
RedParty::RedParty(vector<Nominee> noms) {
    partyInfo.foundedYear = 1990;
    partyInfo.chairmanName = "Red Captain";
    partyInfo.Ideology = "We like red.";
    Name = "Red Party";
    Nominees = noms;
}

// For Blue Party score = (total number of votes) / (number of nominees).
int BlueParty::GetTotalScore() {
    // Number of nominees
    int n_nominees = Nominees.size(); 

    // Find total votes
    int total_votes = 0;
    for (Nominee& nom : Nominees) total_votes += nom.Votes;

    return total_votes / n_nominees;
}

// For Red Party score = the total number of votes.
int RedParty::GetTotalScore() {
    // Find total votes
    int total_votes = 0;
    for (Nominee& nom : Nominees) total_votes += nom.Votes;
    
    return total_votes;
}

/* 
 * For Blue Party, nominees and number of votes with 
 * ascending order based on the nominee's name.
*/
vector<string> BlueParty::GetNomineesVotes() {
    vector<string> sorted_vec;
    
    // Sort Nominees by name
    sort(Nominees.begin(), Nominees.end(), CompareByName);
    
    for (Nominee& nom : Nominees) {
        sorted_vec.push_back(nom.Name + " " + to_string(nom.Votes));
    }

    return sorted_vec;
}

/* 
 * For Red Party, nominees and number of votes with 
 * ascending order based on the number of votes.
*/
vector<string> RedParty::GetNomineesVotes() {
    vector<string> sorted_vec;
    
    // Sort Nominees by name
    sort(Nominees.begin(), Nominees.end(), CompareByVote);
    
    for (Nominee& nom : Nominees) {
        sorted_vec.push_back(nom.Name +" " + to_string(nom.Votes));
    }

    return sorted_vec;
}

// Read nominees from file.
vector<Nominee> read_noms(const string& fname) {
    vector<Nominee> noms;
    string name, surname;
    int votes;

    ifstream ist(fname);
    if (!ist) error("Cannot open file" + fname + "\n");
    
    while (ist >> name >> surname >> votes) {
        noms.push_back(Nominee(name + " " + surname, votes));
    }

    return noms;
}

// To sort alphabetically. 
bool CompareByName(Nominee nom1, Nominee nom2) {
    return nom1.Name < nom2.Name;
}

// To sort with ascending order.
bool CompareByVote(Nominee nom1, Nominee nom2) {
    return nom1.Votes < nom2.Votes;
}