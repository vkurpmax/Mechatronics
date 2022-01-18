#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
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

int IN4 = 15;                                      // D8 NodeMCU ESP8266
const int tombol = 2;                             // D4 NodeMCU ESP8266
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

const char* ssid1 = "Vkurpmax";
const char* password = "lumos maxima";
ESP8266WebServer server(80);
bool statusButton = LOW;

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
  Serial.begin(115200);
  delay(100);

  Serial.println("Connecting ");
  Serial.println(ssid1);
  WiFi.begin(ssid1, password);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected..!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // Status ON/OFF
  server.on("/", connected);
  server.on("/conveyoron", conveyor_ON);
  server.on("/conveyoroff", conveyor_OFF);
  server.onNotFound(not_found);
  server.begin();
  Serial.println("Memulai HTTP server");

  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, myTimerEvent);

  pinMode(IN4, OUTPUT);
  pinMode(tombol, INPUT_PULLUP);  // D4 Pushbutton
  pinMode(16, INPUT);             // D0 NodeMCU ESP8266 for IR
  pinMode(trigPin,OUTPUT);        // Trig pin
  pinMode(echoPin,INPUT);         // Echo pin

  servo1.attach(12);              // D6 node
  servo2.attach(14);              // D5 NodeMCU ESP8266

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
  server.handleClient();
  Blynk.run();
  timer.run();
  pushbutton();
  IR1();
  bacaultra();
  web();
}

void web()
{
  if (statusButton = HIGH)
  {
    countertombol++;
    delay(500);
    if (countertombol == 1)
    {
      statusButton = HIGH;
      digitalWrite(IN4, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    CONVEYOR    ");
      lcd.setCursor(0,1);
      lcd.print("       ON       ");
    }
    if (countertombol == 2)
    {
      statusButton = LOW;
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

void pushbutton()
{
  if (digitalRead(tombol) == LOW)
  {
    countertombol++;
    delay(500);
    if (countertombol == 1)
    {
      statusButton = HIGH;
      digitalWrite(IN4, HIGH);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("    CONVEYOR    ");
      lcd.setCursor(0,1);
      lcd.print("       ON       ");
    }
    if (countertombol == 2)
    {
      statusButton = LOW;
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
    
    digitalWrite(IN4,LOW);  //Motor off
    delay(1000);
    digitalWrite(IN4,HIGH); //Motor on 
  }
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
  
  if(distance>=6 && distance <9 && countertombol == 1) // Besar
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

   digitalWrite(IN4,LOW); // Motor OFF
   delay(1000);
   digitalWrite(IN4,HIGH);
   servo1.write(60);
   delay(4500);
   servo1.write(105);
  }
   if(distance<=5 && distance>=1 &&countertombol == 1)  // Kecil
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

   digitalWrite(IN4,LOW); // Motor OFF
   delay(1000);
   digitalWrite(IN4,HIGH);
   servo2.write(60);
   delay(4500);
   servo2.write(93);
  } 
}




void connected()
{
  statusButton = LOW;
  server.send(200, "text/html", kirimHTML(statusButton));
}

void conveyor_ON()
{
  statusButton = HIGH;
  server.send(200, "text/html", kirimHTML(statusButton));
}

void conveyor_OFF()
{
  statusButton = LOW;
  server.send(200, "text/html", kirimHTML(statusButton));
}

void not_found()
{
  server.send(404, "text/plain", "Halaman tidak ditemukan");
}

// Fungsi untuk mengemas kode HTML yang dikembalikan sebagai string
String kirimHTML(uint8_t statusButton)
{
    String konten = "<html>\n";
    konten +="<head>\n";
    konten +="<title>ICCS</title>\n";
    konten +="</head>\n";
    konten +="<body>\n";
    konten +="<h1 style=\"font-size: 100px; text-align: center\">INTEGRATED CONVEYOR CONTROL SYSTEM</h1>\n";

    if(statusButton)
    {
        konten +="<p style=\"font-size: 80px; text-align: center\">Status Conveyor: ON</p>\n";
        konten +="<a href=\"/conveyoroff\">\n";
        konten +="<button type=\"button\" style=\"font-size: 150px; text-align: center; position: relative; left: 50%\">OFF</button>\n";
        konten +="</a>\n";
    }

    else
    {
        konten +="<p style=\"font-size: 80px; text-align: center\">Status Conveyor: OFF</p>\n";
        konten +="<a href=\"/conveyoron\">\n";
        konten +="<button type=\"button\" style=\"font-size:150 px; text-align: center; position: relative; left: 50%\">ON</button>\n";
        konten +="</a>\n";
    }

    konten +="</body>\n";
    konten +="</html>\n";
    return konten;
}
