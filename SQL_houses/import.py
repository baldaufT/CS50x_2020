from cs50 import SQL
from sys import argv, exit
import csv

if len(argv) != 2:
    print("Usage: python import.py data.csv")
    exit(1)

db = SQL("sqlite:///students.db")

with open(argv[1], newline="") as csv_file:
    csvreader = csv.reader(csv_file)

    name = []
    house = "NULL"
    birth = 0

    for row in csvreader:
        if row[0] == "name":
            continue
        name = row[0].split(" ")
        house = row[1]
        birth = row[2]
        if len(name) is 2:
            name = [name[0], "NULL", name[1]]
        db.execute("INSERT INTO students (first, middle, last, house, birth) VALUES(?,?,?,?,?)", name[0], name[1], name[2], house, birth)