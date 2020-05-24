#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 127 // pixel ความกว้าง
#define SCREEN_HEIGHT 64 // pixel ความสูง 
// กำหนดขาต่อ I2C กับจอ OLED
#define OLED_RESET -1 //ขา reset เป็น -1 ถ้าใช้ร่วมกับขา Arduino reset
Adafruit_SSD1306 OLED(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WidgetTerminal terminal(V30);
WidgetLED led1(V1);
WidgetLED led2(V2);
WidgetLED led3(V3);
void alarm1();
#define stled1 13
#define stled2 12
#define buz 0
int i = 0 ;
int t1 = 0;
char ssid[] = "aisfibre";
char pass[] = "s0897773889";
char auth[] = "doO0XK6TbclY6mCDwI3KWFq7ZdKuJHKf";
void setup() {
  Serial.begin(9600);
  pinMode(stled1, OUTPUT);
  pinMode(stled2, OUTPUT);
  pinMode(buz, OUTPUT);
  tone(buz, 1000, 500);
  delay(400);
  tone(buz, 1500, 500);
  delay(400);
  tone(buz, 2000, 500);
  delay(400);
  noTone(buz);
  Blynk.begin(auth, ssid, pass);
  digitalWrite(stled1, 0);
  digitalWrite(stled1, 0);
  delay(1000);
  if (!OLED.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // สั่งให้จอ OLED เริ่มทำงานที่ Address 0x3C
    Serial.println("SSD1306 allocation failed");
  } else {
    Serial.println("ArdinoAll OLED Start Work !!!");
  }
}
void loop() {
  if (Blynk.connected()) {
    Blynk.run();
 while (t1<3){
 t1++;
 terminal.println("Connect...");
 terminal.println("SSF");
  Blynk.notify("Connect..."); 
 Serial.println(t1);
 delay(1000);
    }
    OLED.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
    OLED.setTextColor(WHITE, BLACK);
    OLED.setCursor(50, 32);
    OLED.setTextSize(1);
    OLED.println("CONNECTED"); // แสดงผลข้อความ ALL
    OLED.display(); // สั่งให้จอแสดงผล
  }
  else{
 alarm1();
  OLED.clearDisplay(); // ลบภาพในหน้าจอทั้งหมด
  OLED.setTextColor(WHITE, BLACK);
  OLED.setCursor(0, 32);
  OLED.setTextSize(1);
  OLED.println("CONNECTING.."); // แสดงผลข้อความ ALL
  OLED.display(); // สั่งให้จอแสดงผล
}
}
void alarm1(){

  tone(buz, 1500, 500);
  delay(100);
  noTone(buz);
  i++;
   delay(100);
  if(i==10){
    i=0;
    delay(1000);
  }
}
