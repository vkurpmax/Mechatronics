/*
  This program was helped by Franklin Delano Exel Mainda.
*/
int in3 = 13;
int in4 = 12;
const int enb = 11;
const int tombol = 3;
int statusTombol = 0;

void setup() {
  pinMode(enb, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(tombol, INPUT_PULLUP);
}

void loop() {
  statusTombol = digitalRead(tombol);
  if (statusTombol == LOW) {
    analogWrite(enb, 200);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
  }
  
  
    else  {
    analogWrite(enb, 0);
  
    }
}
