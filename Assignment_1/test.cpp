#include "std_lib_facilities.h"

int main(void) {
    string s = "";
    s += "abc" + to_string(5);
    
    cout << s << endl;

    return 0;
}