/* 
  This program was created by Franklin Delano Exel Mainda.
  Thanks for helping.
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
  if (digitalRead(tombol) == LOW) {
    tombolStatus = !tombolStatus;
    if (tombolStatus == LOW) {
      analogWrite(enb, 0);
      delay(50);
    }
    else {
      analogWrite(enb, 200);
      delay(50);
    }
  }
}
