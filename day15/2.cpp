#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdlib>
using namespace std;

struct step {
    string label;
    int num;
};

vector<string> get_lines(string filename) {
    vector<string> lines;
    char c;
    string line;
    fstream fs(filename);
    while(fs >> c) {
        if (c==',') {
            lines.push_back(line);
            line = "";
        }
        else {
            line.push_back(c);
        }
    }
    lines.push_back(line);
    return lines;
}



int algo(int curr_num) {
    int ascii_val = int(curr_num);
    ascii_val*=17;
    return ascii_val%256;
}

int get_ans (string chunk) {
    int curr_num = 0;
    for (char c : chunk) {
        curr_num += int(c);
        curr_num = algo(curr_num);
    }
    return curr_num;
}

unordered_map<int, vector<step>> split_line(vector<string> lines) {
    unordered_map<int, vector<step>> data;
    for (string line : lines) {
        string label = "";
        string num_str = "";
        int num;
        bool is_label = true;
        bool remove = false;
        for (char c : line) {
            if (is_label) {
                if (c=='=' or c=='-') {
                    is_label = false;
                    if (c=='-') {
                        remove = true;
                    }
                }
                else {
                    label.push_back(c);
                }
            }
            else {
                num_str.push_back(c);
            }
        }
        num = atoi(num_str.c_str());
        int box = get_ans(label);
        step s;
        s.label = label;
        s.num = num;
        if (!remove) {
            if (data.find(box) == data.end()) {
                vector<step> v;
                v.push_back(s);
                data[box] = v;
            }
            else {
                for (int i=0; i<data[box].size(); i++) {
                    if (data[box][i].label == s.label) {
                        data[box][i].num = s.num;
                        break;
                    }
                    else if (i==data[box].size()-1) {
                        data[box].push_back(s); 
                        break;
                    }
                }
            }
        }
        else {
            if (data.find(box) != data.end()) {
                for (int i=0; i<data[box].size(); i++) {
                    if (data[box][i].label == s.label) {
                        data[box].erase(data[box].begin()+i);
                        break;
                    }
                }
            }
        }
    }
    return data;
}

int calculate_power(int box_num, vector<step> steps) {
    int power = 0;
    int slot = 1;
    for (step s : steps) {
        int add_power = (box_num+1)*slot*s.num;
        cout << "add_power: " << add_power << endl;
        power += add_power;
        slot++;
    }
    return power;
}

int main () {
    string filename = "data.txt";
    vector<string> lines = get_lines(filename);
    unordered_map<int, vector<step>> data = split_line(lines);
    int ans = 0;
    for (auto it=data.begin(); it!=data.end(); it++) {
        int box_num = it->first;
        vector<step> steps = it->second;
        int power = calculate_power(box_num, steps);
        cout << "box_num: " << box_num << endl;
        cout << "power: " << power << endl;
        ans += power;
    }
    cout << "ANSWER: " << ans << endl;
    return 0;
}
