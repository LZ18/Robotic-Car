/**
 * File: tBB_Joystick_Base_Code.ino
 *
 * Description:
 * This file serves as an example for robots controlled by theBasicBot's ESP32-based controller.
 */

/* Includes ------------------------------------------------------------------------------------- */

#include "controller_handling.hpp"
#include "motor_control.hpp"
#include "lights.hpp"
#include "driving.hpp"
#include "auto_drive.hpp"
#include "servo_control.hpp"
#include "sensors.hpp"

/* Variables ------------------------------------------------------------------------------------ */

static Controller controller = {};

/* Setup and Loop ------------------------------------------------------------------------------- */

void setup() {
  // Setup serial
  Serial.begin(9600);
  Serial.print("tBB Joystick Base Code V1");
  Serial.print(" | VER 2.3");
  Serial.println(" | Mar 15, 2024");
  // NOTE: This serial port is shared between both the BLE adapter (e.g., HM-10 module), and the
  // Serial Monitor that is available when you connect the Arduino to a computer. This means if you
  // print anything to the serial, it will go to BOTH the computer and the controller. This should
  // be fine, because the controller doesn't currently parse any input over BLE.

  setupMotors();
  setupDriving();
  setupLights();
  setupServos();
  setupSensors();
}

void loop() {
  /* ---------------------------------- */
  /*         Update Controller          */
  /* ---------------------------------- */

  controller.update();

  /* ---------------------------------- */
  /*           Control Robot            */
  /* ---------------------------------- */
  
// any functions that will be called direclty by a button press must be included here
  controlServo1(controller);
  controlServo2(controller);
  controlLights(controller);
  controlMotors(controller);
  controlAutonomous(controller);
  
}

