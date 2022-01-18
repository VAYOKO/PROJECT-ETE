#include "DS1302.h"
#include <Adafruit_Sensor.h>

int ledState = LOW;             // ledState used to set the LED

#define READ_TIME 1000 //ms
#define WIND_SENSOR_PIN 2 //wind sensor pin
#define WIND_SPEED_20_PULSE_SECOND 1.75  //in m/s this value depend on the sensor type
#define ONE_ROTATION_SENSOR 20.0

volatile unsigned long Rotations; //Cup rotation counter used in interrupt routine

float WindSpeed; //Speed meter per second

unsigned long gulStart_Read_Timer = 0;
#include "DHT.h"

#define DHTPIN 6// Digital pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 22  (AM2302), AM2321
DS1302 rtc(7, 3, 4);
#include <SPI.h>
#include <SD.h>
File LOG; // สร้างออฟเจก File สำหรับจัดการข้อมูล
// Generally, you should use "unsigned long" for variables that hold time
// The value will quickly become too large for an int to store
unsigned long fadeStartTime;
// constants won't change:
const long interval = 100;           // interval at which to blink (milliseconds)
unsigned long previousMillis1 = 0;        // will store last time LED was updated
unsigned long previousMillis2 = 0;        // will store last time LED was updated
const int chipSelect = 5; // กำหนดขา CS ของโมดูล SD Card กับ Arduino ที่ขา 4
int led = 9;
void clockdate()


{



  //  Serial.println(rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '/'));

  Serial.println(rtc.getDOWStr());

  Serial.println(rtc.getTimeStr());

}

DHT dht(DHTPIN, DHTTYPE);

void setup()

{
  pinMode(WIND_SENSOR_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(WIND_SENSOR_PIN), isr_rotation, CHANGE); //Set up the interrupt

  Serial.println("Rotations\tm/s");
  sei(); //Enables interrupts
  gulStart_Read_Timer - millis();
  dht.begin();

  pinMode(led, OUTPUT);
  fadeStartTime = millis();
  Serial.begin(9600);
  while (!Serial) {
  }
  Serial.print("Initializing SD card...");
  pinMode(SS, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");


  // ตั้งเวลาครั้งแรก เอา comment นี้ออก ถ้าตั้งเสร็จแล้ว comment นี้ไว้เพื้อให้เวลาเดินต่อ

  /*  rtc.halt(false);

      rtc.writeProtect(false);

      rtc.setDOW(WEDNESDAY);

      rtc.setTime(18, 33,00);

      rtc.setDate(18, 1, 2022);

      rtc.writeProtect(true);*/

}



void loop()

{
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
    //    LOG.println(rtc.getDateStr(FORMAT_LONG, FORMAT_LITTLEENDIAN, '/')); // สั่งให้เขียนข้อมูล
    workmode();
    LOG.print(rtc.getDOWStr());
    LOG.print(rtc.getTimeStr());
    LOG.print("  ");
    LOG.print(hic);
    LOG.print(" C ");
    LOG.print(h);
    LOG.print(" humi ");
    LOG.print("     ");
    LOG.print(Rotations);
    LOG.print("   \t\t  ");
    LOG.print(WindSpeed);
    LOG.print("  m/s ");
    LOG.close(); // ปิดไฟล์
    Serial.println("done.");
  } else {
    // ถ้าเปิดไฟลืไม่สำเร็จ ให้แสดง error
    Serial.println("error opening LOG.txt");
    savemode();
  }
  // เปิดไฟล์เพื่ออ่าน
  if ((millis() - gulStart_Read_Timer) >= READ_TIME)
  {
    cli(); //Disable interrupts

    //convert rotation to wind speed in m/s
    WindSpeed = WIND_SPEED_20_PULSE_SECOND / ONE_ROTATION_SENSOR * (float)Rotations;
    Serial.print(Rotations); Serial.print("\t\t");
    Serial.println(WindSpeed);

    sei(); //Enables interrupts

    Rotations = 0; //Set Rotations count to 0 ready for calculations
    gulStart_Read_Timer = millis();
  }


  clockdate();


  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)


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
  delay(1000);

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

void isr_rotation()
{
  Rotations++;
}
