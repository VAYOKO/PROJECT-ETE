#include <SPI.h>
#include <SD.h>
#include <DHT.h>                              // รวม Library DHT ไว้ใน Project

DHT dht(2, DHT11);                           // กำหนด DHT Sensor ชื่อ dht ต่อกับ Pin 2 และเป็นเซ็นเซอร์ DHT22


float temp_c;
float temp_f;
float humidity;
unsigned long pre1 = 0;
unsigned long pre2 = 0;
unsigned long pre3 = 0;
unsigned long pre4 = 0;
unsigned long fadeStartTime;
int led = 6;
File Dlog; // สร้างออฟเจก File สำหรับจัดการข้อมูล
const int chipSelect = 53; // กำหนดขา CS ของโมดูล SD Card กับ Arduino ที่ขา 4

#include <Wire.h>
#include <SPI.h>  // not used here, but needed to prevent a RTClib compile error
#include "RTClib.h"

RTC_DS1307 RTC;     // Setup an instance of DS1307 naming it RTC

void setup () {

  Serial.begin(115200); // Set serial port speed
  Wire.begin(); // Start the I2C
  RTC.begin();  // Init RTC
  RTC.adjust(DateTime(__DATE__, __TIME__));  // Time and date is expanded to date and time on your computer at compiletime
  //Serial.print('Time and date set');
  dht.begin();

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




void loop () {


  unsigned long cur1 = millis();

  if (cur1 - pre1 >= 1000) {
    // save the last time you blinked the LED
    DateTime now = RTC.now();

    temp_c = dht.readTemperature();         // คำสั่ง readTemperature เป็นคำสั่งอ่านค่าอุณหภูมิในหน่วยองศาเซลเซียส
    temp_f = dht.readTemperature(true);     // หากต้องการค่าอุณหภูมิในหน่วยองศาฟาเรนไฮต์ให้ใส่ true ลงไปในวงเล็บของคำสั่ง
    humidity = dht.readHumidity();          // คำสั่ง readHumidity เป็นคำสั่งอ่านค่าความชื้นในอากาศเป็นเปอร์เซ็นต์

    Dlog = SD.open("test.txt", FILE_WRITE); // เปิดไฟล์ที่ชื่อ test.txt เพื่อเขียนข้อมูล โหมด FILE_WRITE
    // ถ้าเปิดไฟล์สำเร็จ ให้เขียนข้อมูลเพิ่มลงไป
    if (Dlog) {


      Dlog.print("Temperature is ");
      Dlog.print(temp_c);
      Dlog.print(" C : : ");
      Dlog.print(temp_f);
      Dlog.print(" F >> Humidity ");
      Dlog.print(humidity);
      Dlog.print(" %");

      Dlog.print("   ");
      Dlog.print(now.year()); // สั่งให้เขียนข้อมูล
      Dlog.print('/'); // สั่งให้เขียนข้อมูล
      Dlog.print(now.month()); // สั่งให้เขียนข้อมูล
      Dlog.print('/'); // สั่งให้เขียนข้อมูล
      Dlog.print(now.day()); // สั่งให้เขียนข้อมูล
      Dlog.print(' ' ); // สั่งให้เขียนข้อมูล
      Dlog.print(now.hour()); // สั่งให้เขียนข้อมูล
      Dlog.print(':');// สั่งให้เขียนข้อมูล
      Dlog.print(now.minute()); // สั่งให้เขียนข้อมูล
      Dlog.print(':');// สั่งให้เขียนข้อมูล
      Dlog.println(now.second()); // สั่งให้เขียนข้อมูล




      Serial.print("Temperature is ");
      Serial.print(temp_c);
      Serial.print(" C : : ");
      Serial.print(temp_f);
      Serial.print(" F >> Humidity ");
      Serial.print(humidity);
      Serial.print(" %");
      Serial.print(now.year()); // สั่งให้เขียนข้อมูล
      Serial.print('/'); // สั่งให้เขียนข้อมูล
      Serial.print(now.month()); // สั่งให้เขียนข้อมูล
      Serial.print('/'); // สั่งให้เขียนข้อมูล
      Serial.print(now.day()); // สั่งให้เขียนข้อมูล
      Serial.print(' ' ); // สั่งให้เขียนข้อมูล
      Serial.print(now.hour()); // สั่งให้เขียนข้อมูล
      Serial.print(':');// สั่งให้เขียนข้อมูล
      Serial.print(now.minute()); // สั่งให้เขียนข้อมูล
      Serial.print(':');// สั่งให้เขียนข้อมูล
      Serial.println(now.second()); // สั่งให้เขียนข้อมูล


      Dlog.close(); // ปิดไฟล์
      Serial.println("done.");
    }

    pre1 = cur1;
  }
   unsigned long progress = millis() - fadeStartTime;
  // save the last time you blinked the LED

  if (progress <= 600) {
    long brightness = map(progress, 0, 600, 0, 255);
    analogWrite(led, brightness);

  }
  else if ((progress >= 600) && (progress <= 1100)) {
    long brightness = 255 - map(progress, 0, 600, 0, 255);
    analogWrite(led, brightness);
  }
  else {
    fadeStartTime = millis(); // restart fade again
  }
}
