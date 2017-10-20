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
                # otherwise assume we have a word
                else:
                    # strip off the trailing whitespace and linebreak
                    word = line.rstrip("\n")
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

        # Start with score of zero
        score = 0

        # tokenize text
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text)

        # iterate over tokens
        for token in tokens:
            # if word has a positive sentiment
            if token in self.positives:
                # increase score
                score += 1
            # if word has a negative sentiment
            elif token in self.negatives:
                # decrease score
                score -= 1
            # otherwise sentiment is neutral
            else:
                # do nothing
                score = score

        # return score
        return score
