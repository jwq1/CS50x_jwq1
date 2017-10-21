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

        # convert text to string. Tokenize method expects string or bytes-like object
        text_string = str(text)

        # tokenize text
        tokenizer = nltk.tokenize.TweetTokenizer()
        tokens = tokenizer.tokenize(text_string)

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


    def percent_sentiments(self, tweets):
        """Analyze a list of tweets, returning percent +, -, and 0"""

        score = 0
        total_tweets = 0
        number_positive = 0
        number_negative = 0
        number_neutral = 0

        for tweet in tweets:
            score = analyzer.analyze(tweet)
            total_tweets += 1
            if score > 0.0:
                number_positive += 1
            elif score < 0.0:
                number_negative += 1
            else:
                number_neutral += 1

        percent_positive = float(number_positive / total_tweets)
        percent_negative = float(number_negative / total_tweets)
        percent_neutral = 100 - number_postive - number_negative

        return percent_positive, percent_negative, percent_neutral