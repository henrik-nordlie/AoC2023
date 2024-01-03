#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

vector<vector<string>> read_file(string filename) {
    ifstream file(filename);
    vector<vector<string>> patterns;
    vector<string> lines;
    string line;
    while (getline(file, line)) {
        if (line == "") {
            patterns.push_back(lines);
            lines.clear();
        }
        else {
            lines.push_back(line);
        }
    }
    patterns.push_back(lines);
    return patterns;
}

// returns index of the first duplicate row in all pairs
vector<int> find_duplicate_neighbour_rows(vector<string> lines) {
    vector<int> duplicate_rows;
    for (int i = 0; i < lines.size() - 1; i++) {
        if (lines[i] == lines[i + 1]) {
            duplicate_rows.push_back(i);
        }
    }
    return duplicate_rows;
}

// returns index of the first duplicate col in all pairs
vector<int> find_duplicate_cols(vector<string> lines) {
    vector<int> duplicate_cols;
    bool all_equal = true;
    for (int i = 0; i < lines[0].size()-1; i++) {
        all_equal = true;
        for (int j = 0; j < lines.size(); j++) {
            if (lines[j][i] != lines[j][i + 1]) {
                all_equal = false;
                break;
            }
        }
        if (all_equal) {
            duplicate_cols.push_back(i);
        }
    }
    return duplicate_cols;
}

bool is_row_mirror(vector<string> lines, int row) {
    int top = row;
    int bottom = row + 1;
    while (top >= 0 && bottom < lines.size()) {
        if (lines[top] != lines[bottom]) {
            return false;
        }
        top--;
        bottom++;
    }
    return true;
}

bool is_col_mirror(vector<string> lines, int col) {
    int left = col;
    int right = col + 1;
    while (left >= 0 && right < lines[0].size()) {
        for (int i = 0; i < lines.size(); i++) {
            if (lines[i][left] != lines[i][right]) {
                return false;
            }
        }
        left--;
        right++;
    }
    return true;
}

int find_mirror_row(vector<string> lines, vector<int> duplicate_rows, vector<int> duplicate_cols) {
    for (int i = 0; i < duplicate_rows.size(); i++) {
        if (is_row_mirror(lines, duplicate_rows[i])) {
            return duplicate_rows[i];
        }
    }
    return -1;
}

int find_mirror_col(vector<string> lines, vector<int> duplicate_rows, vector<int> duplicate_cols) {
    for (int i = 0; i < duplicate_cols.size(); i++) {
        if (is_col_mirror(lines, duplicate_cols[i])) {
            return duplicate_cols[i];
        }
    }
    return -1;
}

int find_mirror(vector<string> lines, vector<int> duplicate_rows, vector<int> duplicate_cols) {
    int mirror_row = find_mirror_row(lines, duplicate_rows, duplicate_cols);
    int mirror_col = find_mirror_col(lines, duplicate_rows, duplicate_cols);
    if (mirror_row != -1 && mirror_col != -1) {
        cout << "HERE" << endl;
        return min(mirror_row, mirror_col);
    }
    else if (mirror_row != -1) {
        return mirror_row;
    }
    else if (mirror_col != -1) {
        return -mirror_col;
    }
    else {
        return 0;
    }
}

void find_all_mirrors (vector<vector<string>> patterns) {
    for (int i = 0; i < patterns.size(); i++) {
        vector<string> lines = patterns[i];
        vector<int> duplicate_rows = find_duplicate_neighbour_rows(lines);
        vector<int> duplicate_cols = find_duplicate_cols(lines);
        int mirror = find_mirror(lines, duplicate_rows, duplicate_cols);
        if (mirror == 0) {
            cout << "Pattern " << i + 1 << " was not a mirror" << endl;
        }
        else if (mirror > 0) {
            cout << "Pattern " << i + 1 << " was a mirror horizontally between rows " << mirror + 1 << " and " << mirror + 2 << endl;
        }
        else {
            cout << "Pattern " << i + 1 << " was a mirror vertically between columns " << -mirror + 1 << " and " << -mirror + 2 << endl;
        }
    }
}

int main() {
    string filename = "test.txt";
    vector<vector<string>> patterns = read_file(filename);
    find_all_mirrors(patterns);
}
