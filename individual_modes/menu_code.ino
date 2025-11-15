#define F_CPU 16E6
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 4, 20);

void setup(){
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  DDRD = 0xFF;
  DDRC = 0xF0;
  PORTC = 0x3F;
  PORTD = 0x00;

  lcd.setCursor(0,0);lcd.print(" ");
  lcd.setCursor(0,1);lcd.print(" WELCOME! ");
  lcd.setCursor(0,2);lcd.print(" ");
  lcd.setCursor(0,3);lcd.print(" ");
  delay(2000);
  lcd.clear();
  delay(500);
}

void loop(){
  lcd.setCursor(0,0); lcd.print("1 Voltage"); //display choices
  lcd.setCursor(0,1); lcd.print("2 Current");
  lcd.setCursor(0,2); lcd.print("3 Resistance");
  lcd.setCursor(0,3); lcd.print("4 Temperature");
  
  while(1){
    if(PINC!=0b00111111){
      break;
    }
  } //waiting for input
  delay(100);

  switch(PINC){
    case 0b00111110: //voltage case
      delay(150);
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("1 Leave Voltage");
      while(1)
        if(PINC==0b00111110)
          break;
    break;
    
    case 0b00111101: //current case
      delay(150);
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("1 Leave Current");
      while(1)
        if(PINC==0b00111110)
          break;
    break;
    
    case 0b00111011: //resistance case
      delay(150);
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("1 Leave Resistance");
      while(1)
        if(PINC==0b00111110)
          break;
    break;
    
    case 0b00110111: //temperature case
      delay(150);
      lcd.clear();
      lcd.setCursor(0,0); lcd.print("1 Leave Temperature");
      while(1)
        if(PINC==0b00111110)
          break;
    break;
    }
  
  lcd.clear();
  delay(150);
}
