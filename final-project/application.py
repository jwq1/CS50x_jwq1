# Final Project | Application | (jwq1)
import os
import re
from cs50 import SQL

from flask import Flask, jsonify, render_template, request, url_for, flash, session
from flask_session import Session
from flask_jsglue import JSGlue

from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# Configure application.
app = Flask(__name__)
JSGlue(app)

# Ensure responses aren't cached.
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# Configure session to use filesystem (instead of signed cookies).
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database.
db = SQL("sqlite:///final.db")


@app.route("/")
@login_required
def index():
    """Homepage"""

    # Keep the user logged in
    user_id = session.get("user_id")

    # Get the username
    user_info = db.execute(
            "SELECT username FROM users WHERE id = :user_id"
            + " LIMIT 1",
            user_id=user_id)

    # Ensure user was found
    if user_info == None:
        return apology("You were not found in our database. Please login.")

    # Get username of the current user
    username = user_info[0]['username']

    # Get a list of categories a user can choose from
    category_list = all_categories()

    # Get number of categories
    number_of_categories = len(category_list)

    # Get the most recently added products. Limit to 2.
    recent_products = db.execute("""
            SELECT product_name, image
            FROM products
            ORDER BY id DESC
            LIMIT 2""")

    # Ensure recent products were found.
    if recent_products == None:
        return apology("No recent products")

    # Get product count
    product_count = len(recent_products)

    # Render the home page with the most recent products.
    return render_template(
            "index.html",
            recent_products=recent_products,
            product_count=product_count,
            this_username=username,
            category_list=category_list,
            number_of_categories=number_of_categories)


@app.route("/category")
@login_required
def category():
    """Page of categories to choose from"""

    # keep user logged in
    session.get("user_id")

    # Get a list of categories a user can choose from
    category_list = all_categories()

    # Get number of categories
    number_of_categories = len(category_list)

    # Render category page
    return render_template(
            "category.html",
            category_list=category_list,
            number_of_categories=number_of_categories)

    # TODO
    return apology("TODO")


@app.route("/product")
# @login_required
def product():
    """View an individual product"""

    # Keep the user logged in.
    user_id = session.get("user_id")

    # Request a product from the user.
    product_request = request.args.get("product")

    # Ensure the user asked for a product.
    if not product_request:
        return apology("Please let us know which product you are looking for")
    elif product_request == None:
        return apology("Please let us know which product you are looking for")


    # Find our record of this product
    product_info = find_product(product_request)

    # If no product was found, then apologize.
    if not product_info or product_info == None:
        return apology("Sorry, we don't have information for that product")

    # Assign local variables
    product_name = product_info[0]["product_name"]
    image = product_info[0]["image"]
    link = product_info[0]["link"]
    description = product_info[0]["description"]
    brand = product_info[0]["brand"]
    price = usd(product_info[0]["price"])

    #Render the product page.
    return render_template("product.html",
                            product_name=product_name,
                            image=image,
                            link=link,
                            description=description,
                            brand=brand,
                            price=price)


