/*
  This program Created by Muhammad Fajri Akbar.
  Special Thanks to help me understand this project.
*/

int in3 = 13;
int in4 = 12;
const int enb = 11;
const int tombol = 3;
int tombolStatus = LOW;

void setup() {
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(tombol, INPUT_PULLUP);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void loop() {

nyala:
analogWrite(enb, 200);
if (digitalRead(tombol) == LOW){analogWrite(enb, 0);if (digitalRead(tombol) == HIGH){delay(1000);goto mati;}}

goto nyala;

mati:
analogWrite(enb, 0);
if (digitalRead(tombol) == LOW){analogWrite(enb, 200);if (digitalRead(tombol) == HIGH){delay(1000);goto nyala;}}
goto mati;
  
}
