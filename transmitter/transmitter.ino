#include "FlexCAN.h"
#include "kinetis_flexcan.h"
int led = 13;
// create CAN object
FlexCAN CANTransmitter(16000000/100000);
static CAN_message_t msg;

void setup() {
  // init CAN bus
  CANTransmitter.begin();
  pinMode(led, OUTPUT);
  delay(1000);
  pinMode(24, INPUT_PULLDOWN);
  pinMode(25, INPUT_PULLDOWN);
  Serial.println("CAN Transmitter Initialized");
  delay(2000);
}

void loop() {
  //Serial.print("Sending: ");
  msg.id = 0xFFF;
  msg.len = 2;
  msg.ext = 0;
  for(int i=0; i<msg.len; i++) {
    msg.buf[i] = 99;
    Serial.print(msg.buf[i]); Serial.print(" ");
  }
  Serial.println("");
  // stops when no buffer can be found
  if (CANTransmitter.write(msg) == 0) {
    while(true);
    return;
  }
  digitalWrite(led, !digitalRead(led));
  //Serial.print(digitalRead(24)); //Serial.print(digitalRead(25));
  delay(1000);
}