@app.route("/new", methods=["GET", "POST"])
def new():
    """Add new product"""

    # remember user
    session.get("user_id")

    # If user submits data for a new product, insert it into our table
    if request.method == "POST":

        # Ensure form was submitted
        if not request.form.get("product_name"):
            return apology("No product name")
        elif not request.form.get("link"):
            return apology("No link")
        elif not request.form.get("description"):
            return apology("No description")
        elif not request.form.get("image"):
            return apology("No image")
        elif not request.form.get("brand"):
            return apology("No brand")
        elif not request.form.get("price"):
            return apology("No price")


        # Assign local variables
        product_name=request.form.get("product_name")
        link=request.form.get("link")
        description=request.form.get("description")
        image=request.form.get("image")
        brand=request.form.get("brand")
        price=request.form.get("price")


        # Save this product to the database.
        def save_product():

            product_exists = db.execute("""
                    SELECT product_name FROM products
                    WHERE product_name = :product_name""",
                    product_name=product_name)

            # If the product already exists, apologize to the user.
            if len(product_exists) > 0:
                return apology("Product with this name already exists.")

            try:
                # Save the new product in our products table.
                new_product_row = db.execute("""
                        INSERT INTO products
                        (id, category_id, product_name,
                        link, description, image, brand,
                        price)
                        VALUES (NULL, 1, :product_name,
                        :link, :description, :image,
                        :brand, :price)""",
                        product_name=product_name,
                        link=link,
                        description=description,
                        image=image,
                        brand=brand,
                        price=price)

            except RuntimeError:
                # If db.execute raises an error, return a help message.
                return apology("Oops! We'll fix this. Please try again later.")

            # If the product was not saved to the table, render an apology.
            if new_product_row == None:
                return apology("Something went wrong. Please try again later.")


        # TODO: Append these parameters to the end of
        # Actual: ide50-jwq11.cs50.io:8080/product
        # Expected: ide50-jwq11.cs50.io:8080/product?product=crew sweatshirt
        # Put input, in the form of a URL query parameter.
        def make_parameter(query_input):
            # Format the parameters to serve as query.
            parameters = (
                # Make "product=[parameter]" format
                # to append after ? in URL
                "product=" + query_input
            )

            # Return the parameters in a url query format.
            return parameters


        # Call the save_product method to save our products
        save_product()

        # TODO: Redirect to product page of the newly created product.
        # Placeholder: Redirect to the index page
        return redirect(url_for("index"))

    # Otherwise, render the input form for a new product.
    # The user most likely arrived to the page via GET.
    else:
        return render_template("new.html")



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()


    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure a username was submitted
        if not request.form.get("username"):
            return apology("must provide username or email")

        # Ensure a password was submitted.
        elif not request.form.get("password"):
            return apology("must provide password")

        # Set local variables.
        username = request.form.get("username")
        password = request.form.get("password")

        try:
            # Query database for username.
            rows = db.execute("""
                    SELECT * FROM users
                    WHERE username = :username
                    OR email = :username""",
                    username=request.form.get("username") )

        except RuntimeError:
            # If error with db.execute, apologize to user.
            return apology("Error: We'll fix this. Please try again shortly.")

        # Ensure username exists and password is correct.
        if (len(rows) != 1
            or not pwd_context.verify(request.form.get("password"),
            rows[0]["hash"]) ):
            # Offer prescriptive error message to the user.
            return apology("invalid username/email or password")

        # Remember which user logged in.
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page.
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change users password"""

    # Remember which user we are changing the password for.
    user_id = session.get("user_id")

    # retrieve the users current password
    users_current_password = db.execute("""
            SELECT hash FROM users
            WHERE id = :user_id""",
            user_id = session.get("user_id") )

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure the user's current password was submitted.
        if not request.form.get("current_password"):
            return apology("must provide current password")
        # Ensure the password is correct.
        elif not pwd_context.verify(request.form.get("current_password"),
                                    users_current_password[0]["hash"]):
            return apology("invalid current password")
        # Ensure a new password was submitted.
        elif not request.form.get("new_password"):
            return apology("must provide new password")
        # Ensure a confirmation of the new password was submitted.
        elif not request.form.get("confirm_new_password"):
            return apology("Please confirm your new password")
        # Confirm the new password.
        else:
            # Set variables
            new_password = request.form.get("new_password")
            confirmation = request.form.get("confirm_new_password")
            # Ensure both the new password and the confirmation match.
            if (new_password != confirmation):
                return apology("The new passwords did not match")
            # If all is well, then encrypt the new password.
            else:
                password_hash = pwd_context.hash(request.form.get("new_password"))

        try:
            # Update the password in the database.
            updated_row = db.execute("""
                UPDATE users SET hash = :password_hash
                WHERE id = :user_id""",
                user_id=user_id,
                password_hash=password_hash)

            # If the new password is the same as the current, then apologize.
            if updated_row == None:
                return apology("New password has to be different than current")

        except RuntimeError:
            # If an error occurred with db.execute, apologize to user.
            return apology("500 Error: We'll fix this. Please try again shortly.")

        # Redirect user to login page.
        return redirect(url_for("index"))

    # Otherwise, if the user reached route via GET,
    # (as by clicking a link or via redirect)
    # then display the reset password inputs.
    else:
        return render_template("resetPassword.html")


@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user."""

    # Forget any user_id.
    session.clear()

    # If the user reached route via POST (as by submitting a form via POST).
    if request.method == "POST":

        # Ensure a username was submitted.
        if not request.form.get("username"):
            return apology("must provide username")

        # Ensure a password was submitted.
        elif not request.form.get("password"):
            return apology("must provide password")

        # Ensure a password_confirmation was submitted.
        elif not request.form.get("password_confirmation"):
            return apology("passwords did not match")

        # Ensure the password matches the confirmation.
        elif ( request.form.get("password")
                != request.form.get("password_confirmation") ):
            return apology("passwords did not match")

        # Set local variables
        username=request.form.get("username")
        password=pwd_context.hash(request.form.get("password"))
        email=request.form.get("email")

        try:
            # Create a row in database for the new user.
            rows = db.execute("""
                INSERT INTO users (email, username, hash)
                VALUES (:email, :username, :password)""",
                username=username, password=password, email=email)
            # If the username already exists, then help the user.
            if rows == None:
                return apology("username already exists")
        except RuntimeError:
            # If there was an error with db.execute, apologize to user.
            return apology("Error: We'll fix this. Please try again shortly.")


        # Redirect the user to login page, when they have registered.
        return redirect(url_for("login"))

    # Otherwise, if user reached route via GET
    # (as by clicking a link or via redirect)
    # then render the registeration page.
    else:
        return render_template("register.html")


# Search for products.
@app.route("/search")
def search():
    """Search for products that match query."""

    # Keep the user logged in.
    user_id = session.get("user_id")

    # TODO
    return apology("TODO")


# Search for products in a category requested by the user.
@app.route("/search_category")
def search_category():
    """Search for products that match query."""

    # Get which category the user requested.
    users_selected_category = request.args.get("category")

    # Search database for products in a given category.
    products_in_category = search_by_category(users_selected_category)

    # Check whether any products were found
    if products_in_category == "not a category":
        return apology("Unfortunately, we don't have a category"
            + users_selected_category)
    elif products_in_category == "no products found":
        return apology(
                "Unfortunately, we don't have products in the "
                + users_selected_category
                + " category yet. "
                + "Please consider adding any you think should be here.")

    # Save the number of products in the category.
    number_of_products = len(products_in_category)

    # Render a page with all the products found.
    return render_template("category-search.html",
        products_in_category=products_in_category,
        number_of_products=number_of_products,
        users_selected_category=users_selected_category)


# TODO: re-write update function
@app.route("/update")
def update():
    """Update product search page and/or the specific product page when new content added"""

    # TODO: ensure parameters are present

    # TODO: ensure parameters are in the correct format

    # TODO: Find the products which match the search.

    # TODO: Render the list of products

    # TODO
    return apology("TODO Update")
