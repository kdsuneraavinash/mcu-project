from flask import Flask
from flask import request
from capparselib.parsers import CAPParser
from flask import render_template

from db import database, entry

app = Flask(__name__)
database.init_app(app)


@app.route('/', methods=["POST"])
def get_update():
    alerts = CAPParser(request.data.decode('utf-8')).as_dict()
    alert = alerts[0]
    params = {}
    for param in alert['cap_info'][0]['cap_parameter']:
        name = param['valueName']
        value = param['value']
        params[name] = value
    entry.save_entry(alert, params)
    return "200 - ACK"


@app.route('/', methods=["GET"])
def view():
    entries = entry.get_all_entries()
    return render_template('index.html', entries=entries)


if __name__ == '__main__':
    app.run()
