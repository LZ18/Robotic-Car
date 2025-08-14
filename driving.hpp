#pragma once
/**
 * File: driving.hpp
 *
 * Description:
 * This file contains functions to map a controller's joystick(s) for driving the Basic Bot.
 * The tank drive mode requires 2 joysticks, so it can only be used with the Advanced Controller.
 */

/* Config --------------------------------------------------------------------------------------- */

/**
 * @brief Uncomment this macro to enable "Tank Drive" mode. If left comment out, the robot will
 * remain in the default "Single Joystick Drive" mode.
 *
 * @remark "Tank Drive" mode requires a controller with 2 joysticks, which would mean a tBB Advanced
 * controller, but not a tBB Basic controller.
 */
 
//#define TANK_DRIVE

/* Includes ------------------------------------------------------------------------------------- */

#include "controller_handling.hpp"
#include "motor_control.hpp"

/* Constants ------------------------------------------------------------------------------------ */

static constexpr int kFastModeMotorPercent = 100;
static constexpr int kSlowModeMotorPercent = 50;

static constexpr unsigned long kSpeedToggleDebounceDelayMs = 100;

/* Variables ------------------------------------------------------------------------------------ */

static boolean isFastModeEnabled = true;
static boolean wasSpeedToggleBtnPressed = false;
static unsigned long lastSpeedToggleButtonTime = 0;

/* Functions ------------------------------------------------------------------------------------ */

void singleJoystickDrive(const Controller& aController) {
  if (aController.joyLeftY >= 0) {
    if (aController.joyLeftX >= 0) {
      setLeftMotor(min(aController.joyLeftY + aController.joyLeftX, 100));
      setRightMotor(aController.joyLeftY - aController.joyLeftX);
    } else if (aController.joyLeftX < 0) {
      setLeftMotor(aController.joyLeftY + aController.joyLeftX);
      setRightMotor(min(aController.joyLeftY - aController.joyLeftX, 100));
    }
  } else if (aController.joyLeftY < 0) {
    if (aController.joyLeftX >= 0) {
      setLeftMotor(aController.joyLeftY + aController.joyLeftX);
      setRightMotor(max(aController.joyLeftY - aController.joyLeftX, -100));
    } else if (aController.joyLeftX < 0) {
      setLeftMotor(max(aController.joyLeftY + aController.joyLeftX, -100));
      setRightMotor(aController.joyLeftY - aController.joyLeftX);
    }
  }
}

void tankDrive(const Controller& aController) {
  setLeftMotor(aController.joyLeftY);
  setRightMotor(aController.joyLeftY);
}

void setFastMode() {
  setMotorLimit(kFastModeMotorPercent);
  isFastModeEnabled = true;
  Serial.println("Fast Mode");
}

void setSlowMode() {
  setMotorLimit(kSlowModeMotorPercent);
  isFastModeEnabled = false;
  Serial.println("Slow Mode");
}

void toggleMotorSpeed() {
  if (isFastModeEnabled) {
    setSlowMode();
  } else {
    setFastMode();
  }
}

void setupDriving() { setFastMode(); }

void controlMotors(const Controller& aController) {
  unsigned long currentTime = millis();

  // Speed mode toggle (keep this)
  if (aController.btnLeftJoy && !wasSpeedToggleBtnPressed &&
      currentTime - lastSpeedToggleButtonTime > kSpeedToggleDebounceDelayMs) {
    lastSpeedToggleButtonTime = millis();
    wasSpeedToggleBtnPressed = true;
    toggleMotorSpeed();
  } else if (!aController.btnLeftJoy) {
    wasSpeedToggleBtnPressed = false;
  }

  // 🚀 Arcade drive motor control (add this!)
  int forward = aController.joyLeftY;
  int turn = aController.joyLeftX;

  int leftInput = constrain(forward + turn, -100, 100);
  int rightInput = constrain(forward - turn, -100, 100);

  int leftSpeed = map(leftInput, -100, 100, -255, 255);
  int rightSpeed = map(rightInput, -100, 100, -255, 255);

  setLeftMotor(leftSpeed);
  setRightMotor(rightSpeed);





#ifdef TANK_DRIVE
  /* ---------------------------------- */
  /*             TANK DRIVE             */
  /* ---------------------------------- */
  tankDrive(aController);
#else
  /* ---------------------------------- */
  /*        SINGLE JOYSTICK DRIVE       */
  /* ---------------------------------- */
  singleJoystickDrive(aController);
#endif
}

  /* ---------------------------------- */
  /*        Auto Drive Functions        */
  /* ---------------------------------- */
void driveForward() {
  setLeftMotor(100);
  setRightMotor(100);
}

void driveBackwards() {
  setLeftMotor(-100);
  setRightMotor(-100);
}

void stopDriving() {
  setLeftMotor(0);
  setRightMotor(0);
}

void turnRight() {
  setLeftMotor(-100);
  setRightMotor(100);
}

void turnLeft() {
  setLeftMotor(100);
  setRightMotor(-100);
}

