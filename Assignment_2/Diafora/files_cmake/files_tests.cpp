#include "std_lib_facilities.h"

int main(void) {
    ifstream ifs("file.txt");
    
    if (!ifs) error("File cant open.\n");

    string name;
    int value;

    string new_file_name;
    cout << "Give new file name >> ";
    cin >> new_file_name;

    ofstream ost("../" + new_file_name);
    
    // read 2 variables
    
    // while(ifs >> name >> value) {
    //     ost << "Name: " << name << "\tValue = " << value << endl;
    // }

    // read line by line
    while(1) {
        getline(ifs, name);
        ost << "Full Line: " << name << endl;
        if (ifs.eof()) break;
    }

    return 0;
}