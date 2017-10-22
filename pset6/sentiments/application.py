from flask import Flask, redirect, render_template, request, url_for

import helpers
from analyzer import Analyzer

import os
import sys

app = Flask(__name__)

@app.route("/")
def index():
    return render_template("index.html")

@app.route("/search")
def search():

    # validate screen_name
    screen_name = request.args.get("screen_name", "")
    if not screen_name:
        return redirect(url_for("index"))

    # TODO
    # positive, negative, neutral = 0.0, 0.0, 100.0

    # absolute paths to lists
    positives = os.path.join(sys.path[0], "positive-words.txt")
    negatives = os.path.join(sys.path[0], "negative-words.txt")

    # instantiate analyzer
    analyzer = Analyzer(positives, negatives)

    # get screen_name's tweets
    tweets = helpers.get_user_timeline(screen_name)


    def percent_sentiments(tweets):
        """Analyze a list of tweets, returning percent +, -, and 0"""

        # start all the sentiments at 0
        score = 0
        total_tweets = 0
        number_positive = 0
        number_negative = 0
        number_neutral = 0


        # Add up the values for each sentiment
        try:
            for tweet in tweets:
                score = analyzer.analyze(tweet)
                total_tweets += 1
                if score > 0.0:
                    number_positive += 1
                elif score < 0.0:
                    number_negative += 1
                else:
                    number_neutral += 1
        # If there was no account associated to a given username, redirect to index.html
        except TypeError:
            return redirect(url_for("index"))

        # Calculate the percentages for each sentiment
        try:
            percent_positive = float(number_positive / total_tweets)
            percent_negative = float(number_negative / total_tweets)
            percent_neutral = 1 - percent_positive - percent_negative

        # If username has not made any tweets (e.g. @jw1)
        except ZeroDivisionError:
            # redirect to the index.html page
            return redirect(url_for("index"))

        # return the percentages for each sentiment
        return percent_positive, percent_negative, percent_neutral


    try:
        # Ask for the percent of sentiments
        positive, negative, neutral = percent_sentiments(tweets)
    # If there was no public account for given username, redirect to the index.html page
    except TypeError:
        return redirect(url_for("index"))

    print(positive, negative, neutral)

    # generate chart
    chart = helpers.chart(positive, negative, neutral)

    # render results
    return render_template("search.html", chart=chart, screen_name=screen_name)

