#include "Arduino.h"
#include "pulse-sensor-arduino.h"
#include <dht.h>
#include "LM35.h"


// Pin Definitions
#define HEARTPULSE_PIN_SIG  A3
#define dataPin 8
#define LM35_PIN_VOUT  A1


// object initialization
PulseSensor heartpulse;
dht DHT;
LM35 lm35(LM35_PIN_VOUT);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;



void setup() {
    Serial.begin(9600);
    while (!Serial) ; 
    Serial.println("start");
   
    heartpulse.begin(HEARTPULSE_PIN_SIG);
    menuOption = menu();

}

void loop() {
  if(menuOption == '1') {
    // Heart Rate Pulse Sensor - Test Code
    //Measure Heart Rate
    int heartpulseBPM = heartpulse.BPM;
    Serial.println(heartpulseBPM);
    if (heartpulse.QS == true) {
    Serial.println("PULSE");
    heartpulse.QS = false;
    }
    }
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
    else if(menuOption == '2'){
      int readData=DHT.read11(dataPin);
      float t=DHT.temperature;
      float h=DHT.humidity;
     
      Serial.print("    Humidity = ");
      Serial.print(h);
      Serial.print(" % ");
      Serial.print("\n");
      delay(2000);
      
      
     }
     else if(menuOption == '3') {
    // LM35DZ - Temperature Sensor - Test Code
    //Get Measurment from LM35 temperature sensor.
    float lm35TempC = lm35.getTempC();
    Serial.print(F("Temp: ")); Serial.print(lm35TempC); Serial.println(F("[°C]"));

    }

   

    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
  
}

char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Heart Rate Pulse Sensor"));
    Serial.println(F("(2) DHT22/11 Humidity and Temperature Sensor"));
    Serial.println(F("(3) LM35DZ - Temperature Sensor"));
    
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
               Serial.println(F("Now Testing Heart Rate Pulse Sensor"));
            else if(c == '2') 
               Serial.println(F("Now Testing DHT22/11 Humidity and Temperature Sensor"));
            else if(c == '3') 
                Serial.println(F("Now Testing LM35DZ - Temperature Sensor"));
           
            else 
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
