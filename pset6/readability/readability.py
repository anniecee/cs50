from cs50 import get_string

text = get_string("Text: ")

#Initiate words, letters & sentences to count
words = 1
letters = 0
sentences = 0

#Count letter & sentence
for i in range(len(text)):
    if (text[i].isspace() == True):
        words += 1

    if (text[i].isalpha() == True):
        letters += 1

    if (text[i] == '.' or text[i] == '?' or text[i] == '!'):
        sentences += 1

#Average
L = letters / words * 100
S = sentences / words * 100

#Plug in Coleman-Liau formula to get grade level
X = round(0.0588 * L - 0.296 * S - 15.8)

#Print out grade level
if X < 16 and X >= 1:
    print(f"Grade {X}")

else:
    if X >= 16:
        print("Grade 16+")

    if X < 1:
        print("Before Grade 1")

