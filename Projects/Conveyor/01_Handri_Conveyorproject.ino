#include <NewPing.h>
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo1;
Servo servo2;
#define trigPin 9
#define echoPin 8
#define MAX_DISTANCE 200

NewPing sonar(trigPin, echoPin, MAX_DISTANCE);


int nilaitombol;
int countertombol=0;
//long jarak;
int detectultra;
int val1;
long duration, distance;
int count = 0;
int jer=0;
int app=0;



void setup() {
pinMode(13,INPUT);//pushbutton
pinMode(2,OUTPUT);//motor
pinMode(4,INPUT);//IR1
pinMode(12,OUTPUT);//Buzzer
pinMode(trigPin,OUTPUT);//trigpin
pinMode(echoPin,INPUT);//echopin


servo1.attach(10);
servo2.attach(11);

Serial.begin(9600);
servo1.write(105);
servo2.write(93);

  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("     ORANGE    ");
  lcd.setCursor(0,1);
  lcd.print("SORTING CONVEYER ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("PLEASE PUSH");
  lcd.setCursor(0,1);
  lcd.print("START BUTTON");

}

void loop() {
  // put your main code here, to run repeatedly:
 pushbutton();
 IR1(); 
 bacaultra();

}

void bacaultra(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1;
  delay (500);
  Serial.println(distance);
  
  if(distance>=6 && distance <9)
  {
   servo1.write(45);
   delay(3500);
   servo1.write(105);
   jer++;
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("Jumlah Jeruk =");
   lcd.print(count);
   lcd.setCursor(0,1);
   lcd.print("Besar=");
   lcd.print(app);
   lcd.print(" Kecil=");
   lcd.print(jer);
  }
  else if(distance<=5)
  {
   servo2.write(35);
   delay(4500);
   servo2.write(93);
    app++;
       lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Jumlah Jeruk =");
    lcd.print(count);
   lcd.setCursor(0,1);
   lcd.print("Besar=");
    lcd.print(app);
    lcd.print(" Kecil=");
    lcd.print(jer);
  }
}

void pushbutton()
{
  nilaitombol= digitalRead(13);
  if(nilaitombol == 1)
  {
    
  countertombol++;
  delay(250);
  if(countertombol == 1)
  {
  count=0;
  jer=0;
  app=0;
  digitalWrite(2, HIGH);
  Serial.println("logic on");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    CONVEYER    ");
  lcd.setCursor(0,1);
  lcd.print("       ON");
  }
  else if(countertombol == 2){
  Serial.println("logic off");
  digitalWrite(2, LOW);
  countertombol=0;
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("    CONVEYER    ");
  lcd.setCursor(0,1);
  lcd.print("      OFF");
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
  int val2=digitalRead(4);
  if (val2==LOW)
  {
   Serial.println("ADA HAMBATAN");
   delay(300);
   digitalWrite(2,LOW);
   digitalWrite(12,HIGH);
   delay(300);
   digitalWrite(2,HIGH);
   digitalWrite(12,LOW);
   
   
   count++;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Jumlah Jeruk=");
    lcd.print(count);
    lcd.setCursor(0,1);
   lcd.print("Besar=");
    lcd.print(app);
    lcd.print(" Kecil=");
    lcd.print(jer);
    
  }
  else
  {
   digitalWrite(12,LOW);
  }
}
