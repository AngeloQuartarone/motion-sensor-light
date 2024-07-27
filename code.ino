#include <WiFiS3.h>
#include <ArduinoMqttClient.h>
#include "arduino_secrets.h"

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "192.168.1.35";
int port = 1883;
const char topic[] = "arduino";

const long interval = 60000;
unsigned long previousMillis = 0;
int lightState = 0;

#define WAKEUP_PIN 6
#define LED 4
#define BUTTON 7
int on = 0;  // Inizialmente impostato a 0 per controllare la logica dal sensore di movimento
int alwaysOn = 0;
int lastSentState = -1; // Stato dell'ultimo messaggio MQTT inviato (-1 per indicare uno stato non inizializzato)

void setup() {
  pinMode(WAKEUP_PIN, INPUT);
  pinMode(LED, OUTPUT);
  Serial.begin(9600);

  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();
  mqttClient.setUsernamePassword("mqttuser", "mqttpassword");

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  while (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();
}

void loop() {
  int sensorValue = digitalRead(WAKEUP_PIN);
  int buttonState = digitalRead(BUTTON);
  delay(100);
  Serial.print(sensorValue);
  Serial.print(", ");
  Serial.println(alwaysOn);
  //delay(100);


  if (sensorValue == HIGH) {
    on = 1;
  } else {
    on = 0;
  }

  if (buttonState) {
    alwaysOn = !alwaysOn;
  }
  mqttClient.poll();
  //messageDelivered = 0;

  if (!alwaysOn) {
    digitalWrite(LED, LOW);

    if (on && lastSentState != 1) {
      mqttClient.beginMessage(topic);
      mqttClient.print("light");
      mqttClient.endMessage();
      lastSentState = 1;
    } else if (!on && lastSentState != 0) {
      mqttClient.beginMessage(topic);
      mqttClient.print("nolight");
      mqttClient.endMessage();
      lastSentState = 0;
    }
  } else {
    digitalWrite(LED, HIGH);
    if (lastSentState != 1) {
      mqttClient.beginMessage(topic);
      mqttClient.print("light");
      mqttClient.endMessage();
      lastSentState = 1;
    }
  }
}
