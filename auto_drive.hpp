#pragma once
/**
 * File: auto_drive.hpp
 * Description: Autonomous logic using only the front HC-SR04 sensor.
 */

#include "controller_handling.hpp"
#include "driving.hpp"
#include "sensors.hpp"
#include "motor_control.hpp"
#include "lights.hpp"

static boolean isRunningAuto = false;

void autoStart() {
  for (int x = 1; x <= 4; x++) {
    lightsOn();
    delay(250);
    lightsOff();
    delay(250);
  }
}

void autoDrive() {
  Serial.println("Auto Driving...");
  autoStart();
  setMotorLimit(80);
}

void controlAutonomous(const Controller& aController) {
  static unsigned long lastPrintTime = 0;
  unsigned long currentTime = millis();

  // Always print front sensor value every 1000ms
  if (currentTime - lastPrintTime >= 1000) {
    lastPrintTime = currentTime;
    long front = readDistanceCM(trigFront, echoFront);
    Serial.print("Front Distance: ");
    Serial.print(front);
    Serial.println(" cm");
  }

  // Autonomous toggle
  if (aController.btnMidLeft && !isRunningAuto) {
    isRunningAuto = true;
    autoDrive();
  }

  if (isRunningAuto) {
    long front = readDistanceCM(trigFront, echoFront);

    if (front > 0 && front < 20) {
      setLeftMotor(-180);
      setRightMotor(-180);
    } else {
      setLeftMotor(180);
      setRightMotor(180);
    }
  }

  if (!aController.btnMidLeft && isRunningAuto) {
    isRunningAuto = false;
    stopDriving();
  }
}
