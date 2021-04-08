from cs50 import get_int

h = get_int("Height: ")
while (h < 1 or h > 8):
    h = get_int("Height: ")
for i in range(1, h + 1):
    print(" "*(h-i), end="")
    print("#"*i, end="\n")