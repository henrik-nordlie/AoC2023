from numpy import argmin

def count_num_occ(hand):
    num_occurances = {}
    for char in hand:
        if char not in num_occurances.keys():
            num_occurances[char] = 1
        else:
            num_occurances[char] += 1
    return num_occurances

def find_two_largest_occ(num_occurances):
    two_largest_occurance = [0,0]
    for card_type in num_occurances:
        if int(num_occurances[card_type]) > min(two_largest_occurance):
            two_largest_occurance[argmin(two_largest_occurance)] = num_occurances[card_type]
    two_largest_occurance.sort(reverse=True)
    return two_largest_occurance

def replace_J(num_occurances, hand):
    new_hand = hand
    joker = False
    for num_occ in num_occurances:
        if num_occ == "J":
            num_J = num_occurances[num_occ] 
            joker = True
            if num_J == 5:
                return num_occurances, new_hand

    if joker:
        num_occurances.pop("J")
        two_largest = find_two_largest_occ(num_occurances)
        if two_largest == [2,2]: # two pair
            for card in num_occurances:
                hit = False
                num = num_occurances[card] 
                if num == 2:
                    if not hit:
                        top_pair = card
                    else:
                        if int(char_dict[card]) > int(char_dict[top_pair]):
                            top_pair = card
        else:
            largest = two_largest[0]
            for card in num_occurances:
                num = num_occurances[card] 
                if num == largest:
                    top_pair = card
                    break
 
        num_occurances[top_pair] += num_J
        new_hand = new_hand.replace("J", top_pair)
    
    return num_occurances, new_hand

def get_hand_type(hand):
    num_occurances = count_num_occ(hand)
    two_largest_occurance = find_two_largest_occ(num_occurances)
    if two_largest_occurance[0] > 3: # four or five of a kind 
        return str(two_largest_occurance[0]+1)

    if two_largest_occurance[0] == 3: 
        if two_largest_occurance[1] == 2: # full house
            return "4"
        else:
            return "3"
    else:
        if two_largest_occurance[0] == 2:
            if two_largest_occurance[1] == 2: # two pair
                return "2"
            else:
                return "1"
        else:
            return "0"

def score_hand(hand):
    hand_vals = ""
    for char in hand:
        if char.isnumeric():
            hand_vals += "0"+char
        else:
            hand_vals += char_dict[char]  
    return hand_vals

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


def main():
    file = open("data.txt", "r")

    lines = file.read().split("\n")
    hand_dict = {}

    char_dict = {"T":"10",
                 "J":"01",
                 "Q":"12",
                 "K":"13",
                 "A":"14",
                 "2":"2",
                 "3":"3",
                 "4":"4",
                 "5":"5",
                 "6":"6",
                 "7":"7",
                 "8":"8",
                 "9":"9"}
    for line in lines[:-1]:
        hand_bid = line.split()
        hand, bid = hand_bid[0], int(hand_bid[1])
        hand_dict[hand] = [bid]

    # Extend dict with hand type and scores
    for hand in hand_dict:
        num_occurances = count_num_occ(hand)
        num_occurances, new_hand = replace_J(num_occurances, hand)
        hand_type = get_hand_type(new_hand)
        hand_dict[hand].append(int(hand_type+score_hand(hand)))

    sorted_hand_vals = sort_my(hand_dict)

    ans = 0
    for i in range(len(sorted_hand_vals)):
        ans += sorted_hand_vals[i][0]*(len(sorted_hand_vals)-i)
    print(ans)


if __name__ == "__main__":
    main()
