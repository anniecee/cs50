import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from jinja2 import Template

from helpers import apology, login_required, lookup, full_list, get_rate, his_rate, format_cur

# try another method that will not call every time
def test():
    country_list = full_list()
    cur_list = []
    print(full_list())
    for i in country_list:
        cur_info = lookup(i)
        cur_name = cur_info['name']
        cur_id = cur_info['id']
        cur_display = f"{cur_name} - {cur_id}"
        cur_list.append(cur_display)

    print(cur_list)
    return cur_list

test()