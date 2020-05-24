
/*uhh
   GPIO5  D1 LED
   GPIO4  D2 FLM
   GPIO14 D5 soil
   GPIO12 D6 rain
   GPIO13 D7 GAS
*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 16
Adafruit_SSD1306 display(OLED_RESET);
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define EEPROM_STATE_ADDRESS_1 128
#define EEPROM_STATE_ADDRESS_2 144

#define soil 2
#define rain 12
#define Gas A0
int state = 0;
int led = 14;
int buz = 13;

WidgetTerminal terminal(V3);
WidgetLED led1(V1);
WidgetLED led2(V2);
WidgetLED led3(V3);
WidgetLED led4(V4);
WidgetLED led5(V5);
WidgetLED led6(V6);
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
char pass[] = "ae246532";
char auth[] = "Tx07n9HuWYokKZTHhaUVge5P-LRyvyQ-";

void rainDetect(void);

void setup()
{
  pinMode(buz,OUTPUT);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
display.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
display.setTextSize(1); // กำหนดขนาดตัวอักษร
display.setTextColor(WHITE);
display.setCursor(0,0); // กำหนดตำแหน่ง x,y ที่จะแสดงผล
display.println(" OLED 0.96 TESTER ");
display.setCursor(0,10);
display.setTextSize(2);
display.setTextColor(BLACK, WHITE); //กำหนดข้อความสีขาว ฉากหลังสีดำ
display.println(" Myarduino");
display.setCursor(0,32);
display.setTextSize(1);
display.setTextColor(WHITE);
display.println("128 x 64 Pixels 0.96");
display.setCursor(0,48);
display.setTextSize(1);
display.setTextColor(WHITE);
display.println(" www.myarduino.net "); // แสดงผลข้อความ www.Myarduino.net
display.display();
display.clearDisplay();
pinMode(led,OUTPUT);

  pinMode(rain, INPUT);
  pinMode(Gas, INPUT);
  pinMode(soil, INPUT);

  Blynk.begin(auth, ssid, pass);

  servo.attach(15); // NodeMCU D8 pin
  


   if (Blynk.connected()) {
    Blynk.run();
    digitalWrite(led,HIGH);
    
  }
else{
 digitalWrite(led,LOW);
}
display.setCursor(0,0);
display.setTextSize(2);
display.setTextColor(WHITE);
display.println("Blynk.connected"); // แสดงผลข้อความ www.Myarduino.net
display.display();
delay(2000);

digitalWrite(led,LOW);
delay(1000);
digitalWrite(led,HIGH);
delay(1000);
digitalWrite(led,LOW);
delay(1000);
display.clearDisplay();



}

void loop() {
  if (Blynk.connected()) {
    Blynk.run();
   
digitalWrite(led,HIGH);
delay(1000);

digitalWrite(led,LOW);
delay(1000);

 led5.on();
 
  }
  else{
    led5.off();
  }
 
 gasDetect();

  rainDetect();
  soilDetect();
  
 Blynk.virtualWrite(V18,Tc);
  delay(500);
}

void gasDetect(void) {
  if (analogRead(Gas)>100){
    led4.on();
    delay(200);
    state = 2;
    Serial.println("GAS, GAS, GAS");
       
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
     led6.off();
  }
    
    else{
      led6.on();
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
