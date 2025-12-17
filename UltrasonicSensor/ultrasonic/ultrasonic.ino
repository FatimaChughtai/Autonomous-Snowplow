
#include <Wire.h>
#include "ultrasonic.h"
// int DISTANCE = 0;
int TRG_PIN = 7;
int ECHO_PIN = 8;
bool CHECK = false;


void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(TRG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(TRG_PIN), rxISR, CHANGE);
}

void loop() {
  int duration = 0;
  int pulse;
  digitalWrite(TRG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRG_PIN, LOW);
  pulse = pulseInLong(ECHO_PIN, HIGH);
  if (pulse > 0) { // Check if pulseInLong returned a valid reading
    DISTANCE = (pulse * 0.0343) / 2; // Convert to cm
  }
  if (CHECK){
    CHECK = false;
    checkObject();
  }
}

void checkObject(){
  Serial.println(DISTANCE);
    if (DISTANCE > THRESHOLD || DISTANCE < 0.5){
      Serial.println("No obsclates detected");
      delay(1000);
    }
    else{
      Serial.println("Obstacle Detected! Sending Alert");
    }
}

void rxISR(){
  CHECK = true;
}