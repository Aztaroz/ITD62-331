import paho.mqtt.client as mqtt
host = "192.168.240.37"
port = 1883

import requests as req
import json
url = 'http://192.168.240.37:3000'

def on_connect(self, client, userdata, rc):
    print("MQTT Connected.")
    self.subscribe("sensors")

def on_message(client, userdata,msg):
    global received_msg
    
    res = msg.payload.decode("utf-8")
    received_msg = res
    print(received_msg)

    post = req.post(url+'/sensors', json=json.loads(res))
    print(post)


client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect(host, port)
client.loop_forever()
