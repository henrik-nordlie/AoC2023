#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <cstdlib>
#include <cstring>


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
    for (int i=0; i<lines.size()-1; i++) {
        group.clear();
        string line = lines[i];
        for (int c=0; c<=line.size(); c++) {
            if (line[c] == ',' or c == line.size()) {
                char num_char = line[c-1];
                group.push_back(atoi(&num_char));
            }
        }
        groups.push_back(group);
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


    
int find_solutions (string line, vector<int> groups, int curr_group, int num_solutions, vector<int> checked) {
    bool done = false;
    int start_ind = 0;
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
    return num_solutions;
}


int main() {
    string dataPath = "data.txt";
    vector<string> lines = read_lines(dataPath);
    vector<string> records = make_records(lines);
    vector<vector<int>> groups = make_groups(lines);

    int num_solutions = 0;
    int curr_group = 0;
    vector<int> checked;
    int ans = 0;

    for (auto j=0; j<records.size(); j++) { 
        cout << records[j] << " | ";
        vector<int> group = groups[j];
        for (int i=0; i<group.size(); i++) {
            cout << group[i] << " ";
        }
        cout << endl;

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
