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

# configure application
app = Flask(__name__)
JSGlue(app)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///final.db")

# users table
# CREATE TABLE users (id INTEGER PRIMARY KEY NOT NULL, username TEXT UNIQUE NOT NULL, email TEXT UNIQUE NOT NULL, hash TEXT NOT NULL, first TEXT, last TEXT);

@app.route("/")
@login_required
def index():

    # keep user logged in
    session.get("user_id")

    return apology("TODO")


@app.route("/categories")
@login_required
def categories():

    # keep user logged in
    session.get("user_id")

    return apology("TODO")

@app.route("/product")
# @login_required
def product():

    # keep user logged in
    session.get("user_id")

    # get name of product
    product = "%" + request.args.get("product") + "%"

    try:
        #Get product from the database
        product_info = db.execute("SELECT * FROM products WHERE product_name LIKE :product", product = product)
        # Check whether products were found
        product_check = product_info[0]

    except RuntimeError:
        # If problem with db.execute
        return apology("Error: We'll fix this. Please try again shortly.")

    except IndexError:
        # If no products were found
        return apology("No products named " + request.args.get("product"))

    #Send data to product template
    return render_template("product.html", product_name = product_info[0]["product_name"], image = product_info[0]["image"], link = product_info[0]["link"], description = product_info[0]["description"], brand = product_info[0]["brand"], price = usd(product_info[0]["price"]))
    return apology("TODO")



@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in."""

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username or email")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        try:
            # query database for username
            rows = db.execute("SELECT * FROM users WHERE username = :username OR email = :username", username=request.form.get("username"))
        except RuntimeError:
            # if error with db.execute, apologize to user
            return apology("Error: We'll fix this. Please try again shortly.")

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username/email or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/password", methods=["GET", "POST"])
@login_required
def password():
    """Change users password"""

    # remember which user we are changing the password for
    session.get("user_id")

    # retrieve the users current password
    users_current_password = db.execute("SELECT hash FROM users WHERE id = :user_id", user_id = session.get("user_id") )

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure current_password was submitted
        if not request.form.get("current_password"):
            return apology("must provide current password")
        # ensure username exists and password is correct
        elif not pwd_context.verify(request.form.get("current_password"), users_current_password[0]["hash"]):
            return apology("invalid current password")
        # ensure new password was submitted
        elif not request.form.get("new_password"):
            return apology("must provide new password")
        # ensure the user confirms the password they want
        elif not request.form.get("confirm_new_password"):
            return apology("Please confirm your new password")
        # ensure new passwords match
        elif request.form.get("new_password") != request.form.get("confirm_new_password"):
            return apology("The new passwords did not match")

        try:
            # update the password in the database
            updated_row = db.execute("UPDATE users SET hash = :new_password WHERE id = :user_id", user_id = session.get("user_id"), new_password = pwd_context.hash(request.form.get("new_password")) )
            if updated_row == None:
                return apology("New password has to be different than current")
        except RuntimeError:
            # if error with db.execute, apologize to user
            return apology("500 Error: We'll fix this. Please try again shortly.")

        # redirect user to login page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
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

    # forget any user_id
    session.clear()

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # ensure password_confirmation was submitted
        elif not request.form.get("password_confirmation"):
            return apology("passwords did not match")

        elif request.form.get("password") != request.form.get("password_confirmation"):
            return apology("passwords did not match")

        try:
            # create row in database for username
            rows = db.execute("INSERT INTO users (email, username, hash) VALUES (:email, :username, :password)", username=request.form.get("username"), password=pwd_context.hash(request.form.get("password")), email=request.form.get("email"))
            if rows == None:
                return apology("username already exists")
        except RuntimeError:
            # if error with db.execute, apologize to user
            return apology("Error: We'll fix this. Please try again shortly.")


        # redirect user to login page
        return redirect(url_for("login"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

    return apology("TODO")


# TODO: re-write search function to search for products
@app.route("/search")
def search():
    """Search for products that match query."""

    # TODO

    # get name of place (postal code or city/town name accepted)
    q = request.args.get("q") + "%"

    # find matches for the location in search
    product_search = db.execute("SELECT * FROM todo WHERE todo LIKE :q OR todo LIKE :q LIMIT 50", q=q)


    # return JSON array of objects
    return jsonify(product_search)


# TODO: re-write update function
@app.route("/update")
def update():
    """Update product search page and/or the specific product page when new content added"""

    # # ensure parameters are present
    # if not request.args.get("sw"):
    #     raise RuntimeError("missing sw")
    # if not request.args.get("ne"):
    #     raise RuntimeError("missing ne")

    # # ensure parameters are in lat,lng format
    # if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("sw")):
    #     raise RuntimeError("invalid sw")
    # if not re.search("^-?\d+(?:\.\d+)?,-?\d+(?:\.\d+)?$", request.args.get("ne")):
    #     raise RuntimeError("invalid ne")

    # # explode southwest corner into two variables
    # (sw_lat, sw_lng) = [float(s) for s in request.args.get("sw").split(",")]

    # # explode northeast corner into two variables
    # (ne_lat, ne_lng) = [float(s) for s in request.args.get("ne").split(",")]

    # # find 10 cities within view, pseudorandomly chosen if more within view
    # if (sw_lng <= ne_lng):

    #     # TODO: Update query
    #     # doesn't cross the antimeridian
    #     rows = db.execute("""SELECT * FROM places
    #         WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude AND longitude <= :ne_lng)
    #         GROUP BY country_code, place_name, admin_code1
    #         ORDER BY RANDOM()
    #         LIMIT 10""",
    #         sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    # else:

    #     # TODO: Update query
    #     # crosses the antimeridian
    #     rows = db.execute("""SELECT * FROM places
    #         WHERE :sw_lat <= latitude AND latitude <= :ne_lat AND (:sw_lng <= longitude OR longitude <= :ne_lng)
    #         GROUP BY country_code, place_name, admin_code1
    #         ORDER BY RANDOM()
    #         LIMIT 10""",
    #         sw_lat=sw_lat, ne_lat=ne_lat, sw_lng=sw_lng, ne_lng=ne_lng)

    # # output places as JSON
    # return jsonify(rows)
