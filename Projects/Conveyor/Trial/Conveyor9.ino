#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo servo1;
Servo servo2;

#define trigPin 13                                // D7 NodeMCU ESP8266
#define echoPin 0                                 // D3 NodeMCU ESP8266
#define MAX_DISTANCE 200
#define BLYNK_PRINT Serial

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

int IN4 = 15;                                      // D4 NodeMCU ESP8266
const int tombol = 2;                            // D8 NodeMCU ESP8266
// int nilaitombol;
int countertombol = 0;
int count = 0;                                    // Jumlah Jeruk
int countkecil = 0;
int countbesar = 0;
long duration;
int distance;
int val2;

char auth[] = "D2z26gaorTO98bRkWelsW-mheQCpFkXx";
char ssid[] = "Vkurpmax";
char pass[] = "lumos maxima";

BlynkTimer timer;

void myTimerEvent()
{
  Blynk.virtualWrite(V1,distance);
  Blynk.virtualWrite(V2,count);
  Blynk.virtualWrite(V3,countkecil);
  Blynk.virtualWrite(V4,countbesar);
}

void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);

  pinMode(IN4, OUTPUT);
  pinMode(tombol, INPUT_PULLUP);  // D8 Pushbutton
  // pinMode(14,INPUT);//D5 pushbutton
  pinMode(16, INPUT);//D5 pushbutton
  pinMode(trigPin,OUTPUT);//trigpin
  pinMode(echoPin,INPUT);//echopin

  servo1.attach(12);// d6 node
  servo2.attach(14);                              // D5 NodeMCU ESP8266

  servo1.write(105);
  servo2.write(93);

  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("     ORANGE    ");
  lcd.setCursor(0,1);
  lcd.print("SORTING CONVEYOR");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  PLEASE PUSH  ");
  lcd.setCursor(0,1);
  lcd.print("  START BUTTON  ");
}

void loop()
{ 
  Blynk.run();
  timer.run();
  pushbutton();
  IR1();
  bacaultra();
}

void pushbutton()
{
  if (digitalRead(tombol) == LOW)
  {
    countertombol++;
    delay(500);
    if (countertombol == 1)
    { 
      digitalWrite(IN4, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    CONVEYOR    ");
      lcd.setCursor(0,1);
      lcd.print("       ON       ");
    }
    if (countertombol == 2)
    { 
      digitalWrite(IN4, LOW);
      servo1.write(105);
      servo2.write(93);
      countertombol = 0;
      count = 0;
      countkecil = 0;
      countbesar = 0;

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    CONVEYOR    ");
      lcd.setCursor(0,1);
      lcd.print("      OFF");
      delay(3000);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("     THANK     ");
      lcd.setCursor(0,1);
      lcd.print("      YOU      ");
      delay(3000);

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("  PLEASE  PUSH  ");
      lcd.setCursor(0,1);
      lcd.print("  START BUTTON  ");
    }
  }
}

void IR1()
{
  val2 = digitalRead(16);
  if (val2 == LOW && countertombol == 1)
  {
    count++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Jumlah Jeruk =");
    lcd.print(count);
    lcd.setCursor(0,1);
    lcd.print("Besar=");
    lcd.print(countbesar);
    lcd.print(" Kecil=");
    lcd.print(countkecil);
    
//   Serial.println("ADA HAMBATAN");
 //  delay(100);
   //digitalWrite(2,LOW);
    
    digitalWrite(IN4,LOW);//motor off
    delay(1000);
  // digitalWrite(2,HIGH);
    digitalWrite(IN4,HIGH);//motor on 
  }
  //else
 // {
 //  digitalWrite(12,LOW);
//  }
}

void bacaultra(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  delay (300);
  Serial.println(distance);
  
  if(distance>=6 && distance <9 && countertombol == 1)
  {
 
   countkecil++;
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Jumlah Jeruk =");
   lcd.print(count);
   lcd.setCursor(0,1);
   lcd.print("Besar=");
   lcd.print(countbesar);
   lcd.print(" Kecil=");
   lcd.print(countkecil);

   digitalWrite(IN4,LOW);//motor off
   delay(1000);
   digitalWrite(IN4,HIGH);
   servo1.write(45);
   delay(3500);
   servo1.write(105);
  }
   if(distance<=5 && distance>=1 &&countertombol == 1)
  {
    countbesar++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Jumlah Jeruk =");
    lcd.print(count);
    lcd.setCursor(0,1);
    lcd.print("Besar=");
    lcd.print(countbesar);
    lcd.print(" Kecil=");
    lcd.print(countkecil);

   digitalWrite(IN4,LOW);//motor off
   delay(1000);
   digitalWrite(IN4,HIGH);
   servo2.write(35);
   delay(4500);
   servo2.write(93);
  }
  
}
