#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

int IN4 = 12;
const int tombol = 8;
int nilaitombol;
int countertombol = 0;

void setup() {
  pinMode(IN4, OUTPUT);
  pinMode(8, INPUT);
  pinMode(tombol, INPUT_PULLUP);
  
  lcd.begin();
  lcd.setCursor(0,0);
  lcd.print("     ORANGE    ");
  lcd.setCursor(0,1);
  lcd.print("SORTING CONVEYOR ");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("  PLEASE  PUSH  ");
  lcd.setCursor(0,1);
  lcd.print("  START BUTTON  ");
}

void loop() {
  pushbutton();
}

void pushbutton() {
  if (digitalRead(tombol) == LOW) {
    countertombol++;
    delay(250);
    if (countertombol == 1) {
      digitalWrite(IN4, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    CONVEYER    ");
      lcd.setCursor(0,1);
      lcd.print("       ON       ");
    }
    if (countertombol == 2) {
      digitalWrite(IN4, LOW);
      countertombol = 0;
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    CONVEYER    ");
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
