import sys
import curses.ascii

def main ():

    # Get key from user in command line argument 1
    key = get_key()

    # Get text to encrypt
    users_text = get_plaintext("plaintext:  ")

    # Encrypt text
    ciphertext = encrypt(users_text, key)

    # Print ciphertext
    print("ciphertext: ", end = "")
    for c in ciphertext:
        print(format(c), end = "")
    print()

# Get key for encryption from user
def get_key():

    while True:
        try:
            # convert argument to an integer
            key_int = int(sys.argv[1])
        except (ValueError, IndexError):
            # return to start of loop
            sys.exit("Usage: ./caesar k")
        if len(sys.argv) != 2 or key_int < 0:
            sys.exit("Usage: ./caesar k")
        else:
            # return key as integer
            return key_int
            # exit loop
            break


# Get plaintext from user
def get_plaintext(text_input):

    # ask for input
    while True:
        try:
            # save input to txt
            txt = str(input(text_input))
        except ValueError:
            continue
        # check each character in txt
        for c in txt:
            # if alphabetic continue
            if curses.ascii.isalpha(c) != True and curses.ascii.isblank(c) != True and curses.ascii.ispunct(c) != True:
                print("Please only use alphabetic characters")
                # ask for new input
                get_plaintext("plaintext: ")
        # else we must have gotten plaintext characters
        else:
            return txt
            break




# Encrypt the user's plaintext
def encrypt(text_to_encrypt, key):

    ciphertext = []

    int_txt = text_to_encrypt

    for c in int_txt:
        # count which letter we are on
        index = 0
        # Encrypt and perserve uppercase
        if curses.ascii.isupper(c):
            cipherletter = chr((((ord(c) - 65) + key) % 26) + 65)
            ciphertext.append(cipherletter)
            index += 1
        # Encrypt and perserve lowercase
        elif curses.ascii.islower(c):
            cipherletter = chr((((ord(c) - 97) + key) % 26) + 97)
            ciphertext.append(cipherletter)
            index += 1
        # Must be a space or punctuation. Skip
        # We checked for non-alpha in get_plaintext function
        else:
            cipherletter = c
            ciphertext.append(cipherletter)
            index += 1

    return ciphertext


# Tell python to call the main function
if __name__ == "__main__":
    main()