/*
 This Sketch is based on
 Stepper Motor Control - one revolution
 Created by Tom Igoe
 Modified by Tim Heilers (http://www.taheilers.com) for use with a syring pump.
 
 I used doctek's Simple Syringe Pump https://www.thingiverse.com/thing:866904,
 Adafruit's 200 step NEMA 17 motor https://www.adafruit.com/product/324,
 and an L293D H-Bridge https://www.adafruit.com/product/807.
 
 The syringe pump should draw 1 mL, then dispense 1 mL.
 */

#include <Stepper.h>

const int stepsPerRevolution = 200;  // Number of steps per revolution for Syringe Pump motor
const float threadPitch = 0.1250;    // Pitch of Syringe Pump threaded rod in cm.
const float radius = 0.625;          // Radius of Syringe in cm.


// initialize the stepper library on pins 8 through 11:
Stepper syringePump(stepsPerRevolution, 8, 9 ,10, 11);

void setup() {
  // set the speed at 60 rpm:
  syringePump.setSpeed(60);
  // initialize the serial port:
  Serial.begin(9600);
}

void loop() {
  test();
}

// Volume syring pump moves with one step of the motor.
float mLPerStep() {
  return float((radius * radius * threadPitch * PI)/(stepsPerRevolution));
}

void draw(int amt){
  Serial.println("Drawing " + String(amt) + " mL");
  syringePump.step(-int(amt/mLPerStep()));
}

void dispense(int amt){
  Serial.println("Dispensing " + String(amt)+ " mL");
  syringePump.step(int(amt/mLPerStep()));
}

void test(){
  //Draw 1 mL
  draw(1);
  delay(1000);

  //Dispense 1 mL
  dispense(1);
  delay(1000);
}

