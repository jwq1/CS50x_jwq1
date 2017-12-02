# Final Project | helpers | (jwq1)

import csv
import urllib.request
import random

from flask import redirect, render_template, request, session
from functools import wraps

import feedparser
import urllib.parse

from cs50 import SQL

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///final.db")


def apology(message, code=400):
    """Renders message as an apology to user."""
    def escape(s):
        """
        Escape special characters.

        https://github.com/jacebrowning/memegen#special-characters
        """
        for old, new in [("-", "--"), (" ", "-"), ("_", "__"), ("?", "~q"),
                         ("%", "~p"), ("#", "~h"), ("/", "~s"), ("\"", "''")]:
            s = s.replace(old, new)
        return s
    return render_template("apology.html", top=code, bottom=escape(message)), code


def login_required(f):
    """
    Decorate routes to require login.

    http://flask.pocoo.org/docs/0.12/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def usd(value):
    """Formats value as USD."""
    return f"${value:,.2f}"

def usd_db(value):
    """Formats value as USD."""
    return f"{value:,.2f}"

def add_test_product():
    row = db.execute("INSERT INTO products (id, category_id, product_name, link, description, image, brand, price) VALUES (NULL, 1, 'long sleeve henley tee', 'https://wearpact.com/men/apparel/tops%20&%20shirts/long%20sleeve%20henley%20tee?id=wa1-mhe-chh', 'Made with 100% organic cotton', 'https://static.wearpact.com/img/product/men/mhe-chh-3-1505335935.jpg', 'PACT Apparel', 35)")

# Create flexible query parameters.
def make_parameters_flexible(query_input):

    # Create a parameter to search our database for similar products.
    sql_query_parameter = "%" + query_input + "%"

    # Send query parameter.
    return sql_query_parameter