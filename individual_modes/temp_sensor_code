#include <LiquidCrystal_I2C.h>

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 4, 20); //0x27 address of the lcd in hexa

byte tempc_byte;
const int temperature = A1;

unsigned long temperature_timer;

byte temperature_measurement() {
  float tempc; //variable to store temperature in degree Celsius
  float v_out;

  v_out = analogRead(temperature); //Reading the value from sensor

  tempc = (v_out*500)/1023 - 50; //Storing value in Degree Celsius
  if (tempc >= 127)
    return 127;
  else
    return byte(tempc);
}

void setup() {
  pinMode(temperature, INPUT); //Configuring sensor pin as input
  Serial.begin(9600);
  // Initialize the LCD
  lcd.backlight();
  lcd.init();
  lcd.clear();
}

void loop() {
  tempc_byte = temperature_measurement();
  // Display the measured temperature on the LCD
  lcd.setCursor(0, 2); // Move to the third row
  lcd.print("Temperature: ");
  lcd.print(byte(tempc_byte)); // Display temperature with 2 decimal places

  delay(1000);
}
