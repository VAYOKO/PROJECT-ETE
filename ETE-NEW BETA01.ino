//Varis Vipavanich
#include <DS1307RTC.h>
#include <TimeLib.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>

#include "DHT.h"
#include <Adafruit_Sensor.h>

#define DHTPIN 2 

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
File myFile;
const int chipSelect = 10;

String time ;
tmElements_t tm;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
   Serial.println(F("DHTxx test!"));
pinMode(13,OUTPUT);
pinMode(12 ,OUTPUT);
  dht.begin();
  Serial.begin(9600);
  while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DataLogger Shield Test");
  pinMode(SS, OUTPUT);

  if (!SD.begin(chipSelect)) {
    Serial.println("SD Card initialization failed!");
    return;  
  }
  Serial.println("SD Card OK.");
  ReadText();
  digitalWrite(13,HIGH);
   digitalWrite(12,HIGH);
   delay(1000);
   digitalWrite(13,0);
   digitalWrite(12,0);
}

void loop() {
  
   float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);
  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);
 
 time = Now()+("  ")+("Humidity :")+("  ")+(h)+("  ")+("Temperature :")+("  ")+(t);
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

// 
//  Serial.print(F("Humidity: "));
//  Serial.print(h);
//  Serial.print(F("%  Temperature: "));
//  Serial.print(t);
//  Serial.print(F("°C "));
//  Serial.print(f);
//  Serial.print(F("°F  Heat index: "));
//  Serial.print(hic);
//  Serial.print(F("°C "));
//  Serial.print(hif);
//  Serial.println(F("°F"));
// 
  Serial.println(time);
  WriteText(time);
  delay(3000);
}


void ReadText(){
  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
     digitalWrite(13,0);
      digitalWrite(12,1);
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    digitalWrite(13,1);
     digitalWrite(12,0);
  }
}

void WriteText(String txt){
  myFile = SD.open("test.txt", FILE_WRITE);
  if (myFile) {
    myFile.println(txt);
    myFile.close();
  } 
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}


String Now(){
  String time = "";
  if (RTC.read(tm)) {
    //    time = String(tm.Hour+":"+tm.Minute+":"+tm.Secnd+" DAY : "+tm.Day+"/"+tm.Month+"/"+tmYearToCalendar(tm.Year));
    time+=tm.Hour;
    time+=":";

    time+=tm.Minute;
    time+=":";

    time+=tm.Second;
     time+="     ";
    time+=tm.Day;
    time+="/";

    time+=tm.Month;
    time+="/";

    time+=tmYearToCalendar(tm.Year);
  } 
  else {
    time = "NO";
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } 
    else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
  }
  return time;
}
/*#include <DS1307RTC.h>
#include <TimeLib.h>
#include <Wire.h>

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

void setup() {
  bool parse=false;
  bool config=false;

  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);
  if (parse && config) {
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } else if (parse) {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } else {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }
}

void loop() {
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}
*/
