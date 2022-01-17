#include <AX12A.h>
#include <Servo.h>

#define DirectionPin  (10u)
#define BaudRate    (1000000ul)

Servo servo1;
Servo servo2;

const int PB_Besar = 22;
const int PB_Kecil = 23;

void setup() {
  // put your setup code here, to run once:
  pinMode(PB_Besar, INPUT_PULLUP);
  pinMode(PB_Kecil, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(PB_Besar) == LOW)
  {
    servo1.attach(2);
    servo2.attach(3);

    servo1.write(90);
    servo2.write(0);

    Serial.begin(9600);
    ax12a.begin(BaudRate, DirectionPin, &Serial);
    ax12a.setEndless(1u, ON);
    ax12a.setEndless(2u, ON);
    ax12a.setEndless(3u, ON);
  
    ax12a.ledStatus(2, ON);
    ax12a.ledStatus(3, ON);

    delay(1000);

    ax12a.turn(1, LEFT, 0);   ax12a.turn(2, LEFT, 650); ax12a.turn(3, LEFT, 0);   delay(500);
    servo2.write(130);
    ax12a.turn(1, LEFT, 0);   ax12a.turn(2, LEFT, 200); ax12a.turn(3, RIGHT, 300);   delay(300);
    ax12a.turn(1, LEFT, 200);   ax12a.turn(2, LEFT, 200); ax12a.turn(3, RIGHT, 0);   delay(1000);
    ax12a.turn(1, LEFT, 0);   ax12a.turn(2, RIGHT, 0); ax12a.turn(3, RIGHT, 0);  delay(3000);
    servo2.write(-10);
    delay(1000);

    ax12a.turn(1, LEFT, 0);   ax12a.turn(2, LEFT, 700); ax12a.turn(3, LEFT, 0);  delay(500);
    ax12a.turn(1, RIGHT, 300);  ax12a.turn(2, LEFT, 400); ax12a.turn(3, LEFT, 200);   delay(1700);

    ax12a.turn(1, RIGHT, 0);    ax12a.turn(2, LEFT, 0); ax12a.turn(3, LEFT, 200);  delay(1000);
    servo2.write(130);

    ax12a.turn(1, RIGHT, 0);    ax12a.turn(2, LEFT, 600);   ax12a.turn(3, LEFT, 100); delay(700);
    ax12a.turn(1, LEFT, 300);    ax12a.turn(2, LEFT, 200);   ax12a.turn(3, LEFT, 100); delay(900);

    ax12a.turn(1, LEFT, 0);     ax12a.turn(2, LEFT, 200); ax12a.turn(3, RIGHT, 0);  delay(3000);



    ax12a.ledStatus(2, OFF);
    ax12a.ledStatus(3, OFF);

    servo2.write(120);

    ax12a.turn(1, LEFT, 0);                                                    
    ax12a.turn(2, LEFT, 0);
    ax12a.turn(3, RIGHT, 0);
    ax12a.turn(3, RIGHT, 0);
    delay(1000);
  }

  if (digitalRead(PB_Kecil) == LOW)
  {
    
  }

}
