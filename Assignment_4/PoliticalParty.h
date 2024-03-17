/* 
 * CS150 - header file for Assignment 4
 * Michail E. Koutrakis
 * Email: m.koutrakis@physics.uoc.gr
 * Github: https://github.com/mkoutra
 * June 2023
*/
#include "std_lib_facilities.h"

struct Info {
    int foundedYear;
    string chairmanName;
    string Ideology;
};

struct Nominee {
    // constructor
    Nominee(string, int); 
    
    string Name;
    int Votes;
};

// Abstract Class
class PoliticalParty {
    protected:
        Info partyInfo;
        string Name;
        vector<Nominee> Nominees;
    
    public:
        // Getters
        virtual int GetTotalScore() =0;
        virtual vector<string> GetNomineesVotes() =0;
        Info GetPartyInfo() { return partyInfo; }
        
        // Setters
        void SetPartyInfo(Info partyInfo);
        void SetNominees(vector<Nominee> noms);

        void IncreaseVote(int idx);
        string GetAllInfo();

};

// BlueParty subclass
class BlueParty : public PoliticalParty {
    public:
        // Constructor
        BlueParty(vector<Nominee>);

        int GetTotalScore();
        vector<string> GetNomineesVotes();
};

// RedParty subclass
class RedParty : public PoliticalParty {
    public:
        // Constructor
        RedParty(vector<Nominee>);

        int GetTotalScore();
        vector<string> GetNomineesVotes();
};

// Read nominees from file.
vector<Nominee> read_noms(const string& fname);
// Sorting functions
bool CompareByName(Nominee nom1, Nominee nom2);
bool CompareByVote(Nominee nom1, Nominee nom2);