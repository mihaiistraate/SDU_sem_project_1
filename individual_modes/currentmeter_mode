#include <LiquidCrystal_I2C.h>

const int currentmeter = A2; // Replace with your actual analog pin
const float reference_resistor = 1.00; // Replace with your actual reference resistor value in ohms
//should be at least 0.25W, 0.5-enough
const float v_ref = 5.00; // Replace with your actual supply voltage
float current;
// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 4, 20); //0x27 address of the lcd in hexa

void setup() {
  Serial.begin(9600); //Start serial at 9600 bps
  // Initialize the LCD
  lcd.backlight();
  lcd.init();
  lcd.clear();
}

void calculate_current() {
  float voltage;//better to write voltage=0
  int sensorValue = analogRead(currentmeter); // Read the analog value
  voltage = sensorValue * (v_ref / 1023.0); // Convert to voltage
  current = voltage / reference_resistor; // Calculate the current
}

void loop() {
  calculate_current();

  //Print the measured current to the serial monitor
  //Serial.print("Measured current: ");
  //Serial.println(resistance, 2);

  // Display the measured current on the LCD
  lcd.setCursor(0, 2); // Move to the third row
  lcd.print("Current: ");
  lcd.print(current, 2); // Display current with 2 decimal places
  delay(1000); // Wait for a second before taking another measurement
}
