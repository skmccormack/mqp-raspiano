#include <SPI.h>

const int SS1 = 10;
const int wiper0writeAddr = B00000000;
const int wiper1writeAddr = B00010000;

void setup() {
  // put your setup code here, to run once:
  pinMode(SS1, OUTPUT);

  SPI.begin();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int level = random(0, 256);
  Serial.println(level);
  
  potWrite(wiper0writeAddr, level);
  potWrite(wiper1writeAddr, level);

  delay(1000);

  int in1 = analogRead(A1)/4;
  int in2 = analogRead(A2)/4;

  Serial.println(in1);
  Serial.println(in2);

  delay(2000);

}

void potWrite(int address, int value) {
  digitalWrite(SS1,LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(SS1,HIGH);
}
