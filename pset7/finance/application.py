import os
import sqlite3

from cs50 import SQL, eprint
from datetime import date, datetime, time
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

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

# initialise sqlite3
conn = sqlite3.connect('finance.db')
c = conn.cursor()


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Query database for username
    # rows = db.execute("SELECT * FROM users WHERE username = :username",
    #                   username=request.form.get("username"))

    # load current wallet size
    id = session["user_id"][0]["id"]
    eprint(id)
    wallet = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
    eprint(wallet)
    balance = wallet[0]["cash"]
    eprint(balance)

    # load user's overview
    overview = db.execute("SELECT id, symbol, SUM(num_shares) AS num_shares, SUM(total_price) AS total_price FROM transactions WHERE id = :id GROUP BY id, symbol",
        id=id)

    # obtain length of history for user
    indexO = []
    for i, v in enumerate(overview):
        indexO.append(i)

    # obtain current quotes and net worth
    quotes = []
    net_worth = 0
    for i in indexO:
        quote = lookup(overview[i]["symbol"])
        current_price = quote["price"]
        quotes.append(current_price)
        net_worth = net_worth + (current_price * overview[i]["num_shares"])

    net_worth = net_worth + balance
    eprint(net_worth)

    return render_template("index.html", usd = usd, balance = balance, net_worth = net_worth, indexO = indexO, overview = overview, quotes = quotes)



