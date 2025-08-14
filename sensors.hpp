#pragma once
/**
 * File: sensors.hpp
 * Description: Sensor pin setup and distance function for 1 HC-SR04 (front only).
 */

#include <Arduino.h>

// Only front sensor for now
const int trigFront = 9;
const int echoFront = 8;

void setupSensors() {
  pinMode(trigFront, OUTPUT);
  pinMode(echoFront, INPUT);
}

long readDistanceCM(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 20000); // Timeout after 20ms
  return duration * 0.034 / 2; // Convert to cm
}
