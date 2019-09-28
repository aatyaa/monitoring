#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include"stdio.h"
#include"string.h"

const char* ssid = "IMT Staff";                   // wifi ssid
const char* password =  "Imt.Sch@Dok_HQ2019";         // wifi password
const char* mqttServer = "soldier.cloudmqtt.com";    // IP adress Raspberry Pi
const int   mqttPort = 16475;
const char* mqttUser = "lpxntmad";      // if you don't have MQTT Username, no need input
const char* mqttPassword = "C4AaxTHSNPk5";  // if you don't have MQTT Password, no need input

WiFiClient espClient;
PubSubClient client(espClient);

#define CS 15               //define chip select line for manual control
#define D0 16
#define D4 2
volatile byte flag=0;

void setup() {

  pinMode(D4,INPUT);
  pinMode(CS, OUTPUT);                                       //configure the line as output ss 
  pinMode(D0, OUTPUT);
  
  Serial.begin(115200);

  digitalWrite(CS, HIGH);                                    //Initialize the CS line to HIGH
  digitalWrite(D0, HIGH);
  attachInterrupt(2,EXTERNAL_INTERRUPT,FALLING);
  SPI.begin();                                               //Initialize the SPI module--> configures the MOSI, MISO and CLOCK lines
  SPI.beginTransaction(SPISettings(3000000, LSBFIRST, SPI_MODE0));
  
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }
}

void EXTERNAL_INTERRUPT(){
  flag++;
}

void loop() {

    byte I_RH;byte D_RH;byte I_TEMP;byte D_TEMP;byte LDR;byte GAS;
    String Dot=".";
    Serial.print("HUM"); Serial.print("    ");Serial.print("TEMP");Serial.print("    ");Serial.print("LDR");Serial.print("    ");Serial.println("GAS");
    ////////////////HUM/////////////////////////////////////
    while(flag==0);
    digitalWrite(CS, LOW);                                      
    I_RH = SPI.transfer(10);                            
    Serial.print(I_RH);
    digitalWrite(CS, HIGH);
    digitalWrite(D0, LOW);
    delay(10);
    digitalWrite(D0, HIGH);
    Serial.print('.');
    while(flag==1);
    digitalWrite(CS, LOW);                                      
    D_RH = SPI.transfer(20);
    client.publish("HUM",String(I_RH+Dot+D_RH).c_str());                                
    Serial.print(D_RH);
    digitalWrite(CS, HIGH);
    digitalWrite(D0, LOW);
    delay(10);
    digitalWrite(D0, HIGH);
    Serial.print("   ");
    /////////////////////////////TEMP///////////////////////////////////////////////
    while(flag==2);
    digitalWrite(CS, LOW);                                      
    I_TEMP = SPI.transfer(30);                            
    Serial.print(I_TEMP);
    digitalWrite(CS, HIGH);
    digitalWrite(D0, LOW);
    delay(10);
    digitalWrite(D0, HIGH);
    Serial.print('.');
    while(flag==3);
    digitalWrite(CS, LOW);                                      
    D_TEMP = SPI.transfer(40);
    client.publish("TEMP",String(I_TEMP+Dot+D_TEMP).c_str());                            
    Serial.print(D_TEMP);
    digitalWrite(CS, HIGH);
    digitalWrite(D0, LOW);
    delay(10);
    digitalWrite(D0, HIGH);
    Serial.print("   ");
    /////////////////////LDR///////////////////////////
    while(flag==4);
    digitalWrite(CS, LOW);                                      
    LDR = SPI.transfer(50);
    client.publish("LDR",String(LDR).c_str());                            
    Serial.print(LDR);
    digitalWrite(CS, HIGH);
    digitalWrite(D0, LOW);
    delay(10);
    digitalWrite(D0, HIGH);
    Serial.print("    ");
    ///////////////////////////GAS////////////////////////////////////
    while(flag==5);
    digitalWrite(CS, LOW);                                      
    GAS = SPI.transfer(60);
    client.publish("GAS",String(GAS).c_str());                            
    Serial.println(GAS);
    digitalWrite(CS, HIGH);
    digitalWrite(D0, LOW);
    delay(10);
    digitalWrite(D0, HIGH);
    flag=0;
    client.loop();
     
}