@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    id = session["user_id"][0]["id"]
    eprint(id)

    # load current wallet size
    wallet = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
    balance = wallet[0]["cash"]

    # obtain users transaction history
    history = db.execute("""
        SELECT date, time, symbol, stock_price, num_shares, total_price, transaction_type, balance
        FROM transactions
        WHERE id=:id AND transaction_type='Purchase'""", id=id)

    # obtain length of history for user
    index = []
    for i, v in enumerate(history):
        index.append(i)

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure symbol was submitted
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        # Ensure quantity of shares was submitted
        elif not request.form.get("shares"):
            return apology("must provide number of shares to purchase", 403)

        # Ensure positive integer
        elif not int(request.form.get("shares")) > 0:
            return apology("please provide positive value", 403)

        # check whether symbol recorded
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Sorry, could not retrieve company symbol", 403)
        else:
            quote = lookup(symbol)

        # get no. stocks
        numShares = request.form.get("shares")
        if not numShares:
            return apology("Sorry, could not retrieve number of shares")
        else:
            totalPrice = float(numShares) * float(quote["price"])

        # Ensure user has enough funds in wallet
        if not balance >= totalPrice:
            return apology("Sorry, insufficient funds")
        else:
            transactionType = "Purchase"
            balance = balance - totalPrice
            today = date.today().isoformat()
            time = datetime.now().time().isoformat()

            # update transactions table
            sql = ("""
                INSERT INTO transactions (id, date, time, symbol, stock_price, num_shares, total_price, transaction_type, balance)
                VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)""")
            values = (id, today, time, symbol, quote["price"], int(numShares), totalPrice, transactionType, balance)

            c.execute(sql, values)
            conn.commit()
            # c.close()
            eprint("Table Updated")
            db.execute("UPDATE users SET cash = :balance WHERE id = :id", balance=balance, id=id)


        return redirect("/buy")

    # when reached via link
    elif request.method == "GET":

        return render_template("buy.html", usd = usd, balance = balance, history = history, index = index)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    id = session["user_id"][0]["id"]
    eprint(id)

    # load current wallet size
    wallet = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
    balance = wallet[0]["cash"]

    # obtain users transaction history
    history = db.execute("""
        SELECT date, time, symbol, stock_price, num_shares, total_price, transaction_type, balance
        FROM transactions
        WHERE id=:id""", id=id)

    #obtain length of history for user
    index = []
    for i, v in enumerate(history):
        index.append(i)

    return render_template("history.html", usd = usd, balance = balance, history = history, index = index )



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
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))
        eprint(rows)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        eprint(rows)
        # Remember which user has logged in
        # session["user_id"] = rows[0]["id"]
        # id = session["user_id"][0]["id"]

        # Remember which user logged in
        session["user_id"] = db.execute("SELECT id FROM users WHERE username = :username",
                          username=request.form.get("username"))
        id = session["user_id"][0]["id"]
        eprint(id)

        eprint(rows)
        eprint(session)
        eprint(id)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


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

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # check whether symbol recorded
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Sorry, could not retrieve quote at this time", 403)
        else:
            quote = lookup(symbol)

        return render_template("quoted.html", usd = usd, name = quote['name'], price = float(quote['price']), symbol = quote['symbol'])

    # when reached via link
    elif request.method == "GET":
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password and confirmation password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password", 400)

        # Ensure confirmation password is the same as password
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("password and confirmation password are different", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username", username=request.form.get("username"))

        # Ensure registered username is new
        if len(rows) == 1:
            return apology("username already exists", 403)

        # Insert new user into database
        newEntry = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hashh)",
                    username=request.form.get("username"), hashh=generate_password_hash(request.form.get("password")))
        eprint("New Entry")

        # if insertion fails
        if not newEntry:
            return apology("could not store new entry in server", 403)

        # Automatically log in new user
        session["user_id"] = db.execute("SELECT id FROM users WHERE username = :username",
                          username=request.form.get("username"))
        id = session["user_id"][0]["id"]
        eprint(id)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    id = session["user_id"][0]["id"]
    eprint(id)

    # load current wallet size
    wallet = db.execute("SELECT cash FROM users WHERE id = :id", id=id)
    balance = wallet[0]["cash"]

    # load user's overview
    overview = db.execute("SELECT id, symbol, SUM(num_shares) AS num_shares, SUM(total_price) AS total_price FROM transactions WHERE id = :id GROUP BY id, symbol",
        id=id)
    eprint(overview)

    # obtain length of history for user
    indexO = []
    for i, v in enumerate(overview):
        indexO.append(i)

    # obtain num of each stock owned
    # stockOwned = overview[]

    # obtain users transaction history
    history = db.execute("""
        SELECT date, time, symbol, stock_price, num_shares, total_price, transaction_type, balance
        FROM transactions
        WHERE id=:id AND transaction_type='Sale'""", id=id)

    #obtain length of history for user
    index = []
    for i, v in enumerate(history):
        index.append(i)

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure quantity of shares was submitted
        if not request.form.get("shares"):
            return apology("must provide number of shares to sell", 403)

        # Ensure positive integer
        if not int(request.form.get("shares")) > 0:
            return apology("please provide positive value", 403)

        # check whether symbol recorded
        symbol = request.form.get("symbol")
        eprint(symbol)
        if not symbol:
            return apology("Sorry, could not retrieve company symbol", 403)

        # get no. stocks to sell
        numShares = int(request.form.get("shares"))
        eprint(numShares)
        if not numShares:
            return apology("Sorry, could not retrieve number of shares")

        # Get current quote
        sharesOwned = db.execute("SELECT SUM(num_shares) AS num_shares FROM transactions WHERE id = :id AND symbol = :symbol GROUP BY id, symbol",
            id=id, symbol=symbol)
        currentQuote = lookup(symbol)["price"]
        eprint(currentQuote)
        eprint(sharesOwned[0]["num_shares"])
        eprint(type(sharesOwned[0]["num_shares"]))

        # Ensure user owns sufficient stocks
        if not sharesOwned[0]["num_shares"] >= numShares:
            return apology("Sorry, you do not own enough of this stock")
        else:
            numShares *= -1
            totalPrice = numShares * currentQuote
            transactionType = "Sale"
            balance = balance - totalPrice
            today = date.today().isoformat()
            time = datetime.now().time().isoformat()

            # update transactions table
            sql = ("""
                INSERT INTO transactions (id, date, time, symbol, stock_price, num_shares, total_price, transaction_type, balance)
                VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?)""")
            values = (id, today, time, symbol, currentQuote, numShares, totalPrice, transactionType, balance)

            c.execute(sql, values)
            conn.commit()
            # c.close()
            eprint("Table Updated")
            db.execute("UPDATE users SET cash = :balance WHERE id = :id", balance=balance, id=id)


        return redirect("/sell")

    # when reached via link
    elif request.method == "GET":

        return render_template("sell.html", usd = usd, balance = balance, indexO = indexO, overview = overview, history = history, index = index )


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
