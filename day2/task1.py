import re

color_count = {"red":12, "green":13, "blue":14}

data = open("data.txt", "r")
games = data.readlines()

answer = 0



for gameID, game in enumerate(games):
    color_list = color_count.keys
    valid = True
    results = re.search("(?<=:).*$", game).group(0).split(";")
    # [' 3 blue, 4 red', ' 1 red, 2 green, 6 blue', ' 2 green']
    for result in results:
        for res in result.split(","):
            for color, num in color_count.items():
                hit = re.search(r""+color, res)
                if hit:
                    if int(re.sub(r'[^\d]+', '', res)) > color_count[color]:
                        valid = False
    if valid:
        answer += gameID+1

print(answer)
                        




#legg til på gameID
