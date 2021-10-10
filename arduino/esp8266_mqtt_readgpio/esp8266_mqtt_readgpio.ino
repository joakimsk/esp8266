#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = ""; // WIfi ssid
const char* password = ""; // Wifi password

const char* mqtt_server = "mqttbroker.com"; // MQTT broker IP or address
const int mqtt_server_port = 1883; // MQTT broker port
const char* mqtt_clientid = "esp01"; // This units name at mqtt broker
const char* mqtt_username = ""; // Username to access broker
const char* mqtt_password = ""; // Password to access broker

// See return codes
// https://pubsubclient.knolleary.net/api.html#state

// Initializes the espClient. You should change the espClient name if you have multiple ESPs running in your home automation system
WiFiClient espClient;
PubSubClient client(espClient);

const int buttonPin = 2;

int buttonState = 0;         // variable for reading the pushbutton status


// Timers auxiliar variables
long now = millis();
long lastMeasure = 0;

// Don't change the function below. This functions connects your ESP8266 to your router
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address: ");
  Serial.println(WiFi.localIP());
}

// This functions reconnects your ESP8266 to your MQTT broker
// Change the function below if you want to subscribe to more topics with your ESP8266 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(mqtt_clientid, mqtt_username, mqtt_password)) {
      Serial.println("connected");  
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Enable pullup-resistor

  Serial.begin(74880);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_server_port);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  if(!client.loop())
    client.connect(mqtt_clientid, mqtt_username, mqtt_password); // 

  now = millis();

  // Publishes every 5 seconds
  if (now - lastMeasure > 5000) {
    lastMeasure = now;
    buttonState = digitalRead(buttonPin);
    Serial.println(buttonState);
    if (buttonState == HIGH) { // We invert the state sent, since we use a pullup
      client.publish("home/switch", "0"); 
    } else {
      client.publish("home/switch", "1");
    }
  }
} 
