from cs50 import get_float

c = get_float("Change owned: ")

#Prompt user to input valid value
while (c < 0):
    c = get_float("Change owned: ")

#Convert dollar into cents
cents = c * 100

#Declare number of coins to count
coins = 0

#Count coins
while cents >= 25:
    cents -= 25
    coins += 1

while cents >= 10:
    cents -= 10
    coins += 1

while cents >= 5:
    cents -= 5
    coins += 1

while cents >= 1:
    cents -= 1
    coins += 1

print(coins)