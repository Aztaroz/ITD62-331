from flask import Flask, jsonify, render_template, request
import requests
import paho.mqtt.client as mqtt
host = "192.168.240.37"
port = "1883"
client = mqtt.Client()



app = Flask(__name__)
js_server = 'http://192.168.240.37:3000'
@app.route("/")
def home():
    return render_template("index.html")

@app.route("/thingspeak/aqi")
def get_aqi():
    headers = {'Accept': 'application/json'}
    r = requests.get("https://thingspeak.com/channels/1541265/field/3.json?results=6", headers=headers)
    return r.json()

@app.route("/thingspeak/dewpoint")
def get_dewpoint():
    headers = {'Accept': 'application/json'}
    r = requests.get("https://thingspeak.com/channels/1285636/field/3.json?results=6", headers=headers)
    return r.json()

@app.route("/report")
def report():
    headers = {'Accept': 'application/json'}
    r = requests.get(js_server+'/sensors?_sort=id&_order=desc&_limit=1', headers=headers)
    return r.json()

@app.route("/led")
def toggle_led():
    client.connect(host)
    status = request.args.get('status')
    print(status)
    if status == '1':
        client.publish("led", status)
    elif status == '0':
        client.publish("led", status)
    return jsonify(status=200)


if __name__ == "__main__":
    app.run(debug=True)