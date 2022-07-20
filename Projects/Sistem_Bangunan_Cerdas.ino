/*
FIRE ALARM SYSTEM

LCD:    SDA : A4
        SCL : A5
Buzzer      : D2
PD1         : D4
PD2         : D3
*/

#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd (0x27, 16, 2);


int buzz = 2;
int pd1 = 4;
int pd2 = 3;

void setup() {
  // put your setup code here, to run once:
pinMode(pd1, INPUT);
pinMode(pd2, INPUT);
pinMode(buzz, OUTPUT);

lcd.begin();
lcd.clear();
lcd.setCursor(0,0);
lcd.print("   FIRE ALARM   ");
lcd.setCursor(0,1);
lcd.print("     SYSTEM     ");
delay(3000);

lcd.clear();
lcd.setCursor(0,0);
lcd.print("  NURUL UTAMI  ");
lcd.setCursor(0,1);
lcd.print(" PUTRI WANDINI ");
delay(3000);
lcd.clear();
lcd.setCursor(0,0);
lcd.print("    HASLINDA    ");
lcd.setCursor(0,1);
lcd.print("   PUTU HERDY   ");
delay(3000);

}

void loop() {
  // put your main code here, to run repeatedly:
  

  if (digitalRead(pd1)==LOW)
  {
    digitalWrite(buzz, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    FIRE !!!    ");
    lcd.setCursor(0,1);
    lcd.print("  FIRST FLOOR  ");
    delay(1000);
  }
  else if (digitalRead(pd2)==LOW)
  {
    digitalWrite(buzz, HIGH);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("    FIRE !!!    ");
    lcd.setCursor(0,1);
    lcd.print("  SECOND FLOOR ");
    delay(1000);
  }
  else
  {
    digitalWrite(buzz, LOW);
  }
}
