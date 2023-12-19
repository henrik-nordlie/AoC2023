#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

const char* filename = "data.txt";
ifstream myfile(filename);
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
    
 void find_empty_lines_cols(vector<string> universe, bool empty_cols[], bool empty_lines[]) {
    for (int i=0; i<universe[0].length(); i++) {
        empty_cols[i] = true;
    }
    for (int i=0; i<universe.size(); i++) {
        empty_lines[i] = true;
    }
    for (int i=0; i<universe.size(); i++) {
        bool clear_line = true;
        myline = universe[i];
        for (int c=0; c<myline.length(); c++) {
            if (myline[c] != '.') {
                clear_line = false;
                empty_cols[c] = false;
                empty_lines[i] = false;
            }
        }
    }
}

long long find_manh_dist (array<long long,2> a, array<long long,2> b) {
    long long d_x = abs(b[0] - a[0]);
    long long d_y = abs(b[1] - a[1]);
    long long euc_dist = d_x + d_y;
    return euc_dist;
}

vector<array<long long, 2>> find_galaxies(vector<string> universe, bool empty_cols[], bool empty_lines[]) {
    vector<array<long long, 2>> galaxies;
    array<long long,2> new_galaxy;
    long long i_dist = 0;
    for (int i=0; i<universe.size(); i++) {
        if (empty_lines[i]) {
            i_dist += 1000000;
            continue;
        }
        long long j_dist = 0;
        for (int j=0; j<universe[0].size(); j++) {
            if (universe[i][j] == '#') {
                new_galaxy[0] = i_dist;
                new_galaxy[1] = j_dist;
                cout << "New galaxy found at: " << i_dist << ", " << j_dist << endl;
                galaxies.push_back(new_galaxy);
            }
            if (empty_cols[j]) {
                j_dist += 1000000;
            }
            else {
                j_dist++;
            }
        }
        if (!empty_lines[i]) { // should be a redundant check 
            i_dist++;
        }
    }
    return galaxies;
}

vector<array<long long, 3>> generate_galaxy_pair_dists(vector<array<long long,2>> galaxies) {
    vector<array<long long, 3>> galaxy_pair_dists;
    for (int i=0; i<galaxies.size(); i++) {
        for (int j=galaxies.size()-1; j>i; j--) {
           array<long long,3> pair_dist;
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
    bool empty_lines [universe.size()];
    bool empty_cols [universe[0].length()];
    find_empty_lines_cols(universe, empty_cols, empty_lines);
    vector<array<long long, 2>> galaxies = find_galaxies(universe, empty_cols, empty_lines);
    vector<array<long long, 3>> galaxy_pair_dists = generate_galaxy_pair_dists(galaxies);
    long long ans = 0;
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

