#include "std_lib_facilities.h"

vector<int> max_indices (const vector<int>& vec);

int main(void) {
    vector<int> test = {7,1,7,4,7,7,0,-3,7};

    vector<int> indices = max_indices(test);

    for (int i = 0; i < indices.size(); ++i) {
        cout << indices[i] << " ";
    }

    cout << '\n';

    return 0;
}

vector<int> max_indices (const vector<int>& vec) {
    int max = vec[0];
    vector<int> indices; // Indices of vec-elements with the maximum number
    
    // Find max & store the index to indices.
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] > max) {
            max = vec[i];
            indices.clear();
        }
        if (vec[i] == max) indices.push_back(i);
    }

    return indices;
}