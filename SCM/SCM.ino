#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize I2C LCD (address usually 0x27 or 0x3F, 16 columns, 2 rows)
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Change 0x27 to 0x3F if needed

// Analog input pins
const int thermistorPin = A0;
const int thermocouplePin = A1;
const int rtdPin = A2;
const int lm35Pin = A3;

// Thermistor parameters
const float R1 = 10000.0;  // Voltage divider resistor
const float BETA = 3950.0; // Beta coefficient (adjust for your thermistor)
const float T0 = 298.15;   // Reference temperature (25°C)
const float R0 = 10000.0;  // Resistance at T0

// Variables to hold sensor readings
float thermistorTemp = 0;
float thermocoupleTemp = 0;
float rtdTemp = 0;
float lm35Temp = 0;

// Display variables
int displayIndex = 0;
unsigned long lastDisplayTime = 0;
const long displayInterval = 2000;  // Change display every 2 seconds

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Initialize I2C LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  // Welcome message
  lcd.setCursor(0, 0);
  lcd.print("Temp Sensors");
  lcd.setCursor(0, 1);
  lcd.print("Initializing...");
  delay(2000);
  
  // Set reference voltage
  analogReference(DEFAULT);
  
  lcd.clear();
}

void loop() {
  // Read all sensors
  readThermistor();
  readThermocouple();
  readRTD();
  readLM35();
  
  // Display rotation every 2 seconds
  if (millis() - lastDisplayTime >= displayInterval) {
    lastDisplayTime = millis();
    displayIndex = (displayIndex + 1) % 4;
    updateDisplay();
  }
  
  // Print to Serial Monitor
  printSerialData();
  
  delay(100);
}

void readThermistor() {
  int rawADC = analogRead(thermistorPin);
  float voltage = rawADC * (5.0 / 1023.0);
  
  if (voltage > 0) {
    float resistance = R1 * (5.0 / voltage - 1.0);
    float steinhart = (1.0 / T0) + (1.0 / BETA) * log(resistance / R0);
    steinhart = 1.0 / steinhart;
    thermistorTemp = steinhart - 273.15;
  }
}

void readThermocouple() {
  int rawADC = analogRead(thermocouplePin);
  float voltage = rawADC * (5.0 / 1023.0);
  
  // Basic approximation - ADJUST THIS FOR YOUR AMPLIFIER
  // Example: AD8495 gives 5mV/°C, so 0V = 0°C, 5V = 1000°C
  thermocoupleTemp = voltage * 200.0;  // Change multiplier as needed
}

void readRTD() {
  int rawADC = analogRead(rtdPin);
  float voltage = rawADC * (5.0 / 1023.0);
  
  // Assuming voltage divider with 100Ω resistor
  float rtdResistance = 100.0 * voltage / (5.0 - voltage);
  rtdTemp = (rtdResistance - 100.0) / 0.385;  // For PT100
}

void readLM35() {
  int rawADC = analogRead(lm35Pin);
  lm35Temp = (rawADC * 5.0 * 100.0) / 1024.0;
}

void updateDisplay() {
  lcd.clear();
  
  switch (displayIndex) {
    case 0:
      lcd.setCursor(0, 0);
      lcd.print("Thermistor:");
      lcd.setCursor(0, 1);
      lcd.print(thermistorTemp, 1);
      lcd.print(" C");
      break;
      
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Thermocouple:");
      lcd.setCursor(0, 1);
      lcd.print(thermocoupleTemp, 1);
      lcd.print(" C");
      break;
      
    case 2:
      lcd.setCursor(0, 0);
      lcd.print("RTD:");
      lcd.setCursor(0, 1);
      lcd.print(rtdTemp, 1);
      lcd.print(" C");
      break;
      
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("LM35:");
      lcd.setCursor(0, 1);
      lcd.print(lm35Temp, 1);
      lcd.print(" C");
      break;
  }
}

void printSerialData() {
  static unsigned long lastPrint = 0;
  if (millis() - lastPrint > 1000) {
    lastPrint = millis();
    
    Serial.println("=== Temperature Readings ===");
    Serial.print("Thermistor (A0): ");
    Serial.print(thermistorTemp, 2);
    Serial.println(" °C");
    
    Serial.print("Thermocouple (A1): ");
    Serial.print(thermocoupleTemp, 2);
    Serial.println(" °C");
    
    Serial.print("RTD (A2): ");
    Serial.print(rtdTemp, 2);
    Serial.println(" °C");
    
    Serial.print("LM35 (A3): ");
    Serial.print(lm35Temp, 2);
    Serial.println(" °C");
    
    Serial.print("Displaying: ");
    switch (displayIndex) {
      case 0: Serial.println("Thermistor"); break;
      case 1: Serial.println("Thermocouple"); break;
      case 2: Serial.println("RTD"); break;
      case 3: Serial.println("LM35"); break;
    }
    Serial.println("============================\n");
  }
}
