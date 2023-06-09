import odroid_wiringpi as wiringpi 
import paho.mqtt.client as mqtt
from time import sleep

#zet pin 2 als een input met pull-up weerstand 
PIN = 2
wiringpi.wiringPiSetup()
wiringpi.pinMode(PIN, wiringpi.INPUT)
wiringpi.pullUpDnControl(PIN, wiringpi.PUD_UP)

# zet MQTT broker address 
broker_address = "broker IP"

# zet de MQTT broker username en password
username = "user"
password = "password"

# maak een MQTT client
client = mqtt.Client()

# zet de MQTT broker username en password
client.username_pw_set(username, password)

# connecteer met de MQTT broker
client.connect(broker_address)

while True: 
	if wiringpi.digitalRead(PIN) == wiringpi.LOW:
	# publiceer het bericht "go" op het topic "robot/start"
	client.publish("robot/start", "go")
	# wacht 1 seconde om te voorkomen dat er meerdere berichten worden verzonden 
	# en laat dit weten door published te printen
	print("published")
	sleep(1)
