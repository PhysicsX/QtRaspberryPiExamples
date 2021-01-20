
#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// Update these with values suitable for your network.

const char* ssid = "UPC1009332";
const char* password = "FTGYCYGD";

const char* mqttServer = "iot.reyax.com";
const char* mqttUserName = "zFtbPwRwxE"; // MQTT username
const char* mqttPwd = "GhMshMhWG9"; // MQTT password
const char* clientID = "zFtbPwRwxE0123"; // client id
const char* topic = "api/request"; //publish topic

/*
const char* ssid = "UPC1009332";
const char* password = "FTGYCYGD";
const char* mqttServer = "iot.reyax.com";
const char* mqttUserName = "AxkRcYFqe7"; // MQTT username
const char* mqttPwd = "zhsghF6DSw"; // MQTT password
const char* clientID = "AxkRcYFqe70001"; // client id
const char* topic = "api/request"; //publish topic
*/

unsigned long prevMillis = 0;
const long interval = 1000;
String msgStr = ""; // MQTT message buffer

int tmp = 0;
int pot = 0;
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long startMillisPot;
unsigned long currentMillisPot;
unsigned long currentMillis;
const unsigned long period = 2000;  //the value is a number of mill
const unsigned long periodPot = 500;  //the value is a number of mill

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) 
  {
    
    if (client.connect(clientID, mqttUserName, mqttPwd)) 
    {
      Serial.println("MQTT connected");
      client.subscribe("api/command/28/#");
    } 
    else 
    {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000); // wait 5sec and retry
    }
    
  }
}

void setup() 
{
  Serial.begin(9600);
  setup_wifi();
  client.setServer(mqttServer, 1883);
  client.setCallback(callback);
}



void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  
  if (currentMillis - startMillisPot >= periodPot)  //test whether the period has elapsed
  {
    pot = analogRead(A0);
    Serial.println(pot);
    startMillisPot = currentMillis;
  }
  
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    tmp ++;
    //publish Command
   // msgStr="{\"action\": \"command/insert\",\"deviceId\": \"c0Qm6reG9T4djVORK11HbhciG6LyCbUdMXQB\",\"command\": {\"command\": \"Control Temperature\",\"parameters\": {\"Control\":\"Temperature\"},\"status\":\"to do\",\"result\":{\"temperature\": \"27\"}}}";
   


   String tmpStr = String(pot);
   msgStr="{\"action\": \"command/insert\",\"deviceId\": \"xD5GufgiHVRm6MkfVypfEDKJJzKOyoILkhl0\",\"command\": {\"command\": \"Control Temperature\",\"parameters\": {\"Control\":\"Temperature\"},\"status\":\"to do\",\"result\":{\"temperature\": \""+tmpStr+"\"}}}";

    byte arrSize = msgStr.length() + 1;
    char msg[arrSize];
    Serial.print("PUBLISH DATA:");
    Serial.println(msgStr);
    msgStr.toCharArray(msg, arrSize);
    client.publish(topic, msg);
    msgStr = "";
    startMillis = currentMillis;;
  }
}

//subscribe call back
void callback(char*topic, byte* payload, unsigned int length) {
  Serial.print("Messagearrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");
  
    for (int i = 0; i< length; i++) {
      Serial.print((char)payload[i]);
    }
    
  Serial.println();
  Serial.print("Message size :");
  Serial.println(length);
  Serial.println();
  Serial.println("-----------------------");
}
