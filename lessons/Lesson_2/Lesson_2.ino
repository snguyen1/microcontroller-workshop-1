/***************************************************************************
  Lesson 2

  Harte Microcontroller Workshop
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "RTClib.h"

#define SEALEVELPRESSURE_HPA (1019.64) /* Sealevel pressure in millibar */

Adafruit_BME280 bme;                    // BME280 Enviromental Sensor in I2C mode (default).
RTC_DS3231 rtc;                         // RTC DS3231 Real Time Clock.

unsigned long delayTime = 1000; // Time to wait after each loop in milliseconds.

struct MSR {
  float temperature;
  float pressure;
  float humidity;
  char datetime[20];
} measurements;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Begin Lesson 2"));

  Serial.println(F("Starting BME 280 Sensor"));
  if (!startSensor()) {
    stopError();
    return;
  }

  Serial.println(F("Starting Real Time Clock"));
  if (!startRealTimeClock()){
    stopError();
    return;
  }

  Serial.println(F("Current time is:"));
  printDateTime();
}

void loop() {
  getValues();
  printValues();
  delay(delayTime);
}

bool startSensor() {
  if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    return false;
  }

  return true;
}

bool startRealTimeClock() {
  if (!rtc.begin()) {
    Serial.println(F("Couldn't find RTC"));
    return false;
  }

  return true;
}

void getValues() {
  measurements.temperature = bme.readTemperature();
  measurements.pressure = bme.readPressure() / 100.0F;
  measurements.humidity = bme.readHumidity();
  DateTime now = rtc.now();
  snprintf(measurements.datetime, 20, "%d/%02d/%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
}

void printValues() {
  Serial.println();
  
  Serial.print("Current Time = ");
  Serial.print(measurements.datetime);
  Serial.println(" UTC");

  Serial.print("Temperature = ");
  Serial.print(measurements.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(measurements.pressure);
  Serial.println(" hPa");

  Serial.print("Humidity = ");
  Serial.print(measurements.humidity);
  Serial.println(" %");

  Serial.println();
}

void printDateTime() {
  DateTime now = rtc.now();
  char datetime[20];
  snprintf(datetime, 20, "%d/%02d/%02d %02d:%02d:%02d UTC", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  Serial.println(datetime);
}

void turnOnBlueLED() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
}

void turnOffBlueLED() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
}

void stopError() {
  while (1) {
    turnOnBlueLED();
    delay(100);
    turnOffBlueLED();
    delay(100);
    turnOnBlueLED();
    delay(100);
    turnOffBlueLED();
    delay(800);
  }
}
