#include <LiquidCrystal_I2C.h>

const int resistancemeter = A3; // Replace with your actual analog pin
const float reference_res = 10000.0; // Replace with your actual reference resistor value in ohms
const float v_ref = 5.0; // Replace with your actual supply voltage
float r;
// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 4, 20); //0x27 adress of the lcd in hexa

void setup() {
  Serial.begin(9600); // Start serial at 9600 bps
  // Initialize the LCD
  lcd.backlight();
  lcd.init();
  lcd.clear();
}

void calculate_resistance() {
  float voltage;
  int sensorValue = analogRead(resistancemeter); // Read the analog value
  voltage = sensorValue * (v_ref / 1023.0); // Convert to voltage
  r = voltage * reference_res/(v_ref - voltage); // Calculate the resistance
}

void loop() {
  calculate_resistance();

  //Print the measured resistance to the serial monitor
  //Serial.print("Measured resistance: ");
  //Serial.println(resistance, 2);

  // Display the measured resistance on the LCD
  lcd.setCursor(0, 2); // Move to the third row
  lcd.print("Res: ");
  lcd.print(r, 2); // Display resistance with 2 decimal places
  delay(1000); // Wait for a second before taking another measurement
}
