#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

vector<string> read_file (string filename) {
        ifstream file(filename);
        vector<string> lines;
        string line;
        while (getline(file, line)) {
                lines.push_back(line);
        }
        return lines;
}

struct state {
    bool seen[100*100];
};

int num_dots_above (vector<string>* lines, int x, int y) {
        int num = 0;
        for (int i = y - 1; i >= 0; i--) {
            if ((*lines)[i][x] == '.') {
                num++;
            }
            else {
                break;
            }
        }
        return num;
}

int num_dots_below (vector<string>* lines, int x, int y, int inp_size) {
        int num = 0;
        for (int i = y + 1; i < inp_size; i++) {
            if ((*lines)[i][x] == '.') {
                num++;
            }
            else {
                break;
            }
        }
        return num;
}

int num_dots_left (vector<string>* lines, int x, int y) {
        int num = 0;
        for (int i = x - 1; i >= 0; i--) {
            if ((*lines)[y][i] == '.') {
                num++;
            }
            else {
                break;
            }
        }
        return num;
}

int num_dots_right (vector<string>* lines, int x, int y, int inp_size) {
        int num = 0;
        for (int i = x + 1; i < inp_size; i++) {
            if ((*lines)[y][i] == '.') {
                num++;
            }
            else {
                break;
            }
        }
        return num;
}

void move_to_top_dot (vector<string>* lines, int x, int y) {
    int num = num_dots_above(lines, x, y);
    if (num > 0) {
        (*lines)[y][x] = '.';
        (*lines)[y - num][x] = 'O';
    }
}

void move_to_bottom_dot (vector<string>* lines, int x, int y, int inp_size) {
    int num = num_dots_below(lines, x, y, inp_size);
    if (num > 0) {
        (*lines)[y][x] = '.';
        (*lines)[y + num][x] = 'O';
    }
}

void move_to_left_dot (vector<string>* lines, int x, int y) {
    int num = num_dots_left(lines, x, y);
    if (num > 0) {
        (*lines)[y][x] = '.';
        (*lines)[y][x - num] = 'O';
    }
}

void move_to_right_dot (vector<string>* lines, int x, int y, int inp_size) {
    int num = num_dots_right(lines, x, y, inp_size);
    if (num > 0) {
        (*lines)[y][x] = '.';
        (*lines)[y][x + num] = 'O';
    }
}



void move_all_north (vector<string>* lines, int inp_size) {
    for (int y = 0; y < inp_size; y++) {
        for (int x = 0; x < inp_size; x++) {
            if ((*lines)[y][x] == 'O') {
                move_to_top_dot(lines, x, y);
            }
        }
    }
}

void move_all_south (vector<string>* lines, int inp_size) {
    for (int y = inp_size - 1; y >= 0; y--) {
        for (int x = 0; x < inp_size; x++) {
            if ((*lines)[y][x] == 'O') {
                move_to_bottom_dot(lines, x, y, inp_size);
            }
        }
    }
}

void move_all_west (vector<string>* lines, int inp_size) {
    for (int y = 0; y < inp_size; y++) {
        for (int x = 0; x < inp_size; x++) {
            if ((*lines)[y][x] == 'O') {
                move_to_left_dot(lines, x, y);
            }
        }
    }
}

void move_all_east (vector<string>* lines, int inp_size) {
    for (int y = 0; y < inp_size; y++) {
        for (int x = inp_size - 1; x >= 0; x--) {
            if ((*lines)[y][x] == 'O') {
                move_to_right_dot(lines, x, y, inp_size);
            }
        }
    }
}

void move_one_cycle (vector<string>* lines, int inp_size) {
    move_all_north(lines, inp_size);
    move_all_west(lines, inp_size);
    move_all_south(lines, inp_size);
    move_all_east(lines, inp_size);
}

void find_seen (vector<string>* lines, int inp_size, bool* seen) {
    for (int y = 0; y < inp_size; y++) {
        for (int x = 0; x < inp_size; x++) {
            if ((*lines)[y][x] == 'O') {
                seen[y * inp_size + x] = true;
            }
        }
    }
}

int seen_before (vector<state> seen_vec, bool* seen, int inp_size) {
    for (int vec = 0; vec < seen_vec.size(); vec++) {
        bool same = true;
        for (int j = 0; j < inp_size*inp_size; j++) {
            if (seen[j] != seen_vec[vec].seen[j]) {
                same = false;
                break;
            }
        }
        if (same) {
            return vec;
        }
    }
    return -1;
}

int find_sum (vector<string>* lines, int inp_size) {
    int sum = 0;
    for (int y = 0; y < inp_size; y++) {
        for (int x = 0; x < inp_size; x++) {
            if ((*lines)[y][x] == 'O') {
                sum += inp_size - y;
            }
        }
    }
    return sum;
}

int find_new_sum (state seen_state, int inp_size) {
    int sum = 0;
    for (int i = 0; i < inp_size*inp_size; i++) {
        int curr_y = i / inp_size;
        int curr_x = i % inp_size;
        if (seen_state.seen[i]) {
            sum += inp_size - curr_y;
        }
    }
    return sum;
}

int find_ans(int num_cycles, int i, bool* seen, int seen_index, vector<state>* seen_vec) {
    int cycle_left_over = num_cycles - i - 1;
    int cycle_start = seen_index;
    int cycle_end = i;
    int cycle_length = cycle_end - cycle_start;
    int cycle_index = cycle_start + (cycle_left_over % cycle_length);
    int ans = find_new_sum((*seen_vec)[cycle_index], 100);
    return ans;
}


int main () {
    vector<string> data_lines = read_file("data.txt");
    cout << data_lines.size() << endl;
    cout << data_lines[0].size() << endl;
    // store size of grid
    int inp_size = 100;
    int num_cycles = 1000000000;
    vector<string>* lines_ptr = &data_lines;
    bool seen[inp_size * inp_size];
    vector<state> seen_vec;
    for (int i = 0; i < inp_size; i++) {
        cout << data_lines[i] << endl;
    }
    for (int i = 0; i < num_cycles; i++) {
        move_one_cycle(lines_ptr, inp_size);
        for (int j = 0; j < inp_size; j++) {
            cout << data_lines[j] << endl;
        }
        cout << i << endl;
        cout << endl;
        for (int j = 0; j < inp_size*inp_size; j++) {
            seen[j] = false;
        }
        find_seen(lines_ptr, inp_size, seen);
        int seen_index = seen_before(seen_vec, seen, inp_size);
        if (seen_index != -1) {
            cout << "seen before" << endl;
            cout << seen_index << endl;
            int ans = find_ans(num_cycles, i, seen, seen_index, &seen_vec);
            cout << ans << endl;
            return 0;
        }
        else {
            state new_state;
            for (int j = 0; j < inp_size*inp_size; j++) {
                new_state.seen[j] = seen[j];
            }
            seen_vec.push_back(new_state);
        } 
    }
    int sum = find_sum(lines_ptr, inp_size);
    return 0;
}

