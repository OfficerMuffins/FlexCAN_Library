#include "FlexCAN.h"
#include "kinetis_flexcan.h"
#include <SD.h>
#include <SPI.h>

#define CAN_TEST 1

// TODO: take message from CAN frame and write to SD card
// hello world
#if CAN_TEST == 0
#else
int led = 13;
// create CAN object
FlexCAN CANReceiver(16000000/100000);
static CAN_message_t msg;
static CAN_filter_t filter;

typedef struct uint128_t { unsigned char x[16]; } uint128_t;
#endif

File myFile;

void setup() {
  /*
  Serial.begin(500);
  while (!Serial);
  Serial.println("Initializing SD card...");
  if (!SD.begin(BUILTIN_SDCARD)) {
    Serial.println("initialization failed!");
  }
  myFile = SD.open("test.bin", FILE_WRITE);
  if (!myFile) // file had to be created
    Serial.println("file had to be created");
  Serial.println("attempting write to file");
  // prints a shit load of Ls
  // need a stopping criteria
  while (1) {
    myFile.write(76);
  }

  myFile.close();
  */

#if CAN_TEST == 0
#else
  // init CAN bus
  CANReceiver.begin();
  pinMode(led, OUTPUT);
  Serial.println("CAN Receiver Initialized");
#endif
  pinMode(24, INPUT_PULLDOWN);
  pinMode(25, INPUT_PULLDOWN);
  //Serial.println(CANReceiver.defaultMask.id);
  delay(2000);
}

void loop() {
  CANReceiver.poll();
#if CAN_TEST == 0
#else
  /*
  if(CANReceiver.available()) {
    Serial.println("Found a frame");
    while(1);
  }*/
  while(CANReceiver.read(msg)) {
    // toggle LEDs
    digitalWrite(led, !digitalRead(led));
    Serial.print("Receiving: ");
    for(int i=0; i<msg.len; i++) {
      Serial.print(msg.buf[i]); Serial.print(" ");
    }
    Serial.println("");
  }
  //Serial.print(digitalRead(24)); Serial.println(digitalRead(25));
#endif
  delay(2000);
}
