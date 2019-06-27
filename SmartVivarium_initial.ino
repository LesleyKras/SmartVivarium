#include <ArduinoJson.h>
#include <dht.h>
dht DHT;

// Milliseconds loop instead of delay
unsigned long startMillis;  //some global variables available anywhere in the program
unsigned long currentMillis;
const unsigned long period = 5000;  //the value is a number of milliseconds

//Configuring sensor pins
#define groundMoistureSensor1 A0
#define groundMoistureSensor2 A1

#define tempHumiditySensor 7
#define ledPin 12

void setup()
{
  Serial.begin(9600);  //start Serial in case we need to print debugging info
  pinMode(ledPin, OUTPUT);
  startMillis = millis();  //initial start time

  DynamicJsonDocument doc(2048);
  
  //Load json reptile_profiles
  char reptileData[] = "{\"Reptiles\":{\"Leopard_gecko\":{\"temperature\":{\"minimum\":25,\"maximum\":29},\"humidity\":{\"minimum\":30,\"maximum\":40}},\"Crested_gecko\":{\"temperature\":{\"minimum\":21,\"maximum\":26},\"humidity\":{\"minimum\":70,\"maximum\":80}},\"Bearded_dragon\":{\"temperature\":{\"minimum\":25,\"maximum\":35},\"humidity\":{\"minimum\":35,\"maximum\":40}}}}";
  deserializeJson(doc, reptileData);

  const char* reptiles = doc["Reptiles"];
  
}

void loop()
{
  currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
  if (currentMillis - startMillis >= period)  //test whether the period has elapsed
  {
    //Read data from sensors
    int gm1data = analogRead(groundMoistureSensor1);
    int gm2data = analogRead(groundMoistureSensor2);
    DHT.read11(tempHumiditySensor);

    turnOnPump(100);

    //Print data from sensors
    Serial.println("Ground Moisture:");
    Serial.println("Sensor 1: ");
    Serial.println(gm1data);
    Serial.println("Sensor 2: ");
    Serial.println(gm2data);
    Serial.println("-----------------");
    Serial.println("Temp and humidity:");
    Serial.println("Temp: ");
    Serial.println(DHT.temperature);
    Serial.println("Humidity: ");
    Serial.println(DHT.humidity);
    Serial.println("=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    
    startMillis = currentMillis;
  }
}

void turnOnPump(int duration)
{
  digitalWrite(ledPin, HIGH);
  delay(duration);
  digitalWrite(ledPin, LOW);  
}
