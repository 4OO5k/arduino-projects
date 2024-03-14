#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

int lowerThreshold = 310;
int upperThreshold = 510;

// Sensor pins
#define sensorPower 7
#define sensorPin A0
int val = 0; // Value for storing water level

void setup() {
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.backlight();
  pinMode(sensorPower, OUTPUT);
  digitalWrite(sensorPower, LOW);
}

void loop() {
  int level = readSensor();

  if (level == 0) {
    Serial.println("Water Level: Empty");
    lcd.setCursor(0,0);
    lcd.print("   WATER LEVEL ");
    lcd.setCursor(0,1);
    lcd.print("     EMPTY      ");
  }
  else if (level > 0 && level <= lowerThreshold) {
    Serial.println("Water Level: Low");
    lcd.setCursor(0,0);
    lcd.print("   WATER LEVEL ");
    lcd.setCursor(0,1);
    lcd.print("      LOW       ");
    
  }
  else if (level > lowerThreshold && level <= upperThreshold) {
    Serial.println("Water Level: Medium");
    lcd.setCursor(0,0);
    lcd.print("   WATER LEVEL ");
 lcd.setCursor(0,1);
    lcd.print("     MEDIUM     ");
  }
  else if (level > upperThreshold) {
    Serial.println("Water Level: High");
    lcd.setCursor(0,0);
    lcd.print("   WATER LEVEL ");
    lcd.setCursor(0,1);
    lcd.print("     FULL       ");
  }
  delay(1000);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);
  delay(10);
  val = analogRead(sensorPin);
  digitalWrite(sensorPower, LOW);
  return val;
}
