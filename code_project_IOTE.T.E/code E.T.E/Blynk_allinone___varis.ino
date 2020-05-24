/*
   GPIO5  D1 LED
   GPIO4  D2 FLM
   GPIO14 D5 TMP
   GPIO12 D6 PIR
   GPIO13 D7 GAS
*/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SimpleTimer.h>
#include <TimeLib.h>
#include <WidgetRTC.h>
#include <EEPROM.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <TridentTD_LineNotify.h>  //thank you Mr.TridentTD https://github.com/TridentTD/TridentTD_LineNotify

#define EEPROM_STATE_ADDRESS_1 128
#define EEPROM_STATE_ADDRESS_2 144

#define soil 5
#define rain 12
#define Gas 13
int state = 0;
SimpleTimer timer;
WidgetRTC rtc;

WidgetTerminal terminal(V3);
WidgetLED led1(V4);
WidgetLED led2(V5);
WidgetLED led3(V6);
WidgetLED led4(V7);



char ssid[] = "A30";
char pass[] = "a2252122521";
char auth[] = "FFOTn3lOOPhzEvt9NNWJgQ4lvPMZvAXS";


void setup()
{
  Serial.begin(115200);
  Serial.println("\Starting");

  pinMode(rain, INPUT);
  pinMode(Gas, INPUT);
  pinMode(soil, INPUT);

  Blynk.begin(auth, ssid, pass);



}

void loop() {
  if (Blynk.connected()) {
    Blynk.run();
  }
  timer.run();
 gasDetect();
  rainDetect();
  soilDetect();
  
}

void gasDetect() {
  if (digitalRead(Gas) == LOW) {
    delay(200);
    state = 2;
    Serial.println("GAS, GAS, GAS");
    led4.on();
  }
}

void rainDetect() {
  if (digitalRead(rain) == HIGH) {
    delay(200);
    state = 2;
    Serial.println("Rain");
     led3.on();
  }
}

void soilDetect() {
  
    delay(200);
    Blynk.virtualWrite(V0,soil);
    state = 2;
    }
