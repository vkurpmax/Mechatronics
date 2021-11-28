#include <Servo.h>
Servo servo1;
#define trigPin 9
#define echoPin 8

int nilaitombol;
int countertombol=0;
int count = 0;
int jer=0;
int app=0;

void setup() {
  // put your setup code here, to run once:
  pinMode(13,INPUT);//pushbutton
  pinMode(2,OUTPUT);//motor
  pinMode(trigPin,OUTPUT);//trigpin
  pinMode(echoPin,INPUT);//echopin
  
  servo1.attach(10);

  Serial.begin(9600);
  servo1.write(105);
}

void loop() {
  // put your main code here, to run repeatedly:
  pushbutton();
}

void pushbutton()
{
  digitalWrite(2, HIGH);
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
  digitalWrite(4, LOW);
  Serial.println("logic on");
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("    CONVEYER    ");
//  lcd.setCursor(0,1);
//  lcd.print("       ON");
  }
  else if(countertombol == 2){
  Serial.println("logic off");
  digitalWrite(2, LOW);
  countertombol=0;
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("    CONVEYER    ");
//  lcd.setCursor(0,1);
//  lcd.print("      OFF");
  delay(3000);
//  lcd.clear();
//  lcd.setCursor(0,0);
//  lcd.print("  PLEASE  PUSH  ");
//  lcd.setCursor(0,1);
//  lcd.print("  START BUTTON  ");
  }
  }
}
