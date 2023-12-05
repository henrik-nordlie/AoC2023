file = open("data.txt", "r")


ans = 0
for i, line in enumerate(file.readlines()):
    game, line = line.split(":")
    winners, mine = line.split("|")

    game_ans = 0
    j = 0
    for winner in winners.split():
        for num in mine.split():
            if num == winner:
                game_ans = 2**j
                j += 1
    print(game_ans)
    ans += game_ans
print(ans)

