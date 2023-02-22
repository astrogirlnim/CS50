import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session, jsonify
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

from datetime import datetime  # Import date and tiem

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Update stock information
    stocks = db.execute("SELECT symbol, total_shares FROM Holdings WHERE user_id = ?", session["user_id"])

    # Portfolio sum total
    sum_total = 0
    for stock in stocks:
        quote = lookup(stock["symbol"])
        investment = quote["price"]*stock["total_shares"]
        sum_total += investment

        # Update portfolio
        db.execute("UPDATE Holdings SET current_price = ?, stock_name = ? WHERE user_id = ? AND symbol = ?",
                   quote["price"], quote["name"], session["user_id"], stock["symbol"])
        db.execute("UPDATE Holdings SET new_total = ? WHERE user_id = ? AND symbol = ?",
                   investment, session["user_id"], stock["symbol"])

    # Update balance
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash[0]['cash']
    sum_total += cash

    summary = db.execute("SELECT * FROM Holdings WHERE user_id=?", session["user_id"])

    return render_template("index.html", summary=summary, cash=cash, balance=sum_total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method == "POST":

        # Verify symbol is submitted
        if not request.form.get("symbol"):
            return apology('Must input symbol', 400)

        # Verify share number is submitted
        elif not request.form.get("shares"):
            return apology('Must select a number of stocks', 400)

        # Retrieve information and validate
        quote = lookup(request.form.get("symbol"))
        shares = int(request.form.get("shares"))
        if request.form.get("shares").isnumeric() == False:
            return apology('Must input valid symbol and share number.', 400)

        if not quote or shares <= 0:
            return apology('Must input valid symbol and share number.', 400)

        balance = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        balance = float(balance[0]["cash"])

        # Check if suficient funds
        if balance < shares*quote["price"]:
            return apology("Insuficient Funds.", 400)
        else:
            # Log transaction
            new_balance = float(balance - shares*quote["price"])
            db.execute("UPDATE users SET cash = ? WHERE id = ?", new_balance, session["user_id"])
            db.execute("INSERT INTO Transactions (id, symbol, name, shares, price, total, time) VALUES(?,?,?,?,?,?,?)",
                       session["user_id"], quote["symbol"], quote["name"], shares, quote["price"], shares*quote["price"], datetime.now())

            # Get portfolio stocks
            stocks = db.execute("SELECT symbol FROM Holdings WHERE user_id =? AND symbol = ?", session["user_id"], quote["symbol"])

            # Update total stock portfolio
            if not stocks:
                db.execute("INSERT INTO Holdings (user_id, symbol, total_shares) VALUES(?,?,?)",
                           session["user_id"], quote["symbol"], shares)
            else:
                old_shares = db.execute("SELECT total_shares FROM Holdings WHERE user_id =? AND symbol = ?",
                                        session["user_id"], quote["symbol"])
                new_shares = shares+int(old_shares[0]["total_shares"])
                db.execute("UPDATE Holdings SET total_shares = ? WHERE user_id = ? AND symbol = ?",
                           new_shares, session["user_id"], quote["symbol"])

            return redirect("/")

    else:
        return render_template('buy.html')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    transactions = db.execute("SELECT * FROM Transactions WHERE id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


# Password change: Personal touch!
@app.route("/passwordchange", methods=["GET", "POST"])
def password_change():

    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        new_password = request.form.get("new_password")

        if not name or not password or not new_password:
            return apology("Must input valid username and password.", 400)
        else:
            # Check password and username validity
            rows = db.execute("SELECT * FROM users WHERE username = ?", name)

            if not check_password_hash(rows[0]["hash"], request.form.get("password")) or not rows or name != rows[0]['username']:
                return apology('Incorrect username or password.', 400)

            # Update database
            db.execute("UPDATE users SET hash = ? WHERE username = ?", generate_password_hash(new_password), name)

            return redirect("/")
    else:
        return render_template("passwordchange.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # User accessed via POST
    if request.method == "POST":

        # Ensure quote was submitted
        if not request.form.get("symbol"):
            return apology("Must provide symbol.", 400)

        # Retrieve quote for symbol
        quote = lookup(request.form.get("symbol"))

        # Validate
        if not quote:
            return apology("Must input valid symbol.", 400)
        else:
            return render_template('quoted.html', stock=quote["name"], value=quote["price"])

    else:
        return render_template('quote.html')


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # User reached route via POST
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure confirmation was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide password", 400)

        # Retrieve username and password/confirmation'
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        usernames = db.execute("SELECT username FROM users WHERE username = ?", username)

        # Validate
        if not not usernames:
            return apology('Username already exists.', 400)
        elif password != confirmation:
            return apology('Passwords do not match.', 400)

        # Insert username and password into database
        password_hash = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password_hash)

        # Redirect user to home page
        return redirect("/")

    else:

        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Verify symbol is submitted
        if not request.form.get("symbol"):
            return apology('Must input symbol', 400)

        # Verify share number is submitted
        elif not request.form.get("shares"):
            return apology('Must select a number of stocks', 400)

        stock = request.form.get("symbol")
        quote = lookup(stock)

        # Check if shares is an integer value
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology('Must input valid stock symbol and number.', 400)

        if not stock or not shares or shares <= 0:
            return apology('Must input valid stock symbol and number.', 400)

        current_shares = db.execute("SELECT total_shares FROM Holdings WHERE user_id = ? AND symbol = ?", session["user_id"], stock)
        current_shares = current_shares[0]["total_shares"]

        # Check if suficient stocks
        if shares > current_shares:
            return apology("Insuficient Stocks.", 400)
        else:
            # Log transaction
            new_shares = current_shares - shares
            db.execute("UPDATE Holdings SET total_shares = ? WHERE user_id = ? AND symbol = ?",
                       new_shares, session["user_id"], stock)
            db.execute("INSERT INTO Transactions (id, symbol, name, shares, price, total, time) VALUES(?,?,?,?,?,?,?)",
                       session["user_id"], quote["symbol"], quote["name"], -shares, quote["price"], shares*quote["price"], datetime.now())

            # Update cash
            gain = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
            gain = gain[0]['cash'] + quote["price"]*shares
            db.execute("UPDATE users SET cash = ? WHERE id = ?", gain, session["user_id"])

            # If all stocks drained, remove stock from portfolio:
            if new_shares == 0:
                db.execute("DELETE FROM Holdings WHERE user_id  = ? AND symbol = ?", session["user_id"], stock)

            return redirect("/")
    else:
        return render_template("sell.html")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)