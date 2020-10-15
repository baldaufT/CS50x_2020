from cs50 import get_string

text = get_string("Text: ")

#get input numbers
sent = 0
words = 1
letters = 0
h = 0

for i in text:
    if i is "." or i is "!" or i is "?":
        sent += 1
    if i is " ":
        words += 1
    if i is "'" or i is ":" or i is '"' or i is ";" or i is ",":
        h += 1

letters = len(text) - words + 1 - sent - h

#Calculate S and L
S = (100 / words) * sent
L = (100 / words) * letters

print("wsl: " + str(words) + ", " + str(sent) + ", " + str(letters) + " and S is " + str(S) + " and L is " + str(L) + ". ")

# Calculate grade level
grade = 0.0588 * L - 0.296 * S - 15.8

#round grade to nearest integer number
grade = round(grade)

# output grade level
if grade < 1:
    print("Before Grade 1")
elif grade > 15:
    print("Grade 16+")
else:
    print("Grade " + str(grade))