file = open("data.txt", "r")


ans = 0
card_dict = {}
lines = file.readlines()

for i, line in enumerate(lines): 
    game, line = line.split(":")
    winners, mine = line.split("|")
    if card_dict.get(str(i+1), False):
        copies = card_dict[str(i+1)]+1
    else:
        copies = 1
        card_dict[str(i+1)] = 0
    j = 0
    for winner in winners.split():
        for num in mine.split():
            if num == winner:
                j += 1
    for n in range(copies):
        ans += 1
        for k in range(j):
            if card_dict.get(str(i+k+2), False):
                card_dict[str(i+k+2)] += 1
            else:
                card_dict[str(i+k+2)] = 1
print(ans)
