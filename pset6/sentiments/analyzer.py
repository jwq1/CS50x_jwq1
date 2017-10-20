import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, positives, negatives):
        """Initialize Analyzer."""

        def load_words(txt_file):

            # Create set in which to store words from the text file
            words = set()

            # Open file positive-words.txt (read)
            file = open(txt_file, "r")

            # for each line in file (each line is a word)
            for line in file:
                # if line starts with a semicolon, space, or linebreak
                if str.startswith(line,";" or " " or "\n"):
                    # loop to next line
                    continue
                # else this is probably a word
                else:
                    # strip off the trailing whitespace and linebreak
                    word = line.rstrip("\n")
                    # then if all that is left are alphabetic characters, assume we have a word
                    if str.isalpha(word):
                        # add the word to "words," the set we created earlier.
                        words.add(word)

            # close the file
            file.close()

            # return our set of words
            return words

        # TODO
        self.positives = load_words(positives)
        self.negatives = load_words(negatives)


    def analyze(self, text):
        """Analyze text for sentiment, returning its score."""

        # TODO
        return 0
