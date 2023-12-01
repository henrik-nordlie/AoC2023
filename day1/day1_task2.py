text = open("day1/day1_codes.txt", "r")
#text = open("day1/test.txt", "r")

nums = ["1","2","3","4","5","6","7","8","9"] 
num_words = ["one","two","three", "four", "five", "six", "seven", "eight", "nine"]
count = 0
codes = []

new_codes = []
for i, line in enumerate(text.readlines()):
    code = ""
    for j, char in enumerate(line):
        if char in nums:
            code += char
        else:
            for k, word in enumerate(num_words):
                if line[j:j+len(word)] == word:
                    j = j+len(word)
                    code += nums[k]
    print(int(code[0]+code[-1]))
    new_codes.append(int(code[0]+code[-1]))

print(sum(new_codes))
            

