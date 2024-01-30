#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;


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

int get_ans (string step) {
    int curr_num = 0;
    for (char c : step) {
        curr_num += int(c);
        curr_num = algo(curr_num);
    }
    return curr_num;
}


int main () {
    string filename = "data.txt";
    vector<string> lines = get_lines(filename);
    int ans = 0;
    for (string line : lines) {
        ans += get_ans(line);
    }
    cout << "ANSWER: " << ans << endl;
    return 0;
}
