/***************************************************************************
  Lesson 4

  Harte Microcontroller Workshop
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_SSD1306.h>
#include "RTClib.h"
#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define SEALEVELPRESSURE_HPA (1019.64) /* Sealevel pressure in millibar */
#define uS_TO_S_FACTOR 1000000         /* Conversion factor for micro seconds to seconds */
#define TIME_TO_SLEEP  10              /* Time ESP32 will go to sleep (in seconds) */
#define D4 4                           /* Digital input GPIO 4, which powers our sensors. */
#define OLED_RESET 4                   /* External VCC pin for display */

Adafruit_BME280 bme;                    // BME280 Enviromental Sensor in I2C mode (default).
Adafruit_SSD1306 display(OLED_RESET);   // SSD1306 128x32 OLED Display.
RTC_DS3231 rtc;                         // RTC DS3231 Real Time Clock.
RTC_DATA_ATTR boolean firstBoot = true; // Is this the first time we started?

struct MSR {
  float temperature;
  float pressure;
  float humidity;
  char datetime[20];
} measurements;

void setup() {
  Serial.begin(115200);
  Serial.println(F("Begin Lesson 4"));

  Serial.println(F("Turning on D4 to power devices"));
  turnOnPinD4();

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

  Serial.println(F("Starting SD Card Reader/Writer"));
  if (!startSdCard()) {
    stopError();
    return;
  }

  Serial.println(F("Starting the Display"));
  startDispay();

  // Is this the first time we started?
  if(firstBoot) {
    firstBoot = false;
    Serial.println(F("Let's begin..."));
  } else {
    Serial.println(F("I AM AWAKE!"));
  }

  turnOnBlueLED();
  getValues();
  displayValues();
  printValues();
  saveValues();
  turnOffBlueLED();
  goToSleep();
}

void loop() {
  // I don't run anymore in DEEP SLEEP mode.
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

bool startSdCard() {
  if(!SD.begin()){
      Serial.println(F("Card Mount Failed"));
      return false;
  }
  
  if(SD.cardType() == CARD_NONE){
      Serial.println(F("No SD card attached"));
      return false;
  }

  return true;
}

void startDispay() {
  // initialize with the I2C addr 0x3C (for the 128x32)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void goToSleep() {
  Serial.println(F("Going to Sleep!"));
  delay(100); // Wait a little to make sure everything is done.
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_deep_sleep_start();
}

void turnOnPinD4() {
  pinMode(D4, OUTPUT);
  digitalWrite(D4, HIGH);
  delay(200); //Wait a little bit for the pin to stabilize.
}

void getValues() {
  measurements.temperature = bme.readTemperature();
  measurements.pressure = bme.readPressure() / 100.0F;
  measurements.humidity = bme.readHumidity();
  DateTime now = rtc.now();
  snprintf(measurements.datetime, 20, "%d/%02d/%02d %02d:%02d:%02d", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
}

void saveValues() {
  char message[100];
  snprintf(message, 300, "%s,%f,%f,%f\n", measurements.datetime, measurements.temperature, measurements.pressure, measurements.humidity);
  writeToFile(SD, "/data.csv", message);
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

void displayValues() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println(measurements.datetime);
  display.setCursor(0,8);
  display.println("Temperature=" + String(measurements.temperature) + (char)247 +"C");
  display.setCursor(0,16);
  display.println("Pressure=" + String(measurements.pressure) + "hPa");
  display.setCursor(0,24);
  display.println("Humidity=" + String(measurements.humidity) + "%");
  display.display();
}

void printDateTime() {
  DateTime now = rtc.now();
  char datetime[20];
  snprintf(datetime, 20, "%d/%02d/%02d %02d:%02d:%02d UTC", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
  Serial.println(datetime);
}

void writeToFile(fs::FS &fs, const char * path, const char * message) {
  Serial.printf("Writing to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if(!file){
      File file = fs.open(path, FILE_WRITE);
  }
  if(file.print(message)){
      Serial.println("File Write Success");
  } else {
      Serial.println("File Write Failed");
  }
  file.close();
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
