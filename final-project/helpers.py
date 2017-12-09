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
    row = db.execute("""
    INSERT INTO products
    (id, category_id, product_name, link, description, image, brand, price)
    VALUES (NULL, 1, 'long sleeve henley tee',
    'https://wearpact.com/men/apparel/tops%20&%20shirts/long%20sleeve%20henley%20tee?id=wa1-mhe-chh',
    'Made with 100% organic cotton',
    'https://static.wearpact.com/img/product/men/mhe-chh-3-1505335935.jpg',
    'PACT Apparel', 35)""")



# Find our record for this product
def find_product(product_requested):

    # Create a parameter to search our database
    # for any records, which contain the product name.
    product_parameter = "%" + product_requested + "%"

    try:
        #Search the database for the requested product.
        product_data = db.execute("""
            SELECT *
            FROM products
            WHERE product_name
            LIKE :product
            LIMIT 1""",
            product=product_parameter)

    except RuntimeError:
        # If problem with db.execute, then apologize.
        return apology("Error: We'll fix this. Please try again shortly.")

    # Make sure we found a product.
    if product_data == None:
        return apology("""
            We're sorry, we do not have information for """
            + product_requested +
            """. Please consider adding this product to
            our site, via the "Add Product" tab """)


    # Otherwise, return information about the requested product.
    return product_data
