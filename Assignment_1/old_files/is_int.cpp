// Creation of a function that checks if something is integer

#include <iostream>
#include <string>

using namespace std;

bool is_int(string s);

int main(void) {
    for(;;) {
        string s;
        cin >> ws;
        getline(cin, s);

        if(cin.eof()) {
            cerr << "EOF\n";
            return 1;
        }
        
        cout << is_int(s) << endl;
    }
    return 0;
}

/*
 * Checks if a string represents integer.
 * Ignores leading and trailing whitespaces.
*/
bool is_int(string s) {
    int i{0};
    //Drop leading whitespaces.
    while(s[0] == ' ' || s[0] == '\t' || s[0]=='\n') {
        s = s.substr(1);
    }

    // Sign check
    if (s[0] == '+' || s[0] == '-') {
        s = s.substr(1);
    }
    // String containing only whitespaces or '+', '-' 
    // will be empty at this point (s.size() == 0).
    if (s.empty()) return false;
    
    // Scan string
    while(s[i] != '\0') {
        // Digit
        if ((s[i] >= '0' && s[i] <= '9')) { 
            i++;
            continue;
        }
        // Trailing whitespaces
        else if (s[i] == ' ' || s[i] == '\t') { 
            // scan until end of word
            while(s[i] != '\0') { 
                if(s[i] != ' ' && s[i] != '\t' && s[i] != '\n') {
                    return false; // Non-whitespace found
                }
                i++;
            }
            return true; // only trailing whitespaces found
        }
        // Not digit or whitespace.
        else {
            return false;
        }

        i++;
    }

    return true;
}