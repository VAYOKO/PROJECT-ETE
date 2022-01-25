// DS1302_Serial_Easy (C)2010 Henning Karlsen
// web: http://www.henningkarlsen.com/electronics
//
// A quick demo of how to use my DS1302-library to 
// quickly send time and date information over a serial link
//
// I assume you know how to connect the DS1302.
// DS1302:  CE pin    -> Arduino Digital 2
//          I/O pin   -> Arduino Digital 3
//          SCLK pin  -> Arduino Digital 7

#include <DS1302.h>

// Init the DS1302
DS1302 rtc(4, 3,2);

#include <Adafruit_Sensor.h>

int ledState = LOW;             // ledState used to set the LED



unsigned long gulStart_Read_Timer = 0;
#include "DHT.h"

#define DHTPIN 7// Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
#include <SPI.h>
#include <SD.h>
File LOG; // สร้างออฟเจก File สำหรับจัดการข้อมูล
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long fadeStartTime;
// constants won't change:
const long interval = 100;           // interval at which to blink (milliseconds)

unsigned long previousMillis1 = 0;        // will store last time LED was updated
unsigned long previousMillis = 0;        // will store last time LED was updated
unsigned long previousMillis2 = 0;        // will store last time LED was updated
const int chipSelect = 5; // กำหนดขา CS ของโมดูล SD Card กับ Arduino ที่ขา 4
int led = 6;
int buz = 8;
DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  // Set the clock to run-mode, and disable the write protection
  rtc.halt(false);
  rtc.writeProtect(false);
  
  // Setup Serial connection
  Serial.begin(9600);
pinMode(buz,OUTPUT);
   //The following lines can be commented out to use the values already stored in the DS1302
  //rtc.setDOW(FRIDAY);        // Set Day-of-Week to FRIDAY
  //rtc.setTime(21, 25, 0);     // Set the time to 12:00:00 (24hr format)
 // rtc.setDate(24, 1, 2022);   // Set the date to August 6th, 2010

  tone(buz,5);
  delay(400);
  tone(buz,10);
  delay(400);
   tone(buz,15);
  delay(400);
  noTone(buz);
  sei(); //Enables interrupts
  gulStart_Read_Timer - millis();
  dht.begin();

  pinMode(led, OUTPUT);
 fadeStartTime = millis();
  
  while (!Serial) {
  }
  Serial.print("Initializing SD card...");
  pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");


}

void loop()
{
  
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= 1000) {
   
  
  // Wait one second before repeating :)
  LOG = SD.open("LOG.txt", FILE_WRITE); // เปิดไฟล์ที่ชื่อ test.txt เพื่อเขียนข้อมูล โหมด FILE_WRITE
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
  // ถ้าเปิดไฟล์สำเร็จ ให้เขียนข้อมูลเพิ่มลงไป
  if (LOG) {
    Serial.print("Writing to LOG.txt...");
    LOG.print(rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '/')); // สั่งให้เขียนข้อมูล
     LOG.print(" ");
    LOG.print(rtc.getTimeStr());
    LOG.print(",");
    LOG.print(hic);
    LOG.print(",");
    LOG.println(h);
  
    
  
  
    LOG.close(); // ปิดไฟล์
    Serial.println("done.");
  } else {
    // ถ้าเปิดไฟลืไม่สำเร็จ ให้แสดง error
    Serial.println("error opening LOG.txt");
    
  }
  // เปิดไฟล์เพื่ออ่าน


 
  // Wait one second before repeating :)

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)


  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.print(F("°F  Heat index: "));
  Serial.print(hic);
  Serial.print(F("°C "));
  Serial.print(hif);
  Serial.println(F("°F"));

   previousMillis = currentMillis;
  
  }
  unsigned long progress = millis() - fadeStartTime;
  // save the last time you blinked the LED

  if (progress <= 900) {
    long brightness = map(progress, 0, 900, 0, 255);
    analogWrite(led, brightness);

  }
  else if ((progress >= 900) && (progress <= 1400)) {
    long brightness = 255 - map(progress, 0, 900, 0, 255);
    analogWrite(led, brightness);
  }
  else {
    fadeStartTime = millis(); // restart fade again
  }
}



void workmode() {



  unsigned long currentMillis1 = millis();

  unsigned long currentMillis2 = millis();
  if (currentMillis1 - previousMillis1 >= 500) {
    if (currentMillis2 - previousMillis2 >= 5000) {
      // save the last time you blinked the LED

      // if the LED is off turn it on and vice-versa:
      if (ledState == LOW) {
        ledState = HIGH;
        previousMillis1 = currentMillis1;

      } else {
        ledState = LOW;

        previousMillis2 = currentMillis2;
      }

      // set the LED with the ledState of the variable:
      digitalWrite(led, ledState);
    }
  }
}

void savemode() {


}
