/*uhh
   GPIO5  D1 LED
   GPIO4  D2 FLM
   GPIO14 D5 soil
   GPIO12 D6 rain
   GPIO13 D7 GAS
*/

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define EEPROM_STATE_ADDRESS_1 128
#define EEPROM_STATE_ADDRESS_2 144

#define soil 4
#define rain 12
#define Gas 13
int state = 0;
int buz = 5;
WidgetTerminal terminal(V3);
WidgetLED led1(V4);
WidgetLED led2(V5);
WidgetLED led3(V6);
WidgetLED led4(V7);
WidgetLED led5(V0);
#include <Servo.h>

Servo servo;

int ThermistorPin = 0;
int Vo;
float R1 = 10000;
float logR2, R2, T, Tc, Tf;
float c1 = 1.009249522e-03, c2 = 2.378405444e-04, c3 = 2.019202697e-07;

void soilDetect(void);
void gasDetect(void);
char ssid[] = "A30";
char pass[] = "a2252122521";
char auth[] = "FFOTn3lOOPhzEvt9NNWJgQ4lvPMZvAXS";

void rainDetect(void);

void setup()
{
pinMode(buz,OUTPUT);
  pinMode(rain, INPUT);
  pinMode(Gas, INPUT);
  pinMode(soil, INPUT);

  Blynk.begin(auth, ssid, pass);

  servo.attach(15); // NodeMCU D8 pin
  


  Serial.begin(9600);
  Serial.println("\Starting");
   if (Blynk.connected()) {
    Blynk.run();
    tone(buz,5);
    delay(400);
     tone(buz,10);
    delay(400);
     tone(buz,15);
    delay(400);
    noTone(buz);
    
  }

}

void loop() {
  if (Blynk.connected()) {
    Blynk.run();
  }
 
 gasDetect();
  rainDetect();
  soilDetect();
  
 Blynk.virtualWrite(V18,Tc);
  delay(500);
}

void gasDetect(void) {
  if (digitalRead(Gas) == HIGH) {
    delay(200);
    state = 2;
    Serial.println("GAS, GAS, GAS");
    led4.on();
     Blynk.virtualWrite(V17,Gas);
  }
  else{
    led4.off();
  }
}

void rainDetect(void) {
  if (digitalRead(rain) == LOW) {
    delay(200);
    state = 2;
    Serial.println("Rain");
     led3.on();
}
  else{
    led3.off();
  }
}

void soilDetect(void) {
   if (digitalRead(soil)==LOW) {
    
     led5.on();
  }
    
    else{
      led5.off();
    }
    
    }




BLYNK_WRITE(V1)
{
   servo.write(param.asInt());
}

BLYNK_WRITE(V2)
{
  servo.write(0);
}
BLYNK_WRITE(V3)
{
  servo.write(180);
}
