import cs50

def main():

    print ("O hai! ", end = "")
    cents = int(getChange("How much change is owed? \n"))

    # error check (DELETE LATER)
    print ("cents",cents)

    # Number of coins required
    coins = getCoins(cents)

    print(coins)

# Return minimum number of coins needed to make "centsAmount" of cents
def getCoins(centsAmount):

    # condense centsAmount to ca for brevity
    ca = centsAmount

    # start with zero coins
    coin = 0

    # return coins need
    while True:
        # plus 1 quarter
        if ca % 25 == 0 and ca > 0:
            coin += 1
            ca = ca - 25
        # plus 1 dime
        elif ca % 10 == 0 and ca > 0:
            coin += 1
            ca -= 10
        # plus 1 nickel
        elif ca % 5 == 0 and ca > 0:
            coin += 1
            ca -= 5
        # plus 1 penny
        elif ca % 1 == 0 and ca > 0:
            coin += 1
            ca -= 1
        # we must have all our change
        else:
            # return number of coins
            return coin
            break


# Convert the required amount of change ($) to cents
def getChange(changeNeeded):

    while True:
        try:
            # Get change needed in dollars
            cn = float(input(changeNeeded))
        except ValueError:
            # return to start of loop
            continue
        if cn < 0:
            continue
        else:
            # convert to cents
            cents = cn * 100
            # return cents to user
            return cents
            # exit loop
            break


# tell python call the main fuction
if __name__ == "__main__":
    main()