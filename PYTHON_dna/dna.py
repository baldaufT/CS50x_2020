from sys import argv, exit
import csv

if len(argv) != 3:
    print("Usage: python dna.py data.csv sequence.txt")
    exit(1)

codes = []
string = "ok"
result = {}
length = 0

with open(argv[1], newline="") as csv_file:
    csvreader = csv.reader(csv_file)
    for row in csvreader:
        for col in row:
            codes.append(col)
        break
    codes = codes[1:]

    with open(argv[2], "r") as txt_file:
        string = txt_file.read()
    length = len(string)

    for code in codes:
        result[code] = 0

    i = 0
    count = 0
    found = False
    zwcount = 0
    for code in codes:
        count = 0
        zwcount = 0
        i = 0
        while i + len(code) <= length:
            found = False
            if code in string[(i):(i+len(code))]:
                count += 1
                found = True
            if found:
                i += len(code)
            else:
                i += 1
                if zwcount < count:
                    zwcount = count
                count = 0
        result[code] = zwcount

    #finden des richtigen Namens zu Werten in result
    name = "ok"
    length = len(result)
    result_array = []
    for code in codes:
        result_array.append(result[code])

    for row in csvreader:
        personalValues = []
        for col in row:
            personalValues.append(col)
        name = personalValues[0]
        personalValues = personalValues[1:]
        i = 0
        while i < length:
            if int(personalValues[i]) != int(result_array[i]):
                break
            i += 1
            if i == length:
                print(str(name))
                exit(0)
    print("No match")
exit(0)