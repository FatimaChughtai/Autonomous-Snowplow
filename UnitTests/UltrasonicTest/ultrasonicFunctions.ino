
#include <Wire.h>
#include "ultrasonic.h"



void checkObject(){
  Serial.print("distance received: ");
  Serial.print(DISTANCE);
  Serial.print("  threshold value: ");
  Serial.print(THRESHOLD);
    if (DISTANCE > THRESHOLD || DISTANCE < 0.5){
      Serial.print("ACTUAL RETURN: No obsclates detected  ");
      delay(1000);
    }
    else{
      Serial.print("ACTUAL RETURN Obstacle Detected! Sending Alert  ");
    }
}

void rxISR(){
  CHECK = true;
}