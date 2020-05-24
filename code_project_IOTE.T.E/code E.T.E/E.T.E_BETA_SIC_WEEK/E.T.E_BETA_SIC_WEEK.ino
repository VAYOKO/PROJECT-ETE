

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
WidgetLED led7(V7);
void soilDetect(void);
void gasDetect(void);
char ssid[] = "A30";
char pass[] = "ae246532";
char auth[] = "Tx07n9HuWYokKZTHhaUVge5P-LRyvyQ-";
void rainDetect(void);
void setup()
{
  pinMode(buz,OUTPUT);
pinMode(led,OUTPUT);

  pinMode(rain, INPUT);
  pinMode(Gas, INPUT);
  pinMode(soil, INPUT);

  Blynk.begin(auth, ssid, pass);

  
}
void loop() {
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
    void soilrain(void){
      if((digitalRead(soil)==HIGH&&digitalRead(rain)==HIGH)){
      led7.on();
      led3.off();
      led6.off();
      
    }
    else if(( digitalRead(soil)==HIGH&&digitalRead(rain)==LOW)){
       led6.on();
       led3.off();
       led7.off();
    }
    else  if((digitalRead(soil)==LOW&&digitalRead(rain)==HIGH)){
      led3.on();
      led6.off();
      led7.off();
    }
      
    }
    
