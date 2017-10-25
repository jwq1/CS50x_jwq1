from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, url_for
from flask_session import Session
from passlib.apps import custom_app_context as pwd_context
from tempfile import mkdtemp

from helpers import *

# configure application
app = Flask(__name__)

# ensure responses aren't cached
if app.config["DEBUG"]:
    @app.after_request
    def after_request(response):
        response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
        response.headers["Expires"] = 0
        response.headers["Pragma"] = "no-cache"
        return response

# custom filter
app.jinja_env.filters["usd"] = usd

# configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

@app.route("/")
@login_required
def index():
    return apology("TODO")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    # keep user logged in
    session.get("user_id")

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # if no stock was specified
        if not request.form.get("symbol"):
            return apology("must provide stock ticker symbol")
        # if stock symbol is not a publicly traded company
        elif lookup(request.form.get("symbol")) == None:
            return apology("Requested stock not publicly traded")
        # if no shares requested
        elif not request.form.get("shares"):
            return apology("please specify # of shares")
        # if user requests less than 1 share
        elif float(request.form.get("shares")) < 1:
            return apology("please ask for 1 or more whole shares")
        # if user request a fractional shares
        elif float(request.form.get("shares")) % 1 != 0:
            return apology("fractional shares not available")

        # store dictionary of values into name, price, and symbol for access in index.html
        quote = lookup(request.form.get("symbol"))

        # create row in database for username
        row = db.execute("INSERT INTO 'portfolio' ('id','user_id','stock','shares','purchase_price') VALUES (NULL, :user_id, :stock, :shares, :purchase_price)", user_id=session.get("user_id"), stock=quote["symbol"], shares=request.form.get("shares"), purchase_price=quote["price"]  )

        # render stock purchase on screen for user (TODO)


    # otherwise return the buy page
    return render_template("buy.html")


    return apology("TODO")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""
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
            return apology("must provide username")

        # ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password")

        # query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # ensure username exists and password is correct
        if len(rows) != 1 or not pwd_context.verify(request.form.get("password"), rows[0]["hash"]):
            return apology("invalid username and/or password")

        # remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to home page
        return redirect(url_for("index"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out."""

    # forget any user_id
    session.clear()

    # redirect user to login form
    return redirect(url_for("login"))

@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # keep user logged in
    session.get("user_id")

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure stock ticker symbol was submitted
        if not request.form.get("stock_ticker"):
            return apology("must provide stock ticker symbol")

        # (TODO) Return error if stock ticker is invalid (i.e. if lookup == None)

        # store dictionary of values into name, price, and symbol for access in quoted.html
        quote = lookup(request.form.get("stock_ticker"))

        # if symbol is invalid, return error
        if quote == None:
            return apology("invalid symbol")

        # render the name, price, and symbol of the stock in the template, quoted.html
        return render_template("quoted.html", stock_name=quote["name"], stock_price = quote["price"], stock_symbol = quote["symbol"])

    # remember which user has logged in


    return render_template("quote.html")
    return apology("TODO")

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

        # create row in database for username
        rows = db.execute("INSERT INTO 'users' ('id','username','hash') VALUES (NULL, :username, :password)", username=request.form.get("username"), password=pwd_context.hash(request.form.get("password")))

        if rows== None:
            return apology("username already exists")

        # redirect user to login page
        return redirect(url_for("login"))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")



    return apology("TODO")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""
    return apology("TODO")
