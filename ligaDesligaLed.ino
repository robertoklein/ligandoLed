#include <ESP8266WiFi.h>
#include <PubSubClient.h>

//const char* mqttServer = "m14.cloudmqtt.com";
//const int mqttPort = 19616;
//const char* mqttUser = "axxfrycf";
//const char* mqttPassword = "qAdD5bpKyIk4";

const char* mqttServer = "179.106.217.208";
const int mqttPort = 1883;
const char* mqttUser = "";
const char* mqttPassword = "";

#define LEDAZUL 14

WiFiClient espClient;
PubSubClient client(espClient);

int outputpin = A0;

char ssid[] = "AndroidAP";
char pass[] = "ifyy0846";

//char ssid[] = "fmASUS";
//char pass[] = "fred#123";

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.println("Message arrived [");
  Serial.println(topic);
  
  if(strcmp(topic,"led/liga")==0){
    ligaLed();
  }else if(strcmp(topic,"led/desliga")==0){
    desligaLed();
  }
  
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void setup() {
Serial.begin(9600);
WiFi.begin(ssid,pass);

pinMode(LEDAZUL, OUTPUT);

client.setCallback(callback);

while (WiFi.status() != WL_CONNECTED) {
delay(500);
Serial.println("Connecting to WiFi..");
}

client.setServer(mqttServer, mqttPort);
client.setCallback(callback);

while (!client.connected()) {
    Serial.println("Connecting to MQTT...");
    
    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
    //if (client.connect("ESP8266Client")) {
      Serial.println("connected");  
    } else {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

Serial.println("Connected to the WiFi network");
}

void loop() {
  client.subscribe("led/liga", 1);
  client.subscribe("led/desliga", 1);
  client.loop();
}

void ligaLed(){
  Serial.println("entrou no ligaled");
  digitalWrite(LEDAZUL, LOW);
}

void desligaLed(){
  Serial.println("entrou no desligaled");
  digitalWrite(LEDAZUL, HIGH);
}





