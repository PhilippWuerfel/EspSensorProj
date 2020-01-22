import json
import hmac
import hashlib
import requests

m = hashlib.sha256()
m.update(b"Nobody inspects")
m.update(b" the spammish repetition")
m.digest()
print(m.digest_size)
m.block_size

msg = "{ 'temperature':21.82, 'humidity': 32.31}"
print("message received: ", msg)
msg_json1 = json.dumps(msg)
msg_json2 = json.loads(msg)
    
print("\n Test1:" +str(msg_json1))
print("\n Test2:" +str(msg_json2))

# print(msg_json1['temperature'])
print(msg_json2['temperature'])
# decode the json message from mqtt client
# msg_json = json.loads(msg)
# print("\n Test:" +str(msg_json['temperature']))
body = msg
print("test1")
secret = b"esp8266"  # b'Enter your MongoDB Stitch Webhook password here'
# hash = hmac.new(secret, body.encode("utf-8"), hashlib.sha256)
hashed = hmac.new(secret, body.encode("utf-8"), hashlib.sha256)
print("test2")
url = "https://webhooks.mongodb-stitch.com/api/client/v2.0/app/connecteddevices-fyecb/service/IotReceiveData/incoming_webhook/saveTempHumidData"  # enter your Stitch Web API URL here
header = {"Content-Type": "application/json", "X-Hook-Signature": "sha256=" + hashed.hexdigest()}
print("test3")
myResponse = requests.post(url, headers=header, data=body)
print("test4")
print (myResponse.status_code)
