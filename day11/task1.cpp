#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

const char* filename = "data.txt";
ifstream myfile(filename);
ifstream myfile2(filename);
string data;

string myline;

vector<string> build_universe (const char* filename) {
    vector<string> universe;
    if (myfile.is_open() ) {
        while (getline(myfile, myline)) {
            if (myline.length()) {
                universe.push_back(myline);
            }
        }
        myfile.close();
    }
    else {
        cout << "Couldn't open file" << "\n";
    }
    return universe;
}
    
vector<string> expand_universe(vector<string> universe) {
    vector<string> expanded_universe;

    // empty array of bools to see if columns are empty
    // init to true
    bool* empty_cols = new bool[universe[0].length()];

    for (int i=0; i<universe[0].length(); i++) {
        empty_cols[i] = true;
    }
    for (int i=0; i<universe.size(); i++) {
        bool clear_line = true;
        myline = universe[i];
        for (int c=0; c<myline.length(); c++) {
            if (myline[c] != '.') {
                clear_line = false;
                empty_cols[c] = false;
            }
        }
        if (clear_line) {
           expanded_universe.push_back(myline);
        }
        expanded_universe.push_back(myline);
    }
        
    for (int i=expanded_universe[0].size()-1; i>=0; i--) {
        if (empty_cols[i] == true) {
            for (int j=0; j<expanded_universe.size(); j++) {
                expanded_universe[j].insert(i, "."); 
            }
        }
    }
    delete[] empty_cols;
    return expanded_universe;
}

int find_manh_dist (array<int,2> a, array<int,2> b) {
    int d_x = abs(b[0] - a[0]);
    int d_y = abs(b[1] - a[1]);
    int euc_dist = d_x + d_y;
    return euc_dist;
}

vector<array<int, 2>> find_galaxies(vector<string> expanded_universe) {
    vector<array<int, 2>> galaxies;
    array<int,2> new_galaxy;
    for (int i=0; i<expanded_universe.size(); i++) {
        for (int j=0; j<expanded_universe[0].size(); j++) {
            if (expanded_universe[i][j] == '#') {
                new_galaxy[0] = i;
                new_galaxy[1] = j;
                if (galaxies.size() > 442) {
                galaxies.push_back(new_galaxy);
                }
                else {
                    galaxies.push_back(new_galaxy);
                }
            }
       }
    }
    return galaxies;
}

vector<array<int, 3>> generate_galaxy_pair_dists(vector<array<int,2>> galaxies) {
    vector<array<int, 3>> galaxy_pair_dists;
    for (int i=0; i<galaxies.size(); i++) {
        for (int j=galaxies.size()-1; j>i; j--) {
           array<int,3> pair_dist;
           pair_dist[0] = i+1; // adding one to make galaxy pair index same as galaxy number
           pair_dist[1] = j+1;
           pair_dist[2] = find_manh_dist(galaxies[i], galaxies[j]);

           galaxy_pair_dists.push_back(pair_dist);

        }
    }
    return galaxy_pair_dists;
}

int main () {
    vector<string> universe = build_universe(filename);
    cout << "Original universe: " << endl;
    for (int i=0; i<universe.size(); i++) {
        cout << universe[i] << endl;
    }
    vector<string> expanded_universe;
    expanded_universe = expand_universe(universe);
    cout << "Expanded universe: " << endl;
    for (int i=0; i<expanded_universe.size(); i++) {
        cout << expanded_universe[i] << endl;
    }

    vector<array<int, 2>> galaxies = find_galaxies(expanded_universe);


    cout << galaxies.size() << " galaxies found" << endl;
    vector<array<int, 3>> galaxy_pair_dists = generate_galaxy_pair_dists(galaxies);
    int ans = 0;
    for (int i=0; i<galaxy_pair_dists.size(); i++) {
        for (const auto j: galaxy_pair_dists[i]) {
            cout << j << " ";
        }
        ans += galaxy_pair_dists[i][2];
        cout << endl;
    }
    cout << "ANSWER: " << ans << endl;
    return 0;
}

