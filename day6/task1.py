import re

file = open('data.txt', 'r')
lines = file.read().split('\n')
file.close()

time = lines[0]
distance = lines[1]

time = re.findall(r'\d+', time)
distance = re.findall(r'\d+', distance)

def calculate_dist(total_time, button_time):
    return (total_time-button_time)*button_time

def check_wins(total_time, d2):
    wins = 0
    for button_time in range(total_time):
        d1 = calculate_dist(total_time, button_time)
        if d1 > d2:
            wins += 1
    return wins

num_wins_mult = 1
for i, time in enumerate(time):
    num_wins_mult *= check_wins(int(time), int(distance[i]))
    
print(num_wins_mult)
