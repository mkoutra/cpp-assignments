#include <iostream>
#include <string>
#include <vector>

class EOF_error{};

using namespace std;

void error (string s);
int read_int(void);

int main(void) {
    int num;

    while(1) {
        try {
            num = read_int();
            break;
        }
        catch (runtime_error &e) {
            cin.clear();
            cin.ignore(1000, '\n');
            cerr << e.what() << " Try again. >> ";
        }
        catch(EOF_error) {
            cin.clear();
            cerr << "EOF\n";
            return 0;
        }
    }

    cout << "num = " << num << endl;

    return 0;
}

void error (string s) {
    throw runtime_error(s);
}

int read_int(void) {
    double n;
    cin >> n;

    // not integer given
    if(cin.eof()) throw EOF_error();

    // 
    if (!cin) error("Not int.");

    // handle the case that user gave double.
    if(n != (int)n) error("Not integer");

    // Number out of range.
    if (n < 1 || n > 5) error("Out of range.");


    return (int)n;
}