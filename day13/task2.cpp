#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

struct equal_and_has_smudge {
    bool equal;
    bool has_smudge;
};

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

equal_and_has_smudge compare_rows(vector<string> lines, int row1, int row2) {
    equal_and_has_smudge result;
    result.equal = true;
    result.has_smudge = false;
    for (int i = 0; i < lines[row1].size(); i++) {
        if (lines[row1][i] != lines[row2][i] and result.has_smudge == false) {
            result.has_smudge = true;
            continue;
        }
        else if (lines[row1][i] != lines[row2][i] and result.has_smudge == true) {
            result.equal = false;
            break;
        }
    }
    return result;
}

equal_and_has_smudge compare_cols(vector<string> lines, int col1, int col2) {
    equal_and_has_smudge result;
    result.equal = true;
    result.has_smudge = false;
    for (int i = 0; i < lines.size(); i++) {
        if (lines[i][col1] != lines[i][col2] and result.has_smudge == false) {
            result.has_smudge = true;
            continue;
        }
        else if (lines[i][col1] != lines[i][col2] and result.has_smudge == true) {
            result.equal = false;
            break;
        }
    }
    return result;
}


// returns index of the first duplicate row in all pairs
vector<equal_and_has_smudge> find_duplicate_rows(vector<string> lines) {
    vector<equal_and_has_smudge> duplicate_rows;
    for (int i = 0; i < lines.size()-1; i++) {
        duplicate_rows.push_back(compare_rows(lines, i, i+1));
    }
    return duplicate_rows;
}

// returns index of the first duplicate col in all pairs
vector<equal_and_has_smudge> find_duplicate_cols(vector<string> lines) {
    vector<equal_and_has_smudge> duplicate_cols;
    for (int i = 0; i < lines[0].size()-1; i++) {
        duplicate_cols.push_back(compare_cols(lines, i, i+1));
    }
    return duplicate_cols;
}

bool is_row_mirror(vector<string> lines, int row) {
    int top = row;
    int bottom = row + 1;
    bool smudge_seen = false;
    while (top >= 0 && bottom < lines.size()) {
        equal_and_has_smudge result = compare_rows(lines, top, bottom);
        if (result.equal == false) {
            return false;
        }
        else if (result.has_smudge == true && smudge_seen == true) {
            return false;
        }
        else if (result.has_smudge == true && smudge_seen == false) {
            smudge_seen = true;
        }
        top--;
        bottom++;
    }
    if (smudge_seen == false) {
        return false;
    }
    return true;
}

bool is_col_mirror(vector<string> lines, int col) {
    int left = col;
    int right = col + 1;
    bool smudge_seen = false;
    while (left >= 0 && right < lines[0].size()) {
        equal_and_has_smudge result = compare_cols(lines, left, right);
        if (result.equal == false) {
            return false;
        }
        else if (result.has_smudge == true && smudge_seen == true) {
            return false;
        }
        else if (result.has_smudge == true && smudge_seen == false) {
            smudge_seen = true;
        }
        left--;
        right++;
    }
    if (smudge_seen == false) {
        return false;
    }
    return true;
}

int find_mirror_row(vector<string> lines, vector<equal_and_has_smudge> duplicate_rows) {
    for (int i = 0; i < duplicate_rows.size(); i++) {
        if (duplicate_rows[i].equal == true) {
            if (is_row_mirror(lines, i)) {
                return i+1;
            }
        }
    }
    return -1;
}

int find_mirror_col(vector<string> lines, vector<equal_and_has_smudge> duplicate_cols) {
    for (int i = 0; i < duplicate_cols.size(); i++) {
        if (duplicate_cols[i].equal == true) {
            if (is_col_mirror(lines, i)) {
                return i+1;
            }
        }
    }
    return -1;
}

int find_mirror_ans(vector<string> lines, vector<equal_and_has_smudge> duplicate_rows, vector<equal_and_has_smudge> duplicate_cols) {
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
    vector<equal_and_has_smudge> duplicate_rows = find_duplicate_rows(lines);
    vector<equal_and_has_smudge> duplicate_cols = find_duplicate_cols(lines);
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
        int pattern_ans = find_ans(patterns[i]);
        ans += pattern_ans;
    }
    cout << "Answer: " << ans << endl;
    return 0;
}
