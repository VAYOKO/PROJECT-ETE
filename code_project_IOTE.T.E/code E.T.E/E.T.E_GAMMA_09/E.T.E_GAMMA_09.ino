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
void beep1(void);
void beep2(void);
void beep3(void);
void beep4(void);
void beep5(void);
void beep6(void);

void flue(void);
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
char ssid[] = "aisfibre,A30";
char pass[] = "s0897773889,ae246532";
char auth[] = "8gNuKSQ67E-UlPdznPuFh7u8sRAJfPiP";
void soilDetect(void);
void gasDetect(void);
void rainDetect(void);
#include <Servo.h>

Servo servo;
int buz = 14;
void setup()
{
  servo.attach(15); // NodeMCU D8 pin
  pinMode(led, OUTPUT);
  pinMode(led, INPUT);
  pinMode(rain, INPUT_PULLUP);
  pinMode(Gas, INPUT);
  pinMode(soil, INPUT_PULLUP);
  pinMode(buz, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  // initialize with the I2C addr 0x3C
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  // Clear the buffer.
  display.clearDisplay();
  static unsigned long time6 = millis();
  if ((millis() - time6) > 1500) {
    time6 = millis();
    // Display Text
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("Hello world!");
    display. display();
    time6 = millis();
    display.clearDisplay();

    // Display Inverted Text
    display.setTextColor(BLACK, WHITE); // 'inverted' text
    display.setCursor(0, 0);
    display.println("Hello world!");
    display.display();
    time6 = millis();
    display.clearDisplay();

    // Changing Font Size
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Hello!");
    display.display();
    time6 = millis();
    display.clearDisplay();
    // Display ASCII Characters
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.write(3);
    display.display();
    time6 = millis();
    display.clearDisplay();

    // Scroll full screen
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("Full");
    display.println("screen");
    display.println("scrolling!");
    display.display();

    time6 = millis();


    display.clearDisplay();

    // Scroll part of the screen
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("E.T.E");
    display.println("porject of");
    display.setTextSize(1);
    display.println("<<ATOM>>");
    display.display();
    display.startscrollright(0x00, 0x00);
    time6 = millis();
    display.stopscroll();
    display.clearDisplay();
    beep5();

    beep6();
  }
}
void loop() {

  ldr1();
  static unsigned long time1 = millis();
  static unsigned long time2 = millis();
  if ((millis() - time1) > 5000) {
    time1 = millis();

    led8.on();

    digitalWrite(led, HIGH);
  }
  else {
    if ((millis() - time2) > 400) {
      time2 = millis();

      digitalWrite(led, LOW);
      led8.off();
    }
  }
  if (Blynk.connected()) {
    Blynk.run();
    led5.on(); display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("ONLINE");
    display.display();


  }
  else {
    led5.off();
  }
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("OFFLINE");
  display.display();
  gasDetect();
  rainDetect();
  soilDetect();
}
void gasDetect(void) {
  static unsigned long time10 = millis();
  if ((millis() - time10) > 500) {
    time10 = millis();
    if (analogRead(Gas) > 100) {
      led4.on(); 
    }
  }
}
  void rainDetect(void) {


    static unsigned long time10 = millis();
    if ((millis() - time10) > 500) {
      time10 = millis();
      if (digitalRead(rain) == LOW) {
        time10 = millis();

        Serial.println("Rain");
        led3.on();
        servo.write(180);
      }
      else {
        led3.off();
        servo.write(0);
      }
    }
  }

  void soilDetect(void) {
    static unsigned long time20 = millis();
    if ((millis() - time20) > 500) {
      time20 = millis();
      if (digitalRead(soil) == HIGH) {
        led6.on();
      }
      else {
        led6.off();
      }

    }
  }
  void soilrain(void) {
    static unsigned long time21 = millis();
    if ((millis() - time21) > 500) {
      time21 = millis();
    }
    if (digitalRead(rain) == HIGH) {
      led7.on();
      Blynk.virtualWrite(V30, "flue close ปิดช่องลม");

      servo.write(180);
      time21 = millis();
    }
    else {


      Blynk.virtualWrite(V30, "flue open");
      servo.write(0);
      time21 = millis();
      led7.off();


    }
  }
  void info2(void) {
    display.clearDisplay();

    Blynk.virtualWrite(V30, "");
    Blynk.virtualWrite(V30, "");
    Blynk.virtualWrite(V30, "");
  }
  void info1(void) {

    static unsigned long time3 = millis();
    if ((millis() - time3) > 5000) {

      time3 = millis();

      // Scroll part of the screen
      display.setCursor(0, 0);
      display.setTextSize(1);
      display.println("E.T.E");
      display.println("porject of");
      display.setTextSize(1);
      display.println("<<ATOM>>");
      display.display();
      time3 = millis();
      display.stopscroll();
      display.clearDisplay();
      digitalRead(rain);
      digitalRead(soil);
      Blynk.virtualWrite(D6, rain);
      Blynk.virtualWrite(D7, soil);

      Blynk.virtualWrite(V30, "ssid:", ssid);
      Blynk.virtualWrite(V30, "password:", pass);
      Blynk.virtualWrite(V30, "ssid:", ssid);

      if (Blynk.connected()) {
        Blynk.virtualWrite(V30, "connected");
      }
    }
  }



  BLYNK_WRITE(V40)
  {
    info1();
    Blynk.virtualWrite(V30, "Enable funtion auto working...");
  }




  void ldr1(void) {
    static unsigned long time7 = millis();
    if ((millis() - time7) > 5000) {
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
  void flue(void) {
    static unsigned long time11 = millis();
    if ((millis() - time11) > 500) {
      time11 = millis();
      if (digitalRead(rain) == HIGH) {
        Blynk.virtualWrite(V30, "flue close ปิดช่องลม");
        time11 = millis();
        servo.write(180);
        led7.on();
      }

      else {

        Blynk.virtualWrite(V30, "flue open");
        servo.write(0);
        led7.off();
      }
    }
  }






  void beep1(void) {
    static unsigned long time12 = millis();
    if ((millis() - time12) > 500) {
      time12 = millis();
      tone(buz, 5);
      time12 = millis();
      tone(buz, 10);
      time12 = millis();
      tone(buz, 15);
      time12 = millis();

    }
  }
  void beep2 (void) {
    static unsigned long time13 = millis();
    if ((millis() - time13) > 200) {
      time13 = millis();
      tone(buz, 5);
      time13 = millis();
      tone(buz, 5);
      time13 = millis();
      tone(buz, 5);
      time13 = millis();
      tone(buz, 5);
      time13 = millis();


    }
  }
  void beep3(void) {
    static unsigned long time14 = millis();
    if ((millis() - time14) > 200) {
      time14 = millis();
      tone(buz, 5);
      time14 = millis();
      tone(buz, 15);
      time14 = millis();
      tone(buz, 5);
      time14 = millis();
      tone(buz, 15);
      time14 = millis();
    }
  }
  void beep4 (void) {
    static unsigned long time15 = millis();
    if ((millis() - time15) > 200) {
      time15 = millis();
      tone(buz, 5);
      time15 = millis();
      tone(buz, 5);
      time15 = millis();
      tone(buz, 5);
      time15 = millis();
      tone(buz, 5);
      time15 = millis();
    }
  }
  void beep5 (void) {
    static unsigned long time15 = millis();
    if ((millis() - time15) > 400) {
      time15 = millis();
      tone(buz, 5);

    }
  }
  void beep6 (void) {
    static unsigned long time15 = millis();
    if ((millis() - time15) > 400) {
      time15 = millis();
      tone(buz, 5);
      time15 = millis();
      tone(buz, 10);
      time15 = millis();
      tone(buz, 15);
    }
  }

  /*
     #define BLYNK_PRINT Serial
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

    == Blynk.run();
    -
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



























    โครงงานวิทยาศาสตร์
    โรงเรียนลาซาลกรุงเทพ
    เรื่อง Explore the environment (สำรวจสิ่งแวดล้อม)
    จัดทำโดย
    1.ด.ช.วาริส วิภาวนิช  (Varis Vipavanich)
    2.นาย อัครินทร์ พัฒนาเลิศกิตติ (Akarin Pattanalerdkit)
    3.ด.ช.สัณห์พิชญ์ โมวังหาร  (Sanphit Mowanghan)




    ครูที่ปรึกษา
    นางสาว อัคณา กิล
    นางสาว เบญญาภา ประเสรฐพงษ์
    นาย คมณัษฐ์ แซ่เฮ้ง




    ชื่อโครงงาน : Explore the environment(E.T.E)
    ประเภท : โครงงานวิทยาศาสตร์ประเภทสิ่งประดิษฐ์
    บทคัดย่อ
    การสร้างสิ่งประดิษฐ์ชิ้นนี้ใช้เวลาสร้างป็นเวลา 2ปี โดยมีจุดประสงค์เพื่อสำรวจความเปลี่ยนแปลงและปรากฏการณ์ต่างๆ และใช้พลังงานสะอาดเป็นมิตรต่อสิ่งแวดล้อมโดยใช้พลังงานจากsolar cell และติดต่อผ่านทาง ระบบ IOT (Internet of things) เข้าทางโทรศัพท์









    .


    กิตติกรรมประกาศ
         โครงงานสามารถบรรลุผลสำเร็จได้ดี ด้วยความร่วมมือ จาก
    ผู้ปกครอง คุณครู และเพื่อนๆ ผู้จัดทำขอขอบพระคุณ ผู้มีส่วนร่วมทุกคน ที่ช่วยในการร่วมทำจัดประกอบโปรแกรม
       คณะผู้จัดทำ












    สารบัญ
    บทคัดย่อ                                  ก
    กิตติกรรมประกาศ                    ข
    คำนำ                                       ค
    ความเป็นมา                             1
         วัตถุประสงค์                      2
    ประโยชน์ที่คาดว่าจะได้รับ
    สมมุติฐาน
    เอกสารเกี่ยวข้อง                      3
    การดำเนินงาน                         12
    ผลการดำเนินงาน                     15
    สรุป อภิปราย                          16
    สรุปผลการทดลอง
    อภิปรายผลการทดลอง
    ประโยชน์ที่ได้รับ
    ข้อเสนอแนะ
    บรรณานุกรม                           17
    ภาคผนวก                               18

    ที่มาของโครงงาน
    การเกิดปรากฏการณ์ธรรมชาติ
      ในหลายๆ ด้านแล้ว กล่าวได้ว่าธรรมชาติและมนุษย์มีหลายอย่างที่ขัดแย้งกัน บางคนมองธรรมชาติว่าเป็นเพียงทรัพยากรธรรมชาติที่เอามาเป็นประโยชน์ต่อ มนุษย์เท่านั้น มนุษย์ตัดต้นไม้เพื่อนำไม้ไปเป็นเชื้อเพลิงหรือนำไปสร้างบ้าน หรือเพื่อนำที่ดินไปทำสวน ปลูกผัก หรือสร้างรถ และโรงงานอุตสาหกรรม ซึ่งปล่อยควันเสีย โดยเฉพาะในเมือง หรือการที่มนุษย์จับปลาอย่างมากมายโดยฆ่าทั้งปลาและทำอันตรายต่อสัตว์อื่นๆ ใต้น้ำ ในขณะที่บางคนเลือกที่จะไม่ทำร้ายธรรมชาติ เพราะพวกเขารู้สึกว่าธรรมชาติมีความจำเป็นต่อพวกเขา พวกเขาจึงพยายามทำสิ่งที่ไม่มีผลกระทบต่อธรรมชาติ โดยเฉพาะในเมืองใหญ่ที่มีผู้คนมากมาย ปัญหาธรรมชาติจึงเป็นปัญหาที่ร้ายแรง และกลายเป็นเรื่องการเมืองไปเสียแล้ว มีบางคนคิดว่าอนาคตนี้มนุษย์ จะไม่ต้องการธรรมชาติ และฉลาดพอที่จะสร้างสิ่งต่างๆ ทดแทนธรรมชาติได้ แต่อันที่จริงแล้ว มนุษย์เองก็เกิดจากธรรมชาติและธรรมชาติก็สร้างมนุษย์ มนุษย์เป็นสัตว์ชนิดเดียวที่มีสมองอันชาญฉลาด มีความสามารถที่จะปกป้องธรรมชาติจากอันตราย และช่วยเหลือสิ่งมีชีวิตชนิดอื่นได้ หากธรรมชาติเสื่อมโทรมลงไป มนุษย์อาจจะต้องอยู่อย่างลำบากมากขึ้น นี่จึงเป็นเหตุผลที่เราควรจะดูแลรักษาธรรมชาติ ธรรมชาติสามารถแสดงให้มนุษย์เห็นว่าจะทำสิ่งต่างๆ ได้อย่างไร และมนุษย์ศึกษาธรรมชาติ เพื่อที่จะเข้าใจและแก้ปัญหาต่างๆ ได้อย่างถูกต้อง คณะผู้จัดทำจึง
    คิดสร้างสิ่งประดิษฐ์เพื่อสำรวจความเปลี่ยนแปลงต่างๆ
    วัตถุประสงค์
    1.เพื่อสำรวจการเปลี่ยนแปลงทางธรรมชาติ
    2.เพื่อให้ผู้ศึกษาเข้าใจถึงระบบ IOT
    3.เพื่อให้มนุษย์ตระหนักถึงธรรมชาติ


    ประโยชน์ที่คาดว่าจะได้รับ
    1.รู้ถึงระบบIOT SSID
    2.ตระหนักถึงธรรมชาติที่เปลี่ยนไป
    3.สำรวจสิ่งแวดล้อมและนำมาวิเคราะห์

    สมมุติฐาน
    1.Sersor และระบบต่างๆทำงานได้ด้วยดี
    2.ระบบไม่ขัดข้องหรือขัดข้องน้อยที่สุด






    เอกสารเกี่ยวข้อง  และอุปกรณ์
    NodeMCU
    คำอธิบาย
    แปลจากภาษาอังกฤษ-NodeMCU เป็นแพลตฟอร์มโอเพ่นซอร์ส IoT ซึ่งประกอบด้วยเฟิร์มแวร์ซึ่งทำงานบน ESP-8266 Wi-Fi SoC จาก Espressif Systems และฮาร์ดแวร์ซึ่งอิงกับโมดูล ESP-12 คำว่า "NodeMCU" โดยค่าเริ่มต้นหมายถึงเฟิร์มแวร์มากกว่าชุดพัฒนา เฟิร์มแวร์ใช้ภาษาสคริปต์ Lua โดยอิงตามโครงการ eLua และสร้างขึ้นบน Espressif Non-OS SDK สำหรับ ESP8266 ...




    โมดูลควบคุม






    MQ2 เซ็นเซอร์โมดูล เหมาะสำหรับใช้ตรวจจับแก๊สจำพวก LPG, Propane, Hydrogen, Methane, Butane, Smoke สามารถตรวจจับได้ระดับความเข้มข้นของแก๊สที่ช่วง 300 - 10,000 ppm

    โดยหลักการทำงานของ MQ2 มีดังนี้

    Sensitive material of MQ-2 gas sensor is SnO2, which with lower conductivity in clean air. When the target combustible gas exist, The sensor’s conductivity is more higher along with the gas concentration rising. The circuit on the module converts change of conductivity to correspond output signal of gas concentration.

    MQ-2 gas sensor has high sensitity to LPG, Propane and Hydrogen, also could be used to Methane and other combustible steam, it is with low cost and suitable for different application.


    Soil Moisture Sensor Module
    ใช้งานเพื่อการวัดความชื่นในดิน โดยการวัดค่าความต้านทานระหว่างอิเล็กโทรดที่ชุบโลหะอย่างดีเพื่อป้องกันการเกิดออกซิเดชั่น เพิ่มอายุการใช้งานและลดการสึกหรอเนื่องจากความชื้น  เหมาะสมกับการใช้งานเพื่อการทำระบบรดน้ำอัตโนมัติ




    500MA mini solar lithium battery charging board MINI charging module

    This is a super mini solar Lipo charger based on a single lithium battery charge management chip CN3065.
    This solar charger allows you to get the most possible power from a solar panel or other photovoltaic device and into a rechargeable LiPo battery. The setup is also very easy, just plug the solar panel into one side of the solar charger and plug the battery into the other side and you can start charging!
    The output of the solar charger is designed to charge a single polymer lithium-ion battery. The load should be in parallel with the battery. By default, solar charging is set to a maximum charging current of 500 mA and the maximum recommended input is 6V (minimum 4.4V). It is recommended that the battery be charged not to exceed the rated capacity.


    ถ่านชาร์จ Li-ion 18650 ยี่ห้อ LG รุ่น LGDBHG21865 LG HG2 ความจุเต็ม 3000mAh จ่ายกระแสสูงสุด 20A จำนวน 1 ก้อน
    รายละเอียด:
    • แบรนด์: LG
    • รุ่น: INR18650-HG2
    • รูปแบบ: 18650
    • ประเภท: Li(NiMnCo)O2
    • สามารถชาร์จซ้ำได้ถึง 500 ครั้ง
    • ความจุปกติ: 3000mAh / 11.1Wh
    • ต่ำสุด: 2900mAh
    • แรงดันไฟฟ้า: การชาร์จไฟ: 4.2 ± 0.03V
    • มาตรฐาน: 3.7V
    • แรงดันไฟฟ้าเมื่อชาร์จเต็ม และไม่มีแบตตามลำดับ 4.2V & 2.7V respectively
    • วิธีการชาร์จ: CC-CV (แรงดันไฟฟ้าคงที่และกระแสไฟ จำกัด )
    • การชาร์จกระแสไฟฟ้า ชาร์จช้า: 500mAh, 4.2V | 50mA กระแสไฟท้าย
    • ค่ามาตรฐาน: 1500mA, 4.2V | 50mA กระแสไฟท้าย
    • Rapid Charge (MAX.): 4000mA, 4.2V | 100mA สิ้นสุดในปัจจุบัน
    • เวลาในการชาร์จ: Slow Charge: 387 นาที / 6.45 ชั่วโมง
    • ค่ามาตรฐาน: 147 นาที / 2.45 ชั่วโมง
    • Rapid Charge: 72 นาที / 1.2 ชั่วโมง
    • สูงสุด กระแสไฟในการคายประจุ: ต่อเนื่อง: กระแสคงที่ 20A
    • Peak: 30A โหลดกระแสไฟฟ้า
    • แนะนำ: กระแสคงที่ 3A
    • อุณหภูมิในการทำงาน: ชาร์จ: 0 ถึง 50 ° C
    • การคายประจุ: -20 ถึง 75 ° C
    • อุณหภูมิในการจัดเก็บ: 1 ปี: -20 ~ 25 ° C
    • 3 เดือน: -20 ~ 45 ° C
    • 1 เดือน: -20 ~ 60 ° C
    • น้ำหนัก: 45g / pc
    • ขนาด: Ø 18.5 มม. x 65 มม. Ø 1.85 ซม. x 6.5 ซม

    Features :
    • High sensitivity, rapid response.
    • Compact structure, easy installation, good water resistance.
    • The use of wide temperature range, good stability, high reliability.
    • Can provide different R, B value of products, interchangeable, high precision.

    Specification :
    • Type: Humidity Sensor
    • Material: Mixture
    • Material Crystal structure: Polycrystallinef
    • Usage: Temperature Sensor
    • Theory: Resistance Sensor
    • Output: Analog Sensor
    • 10K 1% accuracy: High temperature type
    • Resistance accuracy: ± 1%, ± 2%, ± 3%
    • The use of temperature range: -40 ℃ to +300 ℃
    • The maximum rated power: 45mW
    • Thermal time constant: ≤3S (static air)
    • Resistance temperature coefficient: -2 to -5% / ℃
    • Insulation performance: 500V
    • DC test a single root insulation resistance: ≥ 100MΩ







    ขั้นตอนการประกอบ
    1.นำsensorต่างมาบักกรีเพื่อเพี่มความยาวสายไฟ
    2.นำมาติดตั้ง
    3.นำระบบ powersupply มาติดตั้ง
    4.ติดตั้ง solarcell









    ผลการทดลอง
    สถนะปกติ













    สถานะฝนตก


       สถานะมีน้ำในดิน

      สถานะพบgasหรือ ควัน

    สรุป
    จากการทดลองบงชี้ได้ว่าเครื่องสามารถทำงานได้ดี แม้ไม่มีคนคอยเฝ้า สามารถใช้ได้ในเวลากลางวันตลอด 12 ช.ม.
    ตอนกลางคืนใช้ได้ 2-3ช.ม และจะเรี่มทงานใหม่ในว้นรุ่งขึ้นเมือมีแสงแดด












    บรรณานุกรม
    https://www.arduinoall.com/?gclid=Cj0KCQjw-b7qBRDPARIsADVbUbXkBEsURK_KnQ6Smfcsbw2LfZDFdvGx8Ma-1pMQoCfrF09ZUJQfJYUaAspDEALw_wcB

    https://www.arduino.cc/


    https://github.com/github











    ภาคผนวก
















    จัทำโดย





    E.T.E V.1-3










    E.T.EV.3-5







    code token

    TwUmaWGdvU9Qzasce8o0YvF3NFopl5-b

    Astnv8XSBJ3jL1MSOqjac0jm9JgB2cna

    Y6JVjptaJZlY7bza71WaPbsgJ7Nzql7c

    EKSYwkQxbwusqN5K_4ua4HVeSypmaBu9

    Tx07n9HuWYokKZTHhaUVge5P-LRyvyQ-

    BFo0sqaiMF2lNGESAf4rTxYNsC4lp0Jw

    8gNuKSQ67E-UlPdznPuFh7u8sRAJfPiP











     GPIO5  D1 LED
     GPIO4  D2 FLM
     GPIO14 D5 soil
     GPIO12 D6 rain
     GPIO13 D7 GAS


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
    }z
    BLYNK_WRITE(V3)
    {
    servo.write(180);
    }
  */
