text = open("day1/day1_codes.txt", "r")
nums = ["0","1","2","3","4","5","6","7","8","9"]
count = 0
codes = []
for i, line in enumerate(text.readlines()):
    code = ""
    for char in line:
        if char in nums:
            code += char
    codes.append(int(code[0]+code[-1]))

print(sum(codes))
            

