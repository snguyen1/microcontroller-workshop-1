/***************************************************************************
  Lesson 1

  Harte Microcontroller Workshop
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SEALEVELPRESSURE_HPA (1019.64)

Adafruit_BME280 bme; // BME280 Enviromental Sensor in I2C mode (default).

unsigned long delayTime = 1000; // Time to wait after each loop in milliseconds.

struct MSR {
  float temperature;
  float pressure;
  float humidity;
  // char datetime[20];
} measurements;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Begin Lesson 1"));

  Serial.println(F("Starting BME 280 Sensor"));
  startSensor();
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

void getValues() {
  measurements.temperature = bme.readTemperature();
  measurements.pressure = bme.readPressure() / 100.0F;
  measurements.humidity = bme.readHumidity();
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