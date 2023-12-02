import re

color_count = {"red":12, "green":13, "blue":14}

data = open("data.txt", "r")
games = data.readlines()

answer = 0


for gameID, game in enumerate(games):

    highest_col_count_dict = {}
    for col in color_count.keys():
        highest_col_count_dict[col] = 0

    valid = True
    results = re.search("(?<=:).*$", game).group(0).split(";")
    # [' 3 blue, 4 red', ' 1 red, 2 green, 6 blue', ' 2 green']
    for result in results:
        for res in result.split(","):
            for color, num in color_count.items():
                hit = re.search(r""+color, res)
                if hit:
                    num = int (re.sub(r'[^\d]+', '', res))
                    highest_col_count_dict[color] = max(highest_col_count_dict[color], num)
    prod = 1
    for val in highest_col_count_dict.values():
        prod *= val
    answer += prod

print(answer)
                        




#legg til på gameID

