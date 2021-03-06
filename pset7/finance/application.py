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

    # CS50 Spec (DONE)
    # Complete the implementation of index
    # in such a way that it displays an HTML table summarizing,
    # for the user currently logged in,
    # which stocks the user owns,
    # the numbers of shares owned,
    # the current price of each stock,
    # the total value of each holding
    # (i.e., shares times price).

    # Also display the user’s current cash balance along with a grand total
    # (i.e., stocks' total value plus cash).


    count_stock = 0

    session.get("user_id")

    try:
        # store users assets in a list of dict objects
        # link to "execute" documentation
            # https://docs.cs50.net/problems/finance/finance.html#hints
        user_assets_history = db.execute("SELECT symbol, SUM(shares) shares, purchase_price FROM portfolio GROUP BY symbol HAVING user_id = :user_id ORDER BY symbol ASC", user_id=session.get("user_id"))
    except RuntimeError:
        # if error with db.execute, apologize to user
        return apology("Error: We'll fix this. Please try again shortly.")


    # create a list to only store user's current stock holdings
    user_assets = []

    # create integer counter for the upcoming loop
    ctr = 0

    # for each stock part of the users portfolio (or former portfolio)
    for stock in user_assets_history:

        # if the user still owns the stock, then keep track of it
        if user_assets_history[ctr]["shares"] > 0:

            # store this stock in our current stock holding list
            user_assets.append(user_assets_history[ctr])

        # increase current stock counter by 1
        ctr += 1
        # ignore stocks in our portfolio with negative shares


    # count the number of stocks the user has
    # use to create the rows in the homepage table
    # see index.html for more
    for rows in user_assets:
        count_stock += 1;


    # get stock's current quote
    # create an empty list to store our stock quotes (keep in scope)
    ownership_quote = []

    # create empty list to store formated stock prices only
    current_price = []

    # create empty stock ownership list to keep in scope for render
    stock_ownership = []

    # save total assets owned by the user
    # will render in index.html
    total_assets = 0.0

    # loop through the owners stocks
    for stock in range(count_stock):

        # # get the symbol of the current stock
        current_symbol = user_assets[stock]["symbol"]

        # get the up-to-date stock quotes
        # store quotes in a list of dict objects
        ownership_quote.append(lookup(current_symbol))

        # store the formatted price into a variable to render in index.html
        current_price.append(usd(ownership_quote[stock]["price"]))

        # calculate total ownership value in the current stock
        # apply usd format
        stock_ownership.append( usd(user_assets[stock]["shares"] * ownership_quote[stock]["price"]) )

        # calculate total ownership value across all stocks
        total_assets = total_assets + (user_assets[stock]["shares"] * ownership_quote[stock]["price"])


    # Get users current cash
    cash_holdings = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session.get("user_id") )


    # render the index template with appropriate variables, index.html
    return render_template("index.html",  current_price = current_price, ownership_quote = ownership_quote, user_assets = user_assets , stock_ownership = stock_ownership, total_assets = usd(total_assets + cash_holdings[0]["cash"]), count_stock = count_stock, cash_holdings = usd(cash_holdings[0]["cash"]) )

    # display homepage
    return render_template("index.html")

    # if something broke
    return apology("TODO")

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock."""
    # keep user logged in
    session.get("user_id")

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # CS50 Spec (DONE)
        # Require that a user input a stock’s symbol.
        # Render an apology if the input is blank.
        # Require that a user input a number of shares.
        # Render an apology if the input is not a positive integer

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
        buy = lookup(request.form.get("symbol"))

        # Render an apology if the symbol does not exist (as per the return value of lookup).
        if (buy == None):
            # otherwise, return an apology
            return apology("Please provide a valid stock symbol")

        try:
            # check whether money exist
            money_available = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id=session.get("user_id") )
        except RuntimeError:
            # if error with db.execute, apologize to user
            return apology("Error: We'll fix this. Please try again shortly.")

        # CS50 Spec (DONE)
        # Render an apology, without completing a purchase,
        # if the user cannot afford the number of shares at the current price.

        # if they do not have enough money to purchase the requested shares of stock
        if money_available[0]["cash"] < ( buy["price"] * float(request.form.get("shares") ) ):
            # apologize
            return apology("Looks like do not have enough money")

        # Otherwise, subtract the cost of that many shares from their account
        money_available[0]["cash"] = money_available[0]["cash"] - ( buy["price"] * float(request.form.get("shares")) )

        try:
            # Update users accounts to reflect new assets
            subtract_stock_cost = db.execute("UPDATE users SET cash = :money WHERE id = :user_id", user_id=session.get("user_id"), money=money_available[0]["cash"])
        except RuntimeError:
            # if error with db.execute, apologize to user
            return apology("Error: We'll fix this. Please try again shortly.")

        try:
            # Add the requested stock shares to our user's portfolio
            # create row in db with symbol, shares, and price of stock purchased by user
            row = db.execute("INSERT INTO 'portfolio' ('id','user_id','symbol','shares','purchase_price') VALUES (NULL, :user_id, :stock, :shares, :purchase_price)", user_id=session.get("user_id"), stock=buy["symbol"], shares=request.form.get("shares"), purchase_price= usd_db(buy["price"]) )
        except RuntimeError:
            # if error with db.execute, apologize to user
            return apology("Error: We'll fix this. Please try again shortly.")

        # render confirmation of stock purchase on screen for user (TODO)


    # otherwise return the buy page
    return render_template("buy.html")


    return apology("TODO")

@app.route("/history")
@login_required
def history():
    """Show history of transactions."""

    # CS50 Spec
    # Complete the implementation of history in such a way that it displays
    # an HTML table summarizing all of a user’s transactions ever,
    # listing row by row each and every buy and every sell.
    # For each row, make clear whether a stock was bought or sold
    # and include the stock’s symbol,
    # the (purchase or sale) price,
    # the number of shares bought or sold,
    # and the date and time at which the transaction occurred.


    count_stock = 0

    session.get("user_id")

    try:
        # store users assets in a list of dict objects
        # link to "execute" documentation
            # https://docs.cs50.net/problems/finance/finance.html#hints
        user_assets = db.execute("SELECT symbol, shares, purchase_price, purchase_time FROM portfolio WHERE user_id = :user_id ORDER BY purchase_time DESC", user_id=session.get("user_id"))
    except RuntimeError:
        # if error with db.execute, apologize to user
        return apology("Error: We'll fix this. Please try again shortly.")

    # count the number of stocks the user has
    # use to create the rows in the homepage table
    # see index.html for more
    for rows in user_assets:
        count_stock += 1;


    # render the index template with appropriate variables, index.html
    return render_template("history.html",  user_assets = user_assets, count_stock = count_stock)


    # if something broke
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

        try:
            # query database for username
            rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))
        except RuntimeError:
            # if error with db.execute, apologize to user
            return apology("Error: We'll fix this. Please try again shortly.")

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


@app.route("/password", methods=["GET", "POST"])
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

        try:
            # create row in database for username
            rows = db.execute("INSERT INTO 'users' ('id','username','hash') VALUES (NULL, :username, :password)", username=request.form.get("username"), password=pwd_context.hash(request.form.get("password")))
            if rows== None:
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


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock."""

    # CS50 Spec (DONE)
    # Complete the implementation of sell in such a way that
    # it enables a user to sell shares of a stock (that he or she owns).
    # Check for and render apologies for any possible errors.



    # keep user logged in
    session.get("user_id")

    try:
        # store the users stocks in a list of dict objects
        # in alphabetic order
        user_stocks_history = db.execute("SELECT symbol, SUM(shares) shares FROM portfolio GROUP BY symbol HAVING user_id  = :user_id ORDER BY symbol ASC", user_id = session.get("user_id") )

        # DUPLICATIVE <-- delete this after tests
        # # find out how many rows were returned by the GROUP BY query
        # # will be used to set range of for loop later on
        # count_stocks = db.execute("SELECT symbol, SUM(shares) shares FROM portfolio GROUP BY symbol HAVING user_id = :user_id", user_id = session.get("user_id") )

    except RuntimeError:
        # if error with db.execute
        # render an apology on screen
        return apology("Error: We'll fix this. Please try again shortly.")



    # Clear out stocks with 0 or fewer shares (lines 446 - 465)

    # create a list to only store user's current stock holdings
    user_stocks = []

    # create integer counter for the upcoming loop
    ctr = 0

    # for each stock part of the users portfolio (or former portfolio)
    for stock in user_stocks_history:

        # if the user still owns the stock, then keep track of it
        if user_stocks_history[ctr]["shares"] > 0:

            # store this stock in our current stock holding list
            user_stocks.append(user_stocks_history[ctr])

        # increase current stock counter by 1
        ctr += 1

        # ignore stocks in our portfolio with negative shares


    # get how many unique stocks a user owns
    unique_stock_count = 0
    # for each row returned by the db query, add 1 to my stock cound
    # used to generate the table in sell.html
    for row in user_stocks:
        unique_stock_count += 1

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # if no stock was specified
        if not request.form.get("symbol"):
            # tell user to choose a stock symbol
            return apology("must choose ticker symbol to sell")
        # if shares were not specified
        elif not request.form.get("shares"):
            # tell user to specify shares
            return apology("please specify shares to sell")
        # if the user selects less than a share to sell
        elif int(request.form.get("shares")) < 1:
            # tell the user to select more than a share to sell
            return apology("please select one or more shares to sell")
        # if user request a fractional shares
        elif float(request.form.get("shares")) % 1 != 0:
            return apology("fractional shares not available")


        try:
            # Make sure the user has enough stock to sell
            shares_of_selected_stock = db.execute("SELECT SUM(shares) shares FROM portfolio WHERE user_id = :user_id AND symbol = :symbol", user_id = session.get("user_id"), symbol = request.form.get("symbol") )

            # Check whether the user has shares to sell
            if (shares_of_selected_stock[0]["shares"] <= int(request.form.get("shares")) ):
                return apology("Not enough shares to sell.")

        except RuntimeError:
            # If the database query failed, apologize to the user.
            return apology("Error: We'll fix this. Please try again shortly.")

        # lookup share value at time of sale
        sales_quote = lookup(request.form.get("symbol"))

        # if invalid symbol
        if (sales_quote == None) :
            return apology("Requested stock not publicly traded.")

        # determine price
        final_sale_price = sales_quote["price"]




        try:
            # Insert a row with to track the sale of a user's stock ownership
            log_of_sale = db.execute("INSERT INTO 'portfolio' ('id','user_id','symbol','shares','purchase_price') VALUES (NULL, :user_id, :symbol, :shares, :sale_price)", user_id=session.get("user_id"), symbol=request.form.get("symbol"), shares=(int(request.form.get("shares")) * -1), sale_price= usd_db(final_sale_price) )

        except RuntimeError:
            # If the database query failed, apologize to the user.
            return apology("Error: We'll fix this. Please try again shortly.")


        # calculate cash received in total (all shares sold)
        total_sale_value = float(final_sale_price) * int(request.form.get("shares"))

        try:
            # find cash the user already holds
            user_cash = db.execute("SELECT cash FROM users WHERE id = :user_id", user_id = session.get("user_id"))

            cash_after_sale = user_cash[0]["cash"] + total_sale_value

            # give the user his or her cash from purchase
            give_cash = db.execute("UPDATE users SET cash = :cash_after_sale WHERE id = :user_id ", user_id = session.get("user_id"), cash_after_sale = cash_after_sale )

        except RuntimeError:
            # If the database query failed, apologize to the user.
            return apology("Error: We'll fix this. Please try again shortly.")

        #Render sold template
        return render_template("sold.html", shares_sold = request.form.get("shares"), stock_sold = request.form.get("symbol"), total_sale_value = total_sale_value)

    # Render sell html on page
    return render_template("sell.html", user_stocks = user_stocks, unique_stock_count = unique_stock_count)

    # If all else fails
    return apology("TODO")

