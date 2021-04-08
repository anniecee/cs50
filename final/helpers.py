import os
import requests
import urllib.parse

from flask import redirect, render_template, request, session
from functools import wraps
from datetime import date, timedelta


def apology(message, code=400):
    """Render message as an apology to user."""
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

    http://flask.pocoo.org/docs/1.0/patterns/viewdecorators/
    """
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function


def get_rate(input_currency, output_currency):
    """Look up latest exchange rate for currencies."""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        query = f"{input_currency}_{output_currency}"
        response = requests.get(f"https://free.currconv.com/api/v7/convert?q={query}&compact=ultra&apiKey={api_key}")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        exrate = response.json()
        return exrate[query]

    except (KeyError, TypeError, ValueError):
        return None


def his_rate(input_currency, output_currency):
    """Look up historical exchange rate of currencies 1 day ago"""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        query = f"{input_currency}_{output_currency}"
        today = date.today()
        yesterday = today - timedelta(days = 1)
        response = requests.get(f"https://free.currconv.com/api/v7/convert?q={query}&compact=ultra&date={yesterday}&apiKey={api_key}")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        exrate = response.json()
        # Return the rate of yesterday
        return exrate[query][f'{yesterday}']

    except (KeyError, TypeError, ValueError):
        return None

def full_list():
    """Extract full list of Country ID"""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        response = requests.get(f"https://free.currconv.com/api/v7/countries?apiKey=b17eb8d8ed387d9b6b79")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        info = response.json()
        #Create list to save data of all Country ID
        countryid_list = list(info['results'].keys())

        return countryid_list

    except (KeyError, TypeError, ValueError):
        return None

def lookup(country_id):
    """Look up info for input currency symbol"""

    # Contact API
    try:
        api_key = os.environ.get("API_KEY")
        response = requests.get(f"https://free.currconv.com/api/v7/countries?apiKey=b17eb8d8ed387d9b6b79")
        response.raise_for_status()
    except requests.RequestException:
        return None

    # Parse response
    try:
        info = response.json()
        # For loop to search for each currency in the results
        for i in info['results']:
            # If the currency is found, return currency's information in a list of dict
            if i == country_id:
                return {
                    "country": info['results'][i]['name'],
                    "id": info['results'][i]['currencyId'],
                    "name": info['results'][i]['currencyName'],
                    "symbol": info['results'][i]['currencySymbol']
                }
    except (KeyError, TypeError, ValueError):
        return None

def format_cur(value, cur_id, cur_symbol):
    """Format value in right currency format"""
    return f"{cur_symbol}{value:,.2f} {cur_id}"
