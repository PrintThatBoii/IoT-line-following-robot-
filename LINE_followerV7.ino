#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ssid";  
const char* password = "passsword";     
const char* mqttServer = "server IP";  
const int mqttPort = 1883;
const char* mqttUser = "username";
const char* mqttPassword = "user password";
const char* clientID = "client_livingroom";  // MQTT client ID

WiFiClient espClient;
PubSubClient client(espClient);

//Ir sensoren
#define left 33
#define center 35
#define right 19

//motor one
#define ENA 13
#define IN1 12
#define IN2 14

//motor two
#define ENB 25
#define IN3 27
#define IN4 26

int Speed = 120;  //snelheid

const int trigPin = 4;
const int echoPin = 18;

//define sound speed in cm/uS
#define SOUND_SPEED 0.034

long duration, cm;

int groen = 21;
int geel = 23;
int rood = 22;

int knop = 32;

int startflag = false;

#include "DHT.h"  // Library nodig voor het uitlezen van de DHT11

#define DHTPIN 15      // signal pin van de DHT11
#define DHTTYPE DHT11  // Aangeven van het type DHT --> 11 of 12

DHT dht(DHTPIN, DHTTYPE);  // DHT basis parameters toevoegen

char temp1[8];

bool stop = false;
int laststop = 0;
int currentpos = 0;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  //set up wifi connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);


  //set a callback function for when data is received from broker
  client.setCallback(callback);


  // connect to broker
  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword)) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // subscribe to topic
  client.subscribe("robot/start");

  pinMode(left, INPUT);
  pinMode(center, INPUT);
  pinMode(right, INPUT);

  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(groen, OUTPUT);
  pinMode(geel, OUTPUT);
  pinMode(rood, OUTPUT);

  pinMode(knop, INPUT_PULLUP);
  
  dht.begin();
}

void loop() {
  client.loop();

  bool leftV = digitalRead(left);
  bool centerV = digitalRead(center);
  bool rightV = digitalRead(right);
  int start = digitalRead(knop);
  Ultrasone();
  motortemp();

  Serial.println(rightV);

  if (leftV == 0 && centerV == 1 && rightV == 0) {
    carforward();
    digitalWrite(groen, HIGH);
    digitalWrite(geel, LOW);
    digitalWrite(rood, LOW);
    client.publish("Robot/robot1/status1", "1");
    client.publish("Robot/robot1/statusledO", "0");
    client.publish("Robot/robot1/statusledR", "0");
  } else if (leftV == 1 && centerV == 1 && rightV == 1) {
    carStop();
    digitalWrite(groen, LOW);
    digitalWrite(geel, HIGH);
    digitalWrite(rood, LOW);
    client.publish("Robot/robot1/status2", "2");

    if (stop) {
      stop = false;
      laststop = millis();
    }
    currentpos = millis();

    if (((currentpos - laststop) >= 5000) || digitalRead(knop) == LOW || startflag == true) {
      currentpos = laststop + 5500;
      stop = true;
      startflag = false;
      carforward();
      delay(300);
    }


  } else if (leftV == 0 && centerV == 0 && rightV == 0) {
    carStop();
    digitalWrite(groen, LOW);
    digitalWrite(geel, LOW);
    digitalWrite(rood, HIGH);
    client.publish("Robot/robot1/status", "404");
    client.publish("Robot/robot1/statusledR", "1");
  } else if (leftV == 1 && centerV == 1 && rightV == 0) {
    carturnleft();
  } else if (leftV == 0 && centerV == 1 && rightV == 1) {
    carturnright();
  } else if (leftV == 1 && centerV == 0 && rightV == 0) {
    carturnleft();
  } else if (leftV == 0 && centerV == 0 && rightV == 1) {
    carturnright();
  }

}

void carforward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carturnleft() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void carturnright() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void carStop() {
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}

void Ultrasone() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);


  duration = pulseIn(echoPin, HIGH);

  cm = (duration / 2) * 0.0343;

  Serial.print("Afstand: ");
  Serial.println(cm);

  if (cm <= 15) {
    carStop();
    digitalWrite(geel, HIGH);
    client.publish("Robot/robot1/status4", "3");
    client.publish("Robot/robot1/statusledO", "1");
    delay(500);
  } else {
    digitalWrite(geel, LOW);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);

  String message;
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    message += (char)payload[i];
  }

  Serial.println();
  Serial.println("-----------------------");

  if (String(topic) == "robot/start") {
    if (message == "go") {
      startflag = true;
    }
  }
}

void motortemp() {

  float temp = dht.readTemperature();
  dtostrf(temp, 7, 2, temp1);
  client.publish("Robot/robot1/motorTemp", temp1);
  Serial.println(temp);

  if (temp <= 30) {
    carStop();
  }
}
