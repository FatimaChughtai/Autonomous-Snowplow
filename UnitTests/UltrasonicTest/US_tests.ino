#include "ultrasonic.h"

int DISTANCE = 0;
int TRG_PIN = 7;
int ECHO_PIN = 8;
bool CHECK = false;



void setup(){
    Serial.begin(9600);
}

void loop(){
    //Test 1: 
    //Values that meet threshold value of 15 are inputted
    //Verify that no objects are detected
    //Should return "No obstacles detected"
    DISTANCE = 25;
    rx_ISR_test();
    if (CHECK){
    CHECK = false;
    checkObject();
    }
    Serial.println("Expected Return: No obstacles detected");
    DISTANCE = 16;
    rx_ISR_test();
    if (CHECK){
    CHECK = false;
    checkObject();
    }
    Serial.println("Expected Return: No obstacles detected");
    DISTANCE = 22;
    rx_ISR_test();
    if (CHECK){
    CHECK = false;
    checkObject();
    }
    Serial.println("Expected Return: No obstacles detected");

    //Test 2
    //Values that DO NOT meet threshold are inputted
    //Should return "Obstacle Detected! Sending Alert"
    DISTANCE = 4;
    rx_ISR_test();
    if (CHECK){
    CHECK = false;
    checkObject();
  }
    Serial.println("Expected Return: Obstacle Detected! Sending Alert");
    
    DISTANCE = 1;
    rx_ISR_test();
    if (CHECK){
    CHECK = false;
    checkObject();
  }
    Serial.println("Expected Return: Obstacle Detected! Sending Alert");

    DISTANCE = 14;
    rx_ISR_test();
    if (CHECK){
    CHECK = false;
    checkObject();
  }
    Serial.println("Expected Return: Obstacle Detected! Sending Alert");

    
}

void rx_ISR_test(){
    rxISR();

}