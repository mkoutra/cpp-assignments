/* 
 * CS150 - Main for Assignment 4
 * Michail E. Koutrakis
 * Email: m.koutrakis@physics.uoc.gr
 * Github: https://github.com/mkoutra
 * June 2023
*/

// TODO: Range check and validity of input

#include "std_lib_facilities.h"
#include "PoliticalParty.h"

int main(void) {
    int choice;
    BlueParty bl(read_noms("BlueParty.txt"));
    RedParty rd(read_noms("RedParty.txt"));

    // Choose party and print the corresponding message.
    cout << "Blue Party [1] ----- Red Party [2]\nGive a number:  ";
    cin >> choice;

    switch(choice) {
        // Blue Party
        case 1:
            cout << bl.GetAllInfo() << "\nChoose a nominee. Give a number: ";

            // Read and print a nominee. 
            cin >> choice;
            cout << "You chose: " << bl.GetNomineesVotes()[choice] << endl;
            break;
        // Red Party
        case 2:
            cout << rd.GetAllInfo() << "\nChoose a nominee. Give a number: ";

            // Read and print a nominee. 
            cin >> choice;
            cout << "You chose: " << rd.GetNomineesVotes()[choice] << endl;
            break;
        // Wrong Input
        default:
            cout << "Wrong input.\n";
            break;
    }

    return 0;
}