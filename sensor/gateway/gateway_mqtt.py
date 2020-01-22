import paho.mqtt.client as mqtt
import json
import hmac
import hashlib
import requests
 
def on_connect(client, userdata, flags, rc):
    client.subscribe('/iot/temphumid')

def on_message(client, userdata, msg):
    msg_decode = str(msg.payload.decode("utf-8", "ignore"))
    print("message received type: ", type(msg_decode))
    print("message received: ", msg_decode)
    print("message topic: ", msg.topic)
    
    # only necessary if manipulation on client data is necessary
    print("Converting to Json Object")
    msg_json = json.loads(msg_decode)
    #print(msg_json)
    #print(msg_json["temperature"])      
    
    # decode the json message from mqtt client
    #print("Converting to Json Dump")
    #msg_json_dump = json.dumps(msg_decode)
    #print(msg_json_dump)
    
    # print("\n Test:" +str(msg_json['temperature']))    
    # print(msg_json)  
    
    # body = msg_json_dump
    body = '{ "device":"' + str(msg_json["device"]) + '", "temperature" : "' + str(msg_json["temperature"]) + '", "humidity" : "' + str(msg_json["humidity"]) + '", "sensortime" : "' + str(msg_json["sensortime"]) + '" }'
    
    print("Sending message to cloud")
    print(body)
    
    # Send message to cloud on MongoDB
    secret = b"esp8266" #b'Enter your MongoDB Stitch Webhook password here'
    hashed = hmac.new(secret, body.encode("utf-8"), hashlib.sha256)
    url = "https://webhooks.mongodb-stitch.com/api/client/v2.0/app/connecteddevices-fyecb/service/IotReceiveData/incoming_webhook/saveTempHumidData"  # enter your Stitch Web API URL here
    header={"Content-Type":"application/json","X-Hook-Signature":"sha256=" + hashed.hexdigest()  }
    myResponse = requests.post(url,headers=header, data=body )
    
    print ("\nStatus code: " + str(myResponse.status_code))
    
# uncomment to debug
def on_log(mqttc, obj, level, string):
    print(string)
 
BROKER_ADDRESS = "localhost"
 
client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
# client.on_log = on_log
 
client.connect(BROKER_ADDRESS)
 
print("Connected to MQTT Broker: " + BROKER_ADDRESS)

client.loop_forever()