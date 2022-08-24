/*
   codeE.T.E GAMMA03 อัพเดท

   1จอOLED
   2ไฟstatus
   GPIO0 D3 FLASH
   GPIO1 TX TXD0
   GPIO2 D4
   GPIO3 RX RXD0
   GPIO4 D2 TXD1
   GPIO5 D1
   GPIO6
   GPIO7
   GPIO8
   GPIO9 SDD2
   GPTO10 SDD3
   GPIO11
   GPIO12 D6 HMOSI
   GPIO13 D7 RXD2 HMISO
   GPIO14 D5 HSCLK
   GPIO15 D8
   GPIO16  USER WAKE
*/
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define EEPROM_STATE_ADDRESS_1 128
#define EEPROM_STATE_ADDRESS_2 144
void info1(void);
int rain = 12;
int Gas = A0;
int led = 9;
int soil = 13;
int ldr = 14;
int ledst = 15;
int LED = 0;
static unsigned long time4 = millis();
// Bitmap of MarilynMonroe Image
WidgetLED led1(V1);
WidgetLED led2(V2);
WidgetLED led3(V3);
WidgetLED led4(V4);
WidgetLED led5(V5);
WidgetLED led6(V6);
WidgetLED led7(V7);
WidgetLED led8(V8);
WidgetLED led9(V9);

char ssid[] = "aisfibre";
char pass[] = "s0897773889";
char auth[] = "Tx07n9HuWYokKZTHhaUVge5P-LRyvyQ-";
void soilDetect(void);
void gasDetect(void);
void rainDetect(void);
#include <Servo.h>

Servo servo;

void setup()
{
servo.attach(15); // NodeMCU D8 pin
pinMode(led,OUTPUT);

  pinMode(rain, INPUT);
  pinMode(Gas, INPUT);
  pinMode(soil, INPUT);

  Blynk.begin(auth, ssid, pass);

  
}
void loop() {
  info1();
static unsigned long time1 = millis();
  static unsigned long time2 = millis();
    if((millis()-time1)>5000){
    time1 = millis();
   
        led8.on();
      
    digitalWrite(led,HIGH);
  }
    else{  if((millis()-time2)>400){
    time2 = millis();
   
      digitalWrite(led,LOW);
    led8.off();  }
  }
  if (Blynk.connected()) {
    Blynk.run();  
 led5.on();
  }
  else{
    led5.off();
  }
 gasDetect();
  rainDetect();
  soilDetect();
}
void gasDetect(void) {
  if (analogRead(Gas)>100){
    led4.on();
    delay(200);

    Serial.println("GAS, GAS, GAS");      
  }
  else{
    led4.off();
  }
}
void rainDetect(void) {
  if (digitalRead(rain) == LOW) {
    delay(200);

    Serial.println("Rain");
     led3.on();
}
  else{
    led3.off();
  }
}
void soilDetect(void) {
   if (digitalRead(soil)==HIGH) {
     led6.on();
  }   
    else{
      led6.offvaris22521
      ();
    } 
    }
    void soilrain(void){
      if(digitalRead(rain)==HIGH){
      led7.on();
       }
    else {
      
       led7.off();
   
      
    }
    }
     void info1(void){
   static unsigned long time3 = millis();
      if((millis()-time3)>5000){
    time3 = millis();
    digitalRead(rain);
    digitalRead(soil);
   Blynk.virtualWrite(D6,rain);
    Blynk.virtualWrite(D7,soil);
     Blynk.virtualWrite(V30,ldr,"^ldr^");
     
      Blynk.virtualWrite(V30,soil,"^soil^");
     if (Blynk.connected()) {
     Blynk.virtualWrite(V30,"connected");
}
}
   }
   BLYNK_WRITE(V35)
{
   servo.write(param.asInt());
}

BLYNK_WRITE(V36)
{
  servo.write(0);
}
BLYNK_WRITE(V37)
{
  servo.write(90);
}

   /*
    * #define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

Servo servo;

char auth[] = "Blynk Auth Token";
char ssid[] = "your ssid";
char pass[] = "wifi password";

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  servo.attach(15); // NodeMCU D8 pin
  
 }
  
void loop()
{
  
  Blynk.run();
  
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
  servo.write(90);
}


*/
    
