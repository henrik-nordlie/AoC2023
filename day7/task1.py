from numpy import argmin

file = open("data.txt", "r")

lines = file.read().split("\n")
hand_dict = {}

for line in lines[:-1]:
    print(line)
    print(80*"=")
    hand_bid = line.split()
    hand, bid = hand_bid[0], int(hand_bid[1])
    hand_dict[hand] = [bid]

def hand_type(hand):
    num_occurances = {}
    for char in hand:
        if char not in num_occurances.keys():
            num_occurances[char] = 1
        else:
            num_occurances[char] += 1

    two_largest_occurance = [0,0]
    for card_type in num_occurances:
        if num_occurances[card_type] > min(two_largest_occurance):
            two_largest_occurance[argmin(two_largest_occurance)] = num_occurances[card_type]
    two_largest_occurance.sort(reverse=True)
    if two_largest_occurance[0] > 3: # four or five of a kind 
        return str(two_largest_occurance[0]+1)          

    if two_largest_occurance[0] == 3: 
        if two_largest_occurance[1] == 2: # full house
            return "4"
        else:
            return "3" # three of a kind
    else:
        if two_largest_occurance[0] == 2:
            if two_largest_occurance[1] == 2: # two pair
                return "2"
            else:
                return "1"
        else:
            return "0"

def score_hand(hand):
    char_dict = {"T":"10", "J":"11", "Q":"12", "K":"13", "A":"14"}
    hand_vals = ""
    for char in hand:
        if char.isnumeric():
            hand_vals += "0"+char
        else:
            hand_vals += char_dict[char]
    return hand_vals


def swap_hands(hand1, hand2):
    if hand1[1] > hand2[1]:
        return False
    elif hand2[1] > hand1[1]:
        return True
    else: # same hand type
        hand1_score = hand1[2]
        hand2_score = hand2[2]

        for i, val in enumerate(hand1_score):
            if hand2_score[i] > val:
                return True
            elif val > hand2_score:
                return False
        # if here they are the same
        return False

# Extend dict with hand type and scores
for hand in hand_dict:
    hand_dict[hand].append(int(hand_type(hand)+score_hand(hand)))

print(hand_dict)

def sort_my(dic):
    
    sorted_hand_vals = []
    for hand in dic:
        bid = dic[hand][0]
        val = dic[hand][1]
         
        if len(sorted_hand_vals) > 0:
            for j in range(len(sorted_hand_vals)):
                if val >= sorted_hand_vals[j][1]:
                    sorted_hand_vals.insert(j, [bid, val])
                    break
                elif j == len(sorted_hand_vals)-1:
                    sorted_hand_vals.append([bid, val])
                    break
        else:
            sorted_hand_vals.append([bid, val])
    return sorted_hand_vals

sorted_hand_vals = sort_my(hand_dict)

ans = 0
for i in range(len(sorted_hand_vals)):
    ans += sorted_hand_vals[i][0]*(len(sorted_hand_vals)-i)
print(ans)
