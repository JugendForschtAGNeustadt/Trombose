#include <ESP8266WiFi.h>

const char* ssid = "Trombose";
const char* password = "12345678";

// Create an instance of the server
// specify the port to listen on as an argument
WiFiServer server(8888);
WiFiClient client;

int triggerVL=D5; 
int echoVL=D6; 
long dauerVL=0; 
long entfernungVL=0;
 
int triggerHR=D7; 
int echoHR=D8; 
long dauerHR=0; 
long entfernungHR=0;

int triggerVR=D0; 
int echoVR=D1; 
long dauerVR=0; 
long entfernungVR=0;

int triggerHL=D4; 
int echoHL=D3; 
long dauerHL=0; 
long entfernungHL=0;

void setup()

{
Serial.begin (115200); 
pinMode(triggerVR, OUTPUT); 
pinMode(echoVR, INPUT);

pinMode(triggerHR, OUTPUT); 
pinMode(echoHR, INPUT); 

pinMode(triggerVL, OUTPUT); 
pinMode(echoVL, INPUT);

pinMode(triggerHL, OUTPUT); 
pinMode(echoHL, INPUT); 

Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.softAP(ssid, password);
  delay(10000);

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  // Start the server
  server.begin();
  Serial.println("");
  Serial.println("Server started");
  delay(3000);

}

void ConnectClient(){

  if(!client){
    client = server.available();
    if (!client) {
    return;
  }

  Serial.println("new client");
   }
  
  
  }

void SendToClient(String message){
  ConnectClient();
  
  
 }

String ReceiveFromClient(){

  String text="";

  //ConnectClient();
   client = server.available();
  
  if (!client) {
    return "";
  }
  Serial.println("new client");

  if(client.available()) {

     Serial.println("Client sent something...");
  
  // Read a line of text from client
  text = client.readStringUntil('\r');
  Serial.print("Received text: ");
  Serial.println(text);
  client.flush();//???
  }

  return text;
 }

void loop()
{

digitalWrite(triggerVR, LOW); 
delay(5); 
digitalWrite(triggerVR, HIGH); 
delay(10);
digitalWrite(triggerVR, LOW);
dauerVR = pulseIn(echoVR, HIGH); 
entfernungVR = (dauerVR/2) * 0.03432; 

digitalWrite(triggerHR, LOW); 
delay(5); 
digitalWrite(triggerHR, HIGH); 
delay(10);
digitalWrite(triggerHR, LOW);
dauerHR = pulseIn(echoHR, HIGH); 
entfernungHR = (dauerHR/2) * 0.03432; 

digitalWrite(triggerVL, LOW); 
delay(5); 
digitalWrite(triggerVL, HIGH); 
delay(10);
digitalWrite(triggerVL, LOW);
dauerVL = pulseIn(echoVL, HIGH); 
entfernungVL = (dauerVL/2) * 0.03432; 

digitalWrite(triggerHL, LOW); 
delay(5); 
digitalWrite(triggerHL, HIGH); 
delay(10);
digitalWrite(triggerHL, LOW);
dauerHL = pulseIn(echoHL, HIGH); 
entfernungHL = (dauerHL/2) * 0.03432; 


Serial.println(entfernungVR);

Serial.println(entfernungVL);

Serial.println(entfernungHR);

Serial.println(entfernungHL); 
Serial.println("________________________"); 
String ClientMsg=ReceiveFromClient();
delay(1000);
}
