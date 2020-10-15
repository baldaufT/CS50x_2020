from cs50 import get_string

num = get_string("Number: ")

if not (len(num) == 15 or len(num) == 16 or len(num) == 13):
    print("INVALID\n")
else:
    sum = 0
    for i in range (2, len(num) + 1, 2):
        zahl = 2 * int(num[-i])
        if zahl < 10:
            sum += zahl
        else:
            sum += zahl % 10
            sum += 1

    for i in range (1, len(num) + 1, 2):
        sum += int(num[-i])

    if not sum % 10 == 0:
        print("INVALID\n")
    else:
        if int(num[:2]) == 34 or int(num[:2]) == 37:
            print("AMEX\n")
        elif int(num[:2]) > 50 and int(num[:2]) < 56: #Mastercard
            print("MASTERCARD\n")
        elif int(num[:1]) == 4: #VISA
            print("VISA\n")
        else:
            print("INVALID\n")