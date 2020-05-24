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


#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);

#define EEPROM_STATE_ADDRESS_1 128
#define EEPROM_STATE_ADDRESS_2 144
void info1(void);



int ldr = 14;
int rain = 12;
int Gas = A0;
int led = 9;
int soil = 13;
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
void ldr1(void);
char ssid[] = "aisfibre";
char pass[] = "s0897773889";
char auth[] = "8gNuKSQ67E-UlPdznPuFh7u8sRAJfPiP";
void soilDetect(void);
void gasDetect(void);
void rainDetect(void);
#include <Servo.h>

Servo servo;

void setup()
{
servo.attach(15); // NodeMCU D8 pin
pinMode(led,OUTPUT);
pinMode(led,INPUT);
  pinMode(rain, INPUT);
  pinMode(Gas, INPUT);
  pinMode(soil, INPUT);

  Blynk.begin(auth, ssid, pass);
 // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  

  // Clear the buffer.
  display.clearDisplay();
static unsigned long time6 = millis();
    if((millis()-time6)>1500){
    time6 = millis();
  // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Hello world!");
  display.display();
    time6 = millis();
  display.clearDisplay();

  // Display Inverted Text
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setCursor(0,0);
  display.println("Hello world!");
  display.display();
    time6 = millis();
  display.clearDisplay();

  // Changing Font Size
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.setTextSize(2);
  display.println("Hello!");
  display.display();
    time6 = millis();
  display.clearDisplay();

  // Display Numbers
  display.setTextSize(1);
  display.setCursor(0,0);
  display.println(123456789);
  display.display();
    time6 = millis();
  display.clearDisplay();

  // Specifying Base For Numbers
  display.setCursor(0,0);
  display.print("0x"); display.print(0xFF, HEX); 
  display.print("(HEX) = ");
  display.print(0xFF, DEC);
  display.println("(DEC)"); 
  display.display();
    time6 = millis();
  display.clearDisplay();

  // Display ASCII Characters
  display.setCursor(0,0);
  display.setTextSize(2);
  display.write(3);
  display.display();
    time6 = millis();
  display.clearDisplay();

  // Scroll full screen
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Full");
  display.println("screen");
  display.println("scrolling!");
  display.display();
  display.startscrollright(0x00, 0x07);
    time6 = millis();
  display.stopscroll();
    time6 = millis();
  display.startscrollleft(0x00, 0x07);
    time6 = millis();
  display.stopscroll();
   time6 = millis();
  display.startscrolldiagright(0x00, 0x07);
    time6 = millis();
  display.startscrolldiagleft(0x00, 0x07);
    time6 = millis();
  display.stopscroll();
  display.clearDisplay();

  // Scroll part of the screen
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Scroll");
  display.println("some part");
  display.println("of the screen.");
  display.display();
  display.startscrollright(0x00, 0x00);
    time6 = millis();
    display.stopscroll();
  display.clearDisplay();
}
}
void loop() {
  info1();
  ldr1();
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
 led5.on(); display.setCursor(0,0);
  display.setTextSize(1);
  display.println("ONLINE");
  display.display();

 
 display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(0,0);
display.println("Rectangle");
display.drawRect(0, 15, 60, 40, WHITE);
display.display();
delay(2000);
  }
  else{
    led5.off();
  }
  display.setTextSize(1);
  display.println("OFFLINE");
  display.display();
 gasDetect();
  rainDetect();
  soilDetect();
}
void gasDetect(void) {
    static unsigned long time10 = millis();
    if((millis()-time10)>500){
    time10 = millis();
  if (analogRead(Gas)>100){
    led4.on();
    time10 = millis();

    Serial.println("GAS, GAS, GAS");      
  }
  else{
    led4.off();
  }
}
}
void rainDetect(void) {
  

static unsigned long time10 = millis();
    if((millis()-time10)>500){
    time10 = millis();
  if (digitalRead(rain) == LOW) {
 time10 = millis();

    Serial.println("Rain");
     led3.on();
}
  else{
    led3.off();
  }
}
}
1
void soilDetect(void) {
   if (digitalRead(soil)==HIGH) {
     led6.on();
  }   
    else{
      led6.off();
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

void ldr1(void){
  static unsigned long time7 = millis();
      if((millis()-time7)>5000){
    time7 = millis();
}
   int val = analogRead(ldr); // อ่านค่าแบบ analog จากขา ldr เก็นไว้ในตัวแปร val
  Serial.println(val);
  if (val < 200) {
    Serial.println("LED ON");
   led9.on();
  } else {
    Serial.println("LED OFF");
    led9.off();
  }
   time7 = millis();
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





#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_SSD1306 display(-1);

void setup()   
{                
  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  

  // Clear the buffer.
  display.clearDisplay();

  // Display Text
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,28);
  display.println("Hello world!");
  display.display();
  delay(2000);
  display.clearDisplay();

  // Display Inverted Text
  display.setTextColor(BLACK, WHITE); // 'inverted' text
  display.setCursor(0,28);
  display.println("Hello world!");
  display.display();
  delay(2000);
  display.clearDisplay();

  // Changing Font Size
  display.setTextColor(WHITE);
  display.setCursor(0,24);
  display.setTextSize(2);
  display.println("Hello!");
  display.display();
  delay(2000);
  display.clearDisplay();

  // Display Numbers
  display.setTextSize(1);
  display.setCursor(0,28);
  display.println(123456789);
  display.display();
  delay(2000);
  display.clearDisplay();

  // Specifying Base For Numbers
  display.setCursor(0,28);
  display.print("0x"); display.print(0xFF, HEX); 
  display.print("(HEX) = ");
  display.print(0xFF, DEC);
  display.println("(DEC)"); 
  display.display();
  delay(2000);
  display.clearDisplay();

  // Display ASCII Characters
  display.setCursor(0,24);
  display.setTextSize(2);
  display.write(3);
  display.display();
  delay(2000);
  display.clearDisplay();

  // Scroll full screen
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Full");
  display.println("screen");
  display.println("scrolling!");
  display.display();
  display.startscrollright(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);
  display.startscrollleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  delay(1000);    
  display.startscrolldiagright(0x00, 0x07);
  delay(2000);
  display.startscrolldiagleft(0x00, 0x07);
  delay(2000);
  display.stopscroll();
  display.clearDisplay();

  // Scroll part of the screen
  display.setCursor(0,0);
  display.setTextSize(1);
  display.println("Scroll");
  display.println("some part");
  display.println("of the screen.");
  display.display();
  display.startscrollright(0x00, 0x00);
}

void loop() {}
















int led = 13;
int ldr = A5;
void setup()
{
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  int val = analogRead(ldr); // อ่านค่าแบบ analog จากขา ldr เก็นไว้ในตัวแปร val
  Serial.println(val);
  if (val < 200) {
    Serial.println("LED ON");
    digitalWrite(led, 1);
  } else {
    Serial.println("LED OFF");
    digitalWrite(led, 0);
  }
  delay(100);
}
*/
    
