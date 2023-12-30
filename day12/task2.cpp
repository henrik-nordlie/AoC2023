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

struct group_memory {
    //these should be same length (length of groups vector)
    vector<int> positions;
    vector<int> solutions;
};

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
        string record = "";
        for (int j=0; j<4; j++) {
            record += p;
            record += "?";
        }
        record += p;

        // remove leading and trailing "."s
        string line;
        string strippedLine;
        for (int ch=0; ch<record.size(); ch++) {
            if (record[ch] != '.') {
                for (int i=ch; i<record.size(); i++) {
                    line.push_back(record[i]);
                }
                break;
            }
        }
        for (int ch=line.size()-1; ch>=0; ch--) {
           if (line[ch] != '.') {
                for (int i=0; i<=ch; i++) {
                    strippedLine.push_back(line[i]);
                }
                break;
           }
        } 
        records.push_back(strippedLine);
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
        vector<int> extended_group;
        for (int k=0; k<5; k++) {
            for (int j=0; j<group.size(); j++) {
                extended_group.push_back(group[j]);
            }
        }
        groups.push_back(extended_group);
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

bool all_hash_used (string line, vector<int> solution, vector<int> groups) {
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

bool contains_duplicate (vector<int> vec) {
    for (int i=0; i<vec.size(); i++) {
        for (int j=i+1; j<vec.size(); j++) {
            if (vec[i] == vec[j]) {
                return true;
            }
        }
    }
    return false;
}

bool check_solution(string line, vector<int> checked, vector<int> groups) {
    for (int i=0; i<groups.size(); i++) {
        if (!group_fits_chunk(line, checked[i], groups[i])) {
            return false;
        }
    }
    if (!all_hash_used(line, checked, groups)) {
        return false;
    }
    if (contains_duplicate(checked)) {
        return false;
    }
    return true;
}

bool unused_hash_before (string line, vector<int> checked, int curr_group, vector<int> groups) {
    for (int ch=0; ch<checked[curr_group]; ch++) {
        if (line[ch] == '#') {
            bool in_sol = false;
            for (int i=0; i<curr_group; i++) {
                for (int j=0; j<groups[i]; j++) {
                    if (checked[i]+j == ch) {
                        in_sol = true;
                        break;
                    }
                }
            }
            if (!in_sol) {
                return true;
            }
        }
    }
    return false;
}

void increment_prev_val_sol (string line, vector<int> checked, vector<int> groups, group_memory* groups_mem, int pos_ind, int known_sols, int i) {
    vector<int>* positions = &groups_mem->positions;
    for (int j=pos_ind-1; j>=0; j--) {
        checked[i] = positions->at(j);
        if (true) { //check_solution(line, checked, groups)) {
            groups_mem->solutions[j] += known_sols;
        }
    }
}

void update_group_mem (string line, vector<int> checked, vector<int> groups, group_memory* groups_mem, int i, int known_sols) {
    vector<int>* positions = &groups_mem[i].positions;
    int pos_ind = distance(positions->begin(), find(positions->begin(), positions->end(), checked[i]));
    if (!binary_search(positions->begin(), positions->end(), checked[i])) {
        positions->push_back(checked[i]);
        groups_mem[i].solutions.push_back(known_sols);
    }
    else {
        groups_mem[i].solutions[pos_ind] += known_sols;
    }
    positions = &groups_mem[i].positions;
    pos_ind = distance(positions->begin(), find(positions->begin(), positions->end(), checked[i]));
    increment_prev_val_sol(line, checked, groups, &groups_mem[i], pos_ind, known_sols, i);
}
    
int find_solutions (string line, vector<int> groups, int curr_group, int num_solutions, vector<int> checked) {
    bool done = false;
    int start_ind = 0;
    group_memory groups_mem [groups.size()];
    group_memory* groups_mem_ptr = groups_mem;
    int known_sols;
    vector<int> checked_before_inc;

    while (!done) {
        vector<int>* positions = &groups_mem[curr_group].positions;
        int pos_ind = distance(positions->begin(), find(positions->begin(), positions->end(), start_ind));
        for (int ch=start_ind; ch<line.size(); ch++) {
            positions = &groups_mem[curr_group].positions;
            if (binary_search(positions->begin(), positions->end(), ch)) {
                checked[curr_group] = ch;
                if (unused_hash_before(line, checked, curr_group, groups)) {
                    continue;
                }
                pos_ind = distance(positions->begin(), find(positions->begin(), positions->end(), ch));
                known_sols = groups_mem[curr_group].solutions[pos_ind];
                num_solutions += known_sols;
                increment_prev_val_sol(line, checked, groups, &groups_mem[curr_group], pos_ind, known_sols, curr_group);
                for (int i=curr_group-1; i>=0; i--) {
                    update_group_mem(line, checked, groups, groups_mem_ptr, i, known_sols);
                }
                /*
                for (int i=0; i<groups.size(); i++) {
                    if (checked[i] > checked_before_inc[i]) {
                        curr_group = i+1;
                        break;
                    }
                
                }
                */
                break;
            }
            else if ((line[ch] == '?' or line[ch] == '#') and group_fits_chunk(line, ch, groups[curr_group])) {
                checked[curr_group] = ch;
                if (curr_group == groups.size()-1) { // last group and fit means finished solution
                    if (check_solution(line, checked, groups)) {
                        num_solutions++;
                        for (int i=0; i<groups.size(); i++) {
                            update_group_mem(line, checked, groups, groups_mem_ptr, i, 1);
                        }
                    }
                }
                else {
                    ch += groups[curr_group];
                    curr_group++;
                    start_ind = ch+1;
                }
            }
        }
        if (curr_group > 0) {
            checked_before_inc = checked;
            checked[curr_group-1]++;
            curr_group--;
            start_ind = checked[curr_group];
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

    
    int ans = 0;

    for (auto j=0; j<records.size(); j++) { 
        int num_solutions = 0;
        int curr_group = 0;
        vector<int> checked;
        
        cout << records[j] << " | ";
        vector<int> group = groups[j];
        for (int i=0; i<group.size(); i++) {
            cout << group[i] << " ";
        }
        cout << " | j: " << j << endl;

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
