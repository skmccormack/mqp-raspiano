#include <SPI.h>

const int SS1 = 10;
const int wiper0writeAddr = B00000000;
const int wiper1writeAddr = B00010000;
int wiperPos = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(SS1, OUTPUT);
  pinMode(A1, INPUT);

  SPI.begin();
  potWrite(wiper0writeAddr, wiperPos);
}

void loop() {
  // get AGC gate voltage
  int vg = analogRead(A1);

  // if gate voltage < 0, increment wiper
  if (vg < 100) {
    incrementPot();
  }

  // if gate voltage > 0, decrement wiper
  if (vg > 200) {
    decrementPot();
  }
}

void potWrite(int address, int value) {
  digitalWrite(SS1,LOW);
  SPI.transfer(address);
  SPI.transfer(value);
  digitalWrite(SS1,HIGH);
}

void incrementPot() {
  if (wiperPos < 257) {
    wiperPos++;
    potWrite(wiper0writeAddr, wiperPos);
  }
}

void decrementPot() {
  if (wiperPos > 0) {
    wiperPos--;
    potWrite(wiper0writeAddr, wiperPos);
  }
}
