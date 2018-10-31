/***************************************************************************
  Lesson 1

  Harte Microcontroller Workshop
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>

#define SEALEVELPRESSURE_HPA (1019.64) /* Sealevel pressure in millibar */
#define OLED_RESET 4                   /* External VCC pin for display */

Adafruit_BME280 bme;                    // BME280 Enviromental Sensor in I2C mode (default).
Adafruit_SSD1306 display(OLED_RESET);   // SSD1306 128x32 OLED Display.

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
  if (!startSensor()) {
    return;
  }

  Serial.println(F("Starting the Display"));
  startDispay();
}

void loop() {
  getValues();
  printValues();
  displayValues();
  delay(delayTime);
}

bool startSensor() {
  if (!bme.begin(0x76)) {
      Serial.println("Could not find a valid BME280 sensor, check wiring!");
      return false;
  }

  return true;
}

void startDispay() {
  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void getValues() {
  measurements.temperature = bme.readTemperature();
  measurements.pressure = bme.readPressure() / 100.0F;
  measurements.humidity = bme.readHumidity();
}

void printValues() {
  Serial.println();
  
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

void displayValues() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("BME280 Measurements");
  display.setCursor(0,8);
  display.println("Temperature=" + String(measurements.temperature) + (char)247 +"C");
  display.setCursor(0,16);
  display.println("Pressure=" + String(measurements.pressure) + "hPa");
  display.setCursor(0,24);
  display.println("Humidity=" + String(measurements.humidity) + "%");
  display.display();
}
