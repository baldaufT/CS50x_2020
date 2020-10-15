from cs50 import SQL
from sys import argv, exit

if len(argv) != 2:
    print("Usage: python import.py 'resp.house'")
    exit(1)

db = SQL("sqlite:///students.db")
roster = db.execute("SELECT first, middle, last, birth FROM students WHERE house = ? ORDER BY last ASC, first ASC;", argv[1])

for ro in roster:
    if ro["middle"] == "NULL":
        print(ro["first"], ro["last"] + ", born " + str(ro["birth"]))
    else:
        print(ro["first"], ro["middle"], ro["last"] + ", born " + str(ro["birth"]))