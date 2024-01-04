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

int find_mirror_row(vector<string> lines, vector<int> duplicate_rows) {
    for (int i = 0; i < duplicate_rows.size(); i++) {
        if (is_row_mirror(lines, duplicate_rows[i])) {
            return duplicate_rows[i]+1;
        }
    }
    return -1;
}

int find_mirror_col(vector<string> lines, vector<int> duplicate_cols) {
    for (int i = 0; i < duplicate_cols.size(); i++) {
        if (is_col_mirror(lines, duplicate_cols[i])) {
            return duplicate_cols[i]+1;
        }
    }
    return -1;
}

int find_mirror_ans(vector<string> lines, vector<int> duplicate_rows, vector<int> duplicate_cols) {
    int row = find_mirror_row(lines, duplicate_rows);
    int col = find_mirror_col(lines, duplicate_cols);
    if (row != -1) {
        return 100*row;
    }
    else if (col != -1) {
        return col;
    }
    else {
        return -1;
    }
}

int find_ans(vector<string> lines) {
    vector<int> duplicate_rows = find_duplicate_neighbour_rows(lines);
    vector<int> duplicate_cols = find_duplicate_cols(lines);
    int ans = find_mirror_ans(lines, duplicate_rows, duplicate_cols);
    if (ans != -1) {
        return ans;
    }
    else {
        cout << "No mirror" << endl;
        return 0;
    }
}

int main() {
    string filename = "data.txt";
    vector<vector<string>> patterns = read_file(filename);
    int ans = 0;
    for (int i = 0; i < patterns.size(); i++) {
        ans += find_ans(patterns[i]);
    }
    cout << "Answer: " << ans << endl;
    return 0;
}
