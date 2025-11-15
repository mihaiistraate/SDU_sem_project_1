#include <LiquidCrystal_I2C.h>

const int voltmeter = A0;
const int v_ref = 5.00;
float v;

// Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 4, 20); //0x27 adress of the lcd in hexa

void setup() {
  Serial.begin(9600);
  // Initialize the LCD
  lcd.backlight();
  lcd.init();
  lcd.clear();
}

void calculate_voltage() {
  float R1 = 10000.00, R2 = 3300.00, resistor_ratio, adc_value = 0.00, voltage;
  resistor_ratio = (R2 / (R1 + R2));
  for (int i = 0; i < 20 ; i++) { //calculating the average analog voltage by taking 20 measurments
    adc_value += analogRead(voltmeter);
    delay(3);//probably we don’t need a delay, it’s too small delay
  }
  adc_value = adc_value / 20; //calculating the average analog value by dividing the sum with 20
  voltage = ((adc_value * v_ref) / 1024);
  v = voltage / resistor_ratio;
}

void loop() { //to different function, bec it doesn’t work together as one program 
  calculate_voltage(); //Clearing LCD after - a test
  //lcd.clear();
  // Display the measured voltage on the LCD
  lcd.setCursor(0, 2); // Move to the third row
  lcd.print("Voltage: ");
  lcd.print(v, 2); // Display voltage with 2 decimal places

  delay(1000); //less like 500
}
