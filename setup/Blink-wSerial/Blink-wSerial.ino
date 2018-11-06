
// Michael S. Williamson 
// 6 NOV 2018
//
// This simple sketch serves as confirmation of successful connection
// and programming of the ESP32. It will flash the LED every second as
// well as display the string "Go Islanders!" on the serial line at a 
// baud rate of 115200, which is the normal default for most systems.
//

void setup() {
  // Initialize pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  // Set serial to common default baudrate.
  Serial.begin(115200);
}

void loop() {
  blink(LED_BUILTIN);
}

void blink(int led) {
  digitalWrite(led, HIGH);   // Turn LED on.
  delay(1000);               // Wait a second.
  digitalWrite(led, LOW);    // Turn LED off.
  writeText();
  delay(1000); 
}

void writeText() {
  Serial.println("Go Islanders!"); 
}
