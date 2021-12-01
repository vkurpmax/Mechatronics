#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int in3 = 13;
int in4 = 12;
const int enb = 11;
const int tombol = 3;

void setup() {
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(tombol, INPUT_PULLUP);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("     ORANGE    ");
  lcd.setCursor(0,1);
  lcd.print("SORTING CONVEYER ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  PLEASE  PUSH  ");
  lcd.setCursor(0,1);
  lcd.print("  START BUTTON  ");
}

void loop(){
  pushbutton();
}


void pushbutton() {
analogWrite(enb, 0);
if (digitalRead(tombol) == LOW){analogWrite(enb, 200);if (digitalRead(tombol) == HIGH){delay(1000);goto nyala;}}
goto mati;

nyala:
analogWrite(enb, 200);
if (digitalRead(tombol) == LOW){analogWrite(enb, 0);if (digitalRead(tombol) == HIGH){delay(1000);goto mati;}}
goto nyala;

mati:
analogWrite(enb, 0);
if (digitalRead(tombol) == LOW){analogWrite(enb, 200);if (digitalRead(tombol) == HIGH){delay(1000);goto nyala;}}
goto mati;
  
}
