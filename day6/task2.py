import re
import math

file = open('data.txt', 'r')
lines = file.read().split('\n')
file.close()

time = lines[0]
distance = lines[1]

time = re.findall(r'\d+', time)
distance = re.findall(r'\d+', distance)

new_time = ""
new_dist = ""
for tid in time:
    new_time += tid
for dist in distance:
    new_dist += dist

def find_press_time(t, distance):
    c1 = (t - math.sqrt((t**2) - 4*distance))/2
    c2 = (t + math.sqrt((t**2) - 4*distance))/2
    return [c1, c2] 

press_times = find_press_time(int(new_time), int(new_dist))
num_wins = math.ceil(press_times[1])-math.floor(press_times[0])-1
print(num_wins)

