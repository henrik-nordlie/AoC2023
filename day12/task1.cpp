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


int main() {
    string dataPath = "test.txt";
    vector<string> lines = read_lines(dataPath);
    
    for (int i=0; i<lines.size()-1; i++) {
        cout << lines[i] << endl;}
    cout << "-------------------" << endl;

    vector<string> records = make_records(lines);
    vector<vector<int>> groups = make_groups(lines);

    for (int i=0; i<records.size(); i++) {
        cout << records[i] << " | ";
        vector<int> group = groups[i];
        for (int j=0; j<group.size(); j++) {
            cout << group[j] << " ";
        }
        cout << endl;
    }
    

}
