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

# Return a list of all categories.
def all_categories():

    # Select a list of categories from the database.
    category_rows = db.execute("SELECT category FROM categories;")

    # Create an empty list to store each category.
    list_of_categories = []

    # Get the number of categories.
    category_list_length = len(category_rows)

    # Store the list categories.
    for row in range(category_list_length):
        list_of_categories.append(category_rows[row]["category"])

    # Return the list of categories.
    return list_of_categories

# Find all the products in a specific category.
def search_by_category(selected_category):

    # Get the category information for the selected category.
    category_row = db.execute("""
            SELECT category FROM categories
            WHERE category=:selected_category"""
            , selected_category=selected_category)

    # Save the category id.
    category_id = category_row[0]["id"]

    # Search for products with the same category id.
    product_rows = db.execute("""
            SELECT * FROM products WHERE category_id=:category_id"""
            , category_id=category_id)

    return product_rows


def add_test_product():
    row = db.execute("INSERT INTO products (id, category_id, product_name, link, description, image, brand, price) VALUES (NULL, 1, 'long sleeve henley tee', 'https://wearpact.com/men/apparel/tops%20&%20shirts/long%20sleeve%20henley%20tee?id=wa1-mhe-chh', 'Made with 100% organic cotton', 'https://static.wearpact.com/img/product/men/mhe-chh-3-1505335935.jpg', 'PACT Apparel', 35)")

# Create flexible query parameters.
def make_parameters_flexible(query_input):

    # Create a parameter to search our database for similar products.
    sql_query_parameter = "%" + query_input + "%"

    # Send query parameter.
    return sql_query_parameter

# Populate the category database (if deleted)
def populate_categories_in_database():
    row_ids = db.execute("""
                        INSERT INTO 'categories'
                        ('category') VALUES
                        ('Appliances')
                        , ('Apps & Games')
                        , ('Arts, Crafts & Sewing')
                        , ('Automotive Parts & Accessories')
                        , ('Baby')
                        , ('Beauty & Personal Care')
                        , ('Books')
                        , ('Cell Phones & Accessories')
                        , ('Clothing, Shoes & Jewelry')
                        , ('Collectibles & Fine Art')
                        , ('Computers')
                        , ('Courses')
                        , ('Credit and Payment Cards')
                        , ('Digital Music')
                        , ('Electronics')
                        , ('Garden & Outdoor')
                        , ('Gift Cards')
                        , ('Grocery & Gourmet Food')
                        , ('Handmade')
                        , ('Health, Household & Baby Care')
                        , ('Home & Business Services')
                        , ('Home & Kitchen')
                        , ('Industrial & Scientific')
                        , ('Luggage & Travel Gear')
                        , ('Luxury Beauty')
                        , ('Magazine Subscriptions')
                        , ('Movies & TV')
                        , ('Musical Instruments')
                        , ('Office Products')
                        , ('Pet Supplies')
                        , ('Software')
                        , ('Sports & Outdoors')
                        , ('Tools & Home Improvement')
                        , ('Toys & Games')
                        , ('Vehicles')
                        , ('Video Games')
                        , ('Wine')
                        """)

    return row_ids
