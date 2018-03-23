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
            SELECT id, category FROM categories
            WHERE category LIKE :category_parameter"""
            , category_parameter=(selected_category + "%") )

    # Check whether a category was found.
    if category_row == None:
        return "not a category"
    elif not category_row:
        return "not a category"

    # Save the category id.
    category_id = category_row[0]["id"]

    # Search for products with the same category id.
    product_rows = db.execute("""
            SELECT product_name, image, categories.category
            FROM products
            LEFT JOIN categories ON products.category_id=categories.id
            WHERE products.category_id=:category_id;"""
            , category_id=category_id)

    # Check whether products exist in this category
    if product_rows == None:
        return "no products found"
    elif not product_rows:
        return "no products found"

    return product_rows

# Find our record for this product
def find_product(id_requested):

    # Create a parameter to search our database
    # for any records, which contain the product name.
    product_parameter = "%" + str(id_requested) + "%"

    #Search the database for the requested product.
    product_data = db.execute("""
        SELECT *
        FROM products
        WHERE id
        LIKE :products_id
        LIMIT 30""",
        products_id=product_parameter)


    # Return information about the requested product.
    return product_data


def get_reference(product_with_references):
    """Search for references to product research."""

    # If no name is given, then ask the user for one.
    if not product_with_references:
        return apology("Please specify product")
    elif product_with_references == None:
        return apology("Please specify product")

    # Search for references to a given product
    references_for_product = db.execute("""
            SELECT research.link, title, research.id
            FROM research
            LEFT JOIN products
            ON products.id=research.product_id
            WHERE products.id=:product
            """, product=product_with_references)

    # Save the number of research articles for this products.
    number_of_references = len(references_for_product)

    # Save the titles and links to each reference.
    # Create an empty list to save our ids.
    reference_ids = []
    # Create an empty list to save our titles.
    reference_titles = []
    # Create an empty list to save our links.
    reference_links = []

    # Loop through each title in our list of references
    for reference_article in references_for_product:

        # Save the id.
        reference_ids.append(reference_article["id"])

        # Ensure we have a title.
        if not reference_article["title"]:
            # If there is no title, then use the link.
            reference_titles.append(reference_article["link"])
        # If there is a title, then use the title.
        else:
            # Save the title.
            reference_titles.append(reference_article["title"])

        # Save the link.
        reference_links.append(reference_article["link"])

    return (number_of_references, reference_ids, reference_titles, reference_links)
