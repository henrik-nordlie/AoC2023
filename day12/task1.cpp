#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cmath>


using namespace std;

vector<string> read_lines (string path) {
    ifstream dataFile(path);
    string dataString;    
    vector<string> lines;
    if ( dataFile.is_open() ) { // always check whether the file is open
        while (dataFile) {
            getline(dataFile, dataString);
            lines.push_back(dataString);
        }                                   
    }
    return lines;
}

vector<string> make_records(vector<string> lines) {
    vector<string> records;
    for (int i=0; i<lines.size()-1; i++) {
        char* p = strtok((char*)lines[i].c_str(), " ");
        records.push_back(p);
        p = strtok(NULL, " ");
    }
    return records;
}

vector<vector<int>> make_groups(vector<string> lines) {
    vector<vector<int>> groups;
    vector<int> group;
    char * p;
    int start_num = 0;
    int num = 0;
    for (int i=0; i<lines.size()-1; i++) {
        group.clear();
        string line = lines[i];
        for (int c=0; c<=line.size(); c++) {
            if (line[c] == ' ') {
                start_num = c+1;
            }
            if (line[c] == ',' or c == line.size()) {
                int num = atoi(&line[start_num]);
                start_num = c+1;
                group.push_back(num);
            }
        }
        groups.push_back(group);
        for (int i=0; i<group.size(); i++) {
            cout << group[i] << " ";
        }
        cout << endl;
    }
    return groups;
}

bool group_fits_chunk (string line, int ch, int group) {
    if (ch+group > line.size()) {
        return false;
    }
    for (int i=ch; i<ch+group; i++) {
        if (line[i] != '?' and line[i] != '#') { 
            return false;
        }
    }
    if (ch > 0 and line[ch-1] == '#') {
        return false; // spring before chunk means no solution
    }
    else if (ch+group < line.size() and line[ch+group] == '#') {
        return false; // spring after chunk means no solution
    }
    return true;
}

bool check_solution (string line, vector<int> solution, vector<int> groups) {
    bool valid = true;
    for (int ch=0; ch<line.size(); ch++) {
        if (line[ch] =='#') {
            int gr = 0;
            bool in_sol = false;
            for (int i=0; i<groups.size(); i++) {
                if (!in_sol) {
                    for (int j=0; j<groups[gr]; j++) {
                        if (solution[i]+j == ch) {
                            in_sol = true;
                            break;
                        }
                    }
                }
                gr ++;
            }
            if (!in_sol) {
                valid = false;
                break;
            }
        }
    }
    return valid;
}

    
int find_solutions (string line, vector<int> groups, int curr_group, int num_solutions, vector<int> checked) {
    bool done = false;
    int start_ind = 0;
    vector<vector<int>> all_checked;
    while (!done) {
        if (curr_group > 0) {
            start_ind = max(checked[curr_group], checked[curr_group-1]+groups[curr_group-1]+1);
        }
        else {
            start_ind = checked[curr_group];
        }
        for (int ch=start_ind; ch<line.size(); ch++) {
            if ((line[ch] == '?' or line[ch] == '#') and group_fits_chunk(line, ch, groups[curr_group])) {
                checked[curr_group] = ch;
                if (curr_group == groups.size()-1) { // last group and fit means finished solution
                    all_checked.push_back(checked);
                    num_solutions++;
                }
                else {
                    curr_group++;
                    ch += groups[curr_group-1];
                }
            }
        }
        if (curr_group > 0) {
            checked[curr_group-1]++;
            checked[curr_group] = 0;
            curr_group--;
        }
        else {
            done = true;
        }
    }
    for (int i=0; i<all_checked.size(); i++) {
            
        if (!check_solution(line, all_checked[i], groups)) {
                num_solutions--;
        }
        else {
            string printLine = line;
            for (int j=0; j<groups.size(); j++) {
               for (int k=0; k<groups[j]; k++) {
                   printLine[all_checked[i][j]+k] = '#';
               }
            }
            cout << printLine << endl;
        }
    }

    return num_solutions;
}


int main() {
    string dataPath = "test2.txt";
    vector<string> lines = read_lines(dataPath);
    vector<string> records = make_records(lines);
    vector<vector<int>> groups = make_groups(lines);

    int num_solutions = 0;
    int curr_group = 0;
    vector<int> checked;
    int ans = 0;

    for (auto j=0; j<records.size(); j++) { 
        /*
        cout << records[j] << " | ";
        vector<int> group = groups[j];
        for (int i=0; i<group.size(); i++) {
            cout << group[i] << " ";
        }
        cout << " | j: " << j << endl;
*/
        int record_ind = j;
        for (int i=0; i<groups[record_ind].size(); i++) {
            checked.push_back(0);
        }
        int record_ans = find_solutions(records[record_ind], groups[record_ind], curr_group, num_solutions, checked);
        cout << record_ans << endl;
        ans += record_ans;
    }
    
    cout << "ANSWER: " << ans << endl; 

}
