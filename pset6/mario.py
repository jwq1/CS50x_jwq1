def main():

    h = getOnlyInt("Height: ")

    while True:
        if (h < 0 or h > 23):
            h = getOnlyInt("Height: ")
            continue
        else:
            break

    # we must have the right input
    for i in range(h):
    # print spaces
        print(" ", end ="")
        print(" " * ((h-1) - (1*i)), end ="")
        # print hashes
        print("#" * i, end ="")
        print("#" * 1)



def getOnlyInt(h):
    while True:
        try:
            # Get integer value for height
            h = int(input(h))
        except ValueError:
            # return to start of loop
            continue
        else:
            return h
            break

if __name__ == "__main__":
    main()