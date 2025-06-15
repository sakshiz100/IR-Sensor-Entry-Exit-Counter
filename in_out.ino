#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// Define the pins for the sensors and buzzer
const int entrySensorPin = 2; // IR sensor for entry count
const int exitSensorPin = 3; // IR sensor for exit count
const int buzzerPin = 4; // Buzzer pin
// Variables to store count values
int entryCount = 0;
int exitCount = 0;
// Set the LCD address (typically 0x27 for a 16x2 display)
int lcdAddress = 0x27;
// Set the LCD dimensions (16x2)
int lcdCols = 16;
int lcdRows = 2;
// Initialize the LCD interface
LiquidCrystal_I2C lcd(lcdAddress, lcdCols, lcdRows);
void setup() {
// Initialize serial communication
Serial.begin(9600);
// Initialize sensor pins
pinMode(entrySensorPin, INPUT);
pinMode(exitSensorPin, INPUT);
// Initialize buzzer pin
pinMode(buzzerPin, OUTPUT);
// Initialize LCD with the I2C address
lcd.init();
lcd.backlight();
// Print setup message to serial monitor
Serial.println("Setup complete. Ready for operation.");
}
void loop() {
// Check entry sensor
if (digitalRead(entrySensorPin) == LOW) {
delay(100); // Debounce
if (digitalRead(entrySensorPin) == LOW) {
// Increment entry count
entryCount++;
// Play sound on buzzer (100Hz)
tone(buzzerPin, 100);
// Print entry and exit counts to serial monitor
Serial.print("Entry count = ");
Serial.print(entryCount);
Serial.print(", Exit count = ");
Serial.println(exitCount);
// Display counts on LCD
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Entry count = ");
lcd.print(entryCount);
lcd.setCursor(0, 1);
lcd.print("Exit count = ");
lcd.print(exitCount);
// Wait for a short delay
delay(500); // Additional delay after entry
// Stop buzzer sound
noTone(buzzerPin);
}
}
// Check exit sensor
if (digitalRead(exitSensorPin) == LOW) {
delay(100); // Debounce
if (digitalRead(exitSensorPin) == LOW && exitCount < entryCount) {
// Increment exit count if it's less than entry count
exitCount++;
// Play sound on buzzer (1000Hz)
tone(buzzerPin, 1000);
// Print entry and exit counts to serial monitor
Serial.print("Entry count = ");
Serial.print(entryCount);
Serial.print(", Exit count = ");
Serial.println(exitCount);
// Display counts on LCD
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Entry count = ");
lcd.print(entryCount);
lcd.setCursor(0, 1);
lcd.print("Exit count = ");
lcd.print(exitCount);
// Wait for a short delay
delay(500); // Additional delay after exit
// Stop buzzer sound
noTone(buzzerPin);
}
}
}
