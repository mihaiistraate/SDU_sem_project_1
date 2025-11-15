#include <LiquidCrystal_I2C.h>

//defining sensor pins
const int VOLTMETER = A0; //voltmeter input pin
const int TEMPERATURE = A1; //temperature sensor input pin
const int CURRENTMETER = A2; //currentmeter input pin
const int RESISTANCEMETER = A3; //resistancemeter input pin

//defining button pins
const int VOLT_BUTTON = 2; //voltmeter button
const int CURRENT_BUTTON = 3; //currentmeter button
const int RES_BUTTON = 4; //resistancemeter button
const int TEMP_BUTTON = 5; //temperature sensor button
const int RELAY = 6; //relay switch pin

//defining unused pins as input with pullup resistors
const int PIN_PD7 = 7; //unused pin as input pullup resistor
const int PIN_PB0 = 8; //unused pin as input pullup resistor
const int PIN_PB1 = 9; //unused pin as input pullup resistor
const int PIN_PB2 = 10; //unused pin as input pullup resistor
const int PIN_PB3 = 11; //unused pin as input pullup resistor
const int PIN_PB4 = 12; //unused pin as input pullup resistor

//defining other constants
const float V_REF = 5; //reference voltage level
const float SHUNT_RES = 1.30; //reference shunt resistor R3
const float REF_RES = 9930.00; //serial resistor R8 for the resistancemeter
const int MENU_PERIOD = 500; //disable first button for 500 ms
const float LOW_BATTERY_LEVEL = 7.5; //defining minimum level of voltage on the battery

//defining constant resistor values
const float R1 = 9920.00;
const float R2 = 3270.00;
const float R4 = 993.00;
const float R5 = 5560.00;

//global variables
int flag = 0; //keeps track of which button is pressed
float result, battery_level = 0;
unsigned long menu_timer = 0;
bool battery; //keep track if the battery has a minimum voltage

LiquidCrystal_I2C lcd(0x27, 4, 20); //0x27 address of the LCD in hexa

float get_voltage(int port)
{
  int sensorValue = 0;
  for (int i = 0; i < 20 ; ++i) //calculating the average analog voltage by taking 20 measurments
  {
    sensorValue += analogRead(port);
    delay(5);
  }
  return sensorValue * V_REF / (1023.00 * 20.00); // Convert to voltage and return the value
}

float calculate_temperature()
{
  return (get_voltage(TEMPERATURE) - 0.5) * 100; //converting to Degree Celsius
}

float calculate_resistance()
{
  return get_voltage(RESISTANCEMETER) * REF_RES / (V_REF - get_voltage(RESISTANCEMETER)); //calculate the resistance;
}

float calculate_current()
{
  float current_gain = 1+(R5/R4);
  return get_voltage(CURRENTMETER) * 1000.00 / (current_gain * SHUNT_RES); //calculate the current in mA
}

float calculate_voltage()
{
  float resistor_ratio = R2 / (R1 + R2);
  return get_voltage(VOLTMETER) / resistor_ratio; //calculate the voltage
}

void battery_check()
{
  digitalWrite(RELAY, HIGH);
  battery_level = calculate_voltage();
  digitalWrite(RELAY, LOW);
  if(battery_level < LOW_BATTERY_LEVEL) battery = false; // keeping track of the battery level using a bool variable
  else battery = true;
}

void menu()
{
  lcd.clear();
  lcd.setCursor(0,0);lcd.print("Press 1 - Temp."); //displaying the choices on the main menu
  lcd.setCursor(0,1);lcd.print("Press 2 - Resistance");
  lcd.setCursor(0,2);lcd.print("Press 3 - Current");
  lcd.setCursor(0,3);lcd.print("Press 4 - Voltage");
}

//implementing the stopwatch
bool running = false;
int activecnt = 0;
struct time_t{
  int hours, min, sec;
  long int msec;
} counter, split;

void reset(){
  counter.hours = counter.min = counter.sec = counter.msec = 0; //this is how the time is resetted, when 2&3 are being pressed
}

void print(int y, int line, struct time_t counter, bool on){
  lcd.setCursor(y, line);
  lcd.print("          ");
  lcd.setCursor(y, line);
  counter.hours = counter.msec / 3600000;
  counter.min = (counter.msec - counter.hours * 3600000) / 60000;
  counter.sec = (counter.msec - counter.hours * 3600000 - counter.min * 60000)/ 1000;
  if (on == false)
  {
  int msec = counter.msec - counter.hours * 3600000 - counter.min * 60000 - counter.sec * 1000;
  if(counter.hours < 10) lcd.print("0");
  lcd.print(counter.hours);
  lcd.print(':');
  if(counter.min < 10) lcd.print("0");
  lcd.print(counter.min);
  lcd.print(':');
  if(counter.sec < 10) lcd.print("0");
  lcd.print(counter.sec);
  }
  else{
    if(counter.hours < 10) lcd.print("0");
    lcd.print(counter.hours);
    lcd.print(':');
    if(counter.min < 10) lcd.print("0");
    lcd.print(counter.min);
    lcd.print(':');
    if(counter.sec < 10) lcd.print("0");
    lcd.print(counter.sec);
  }
}

void setup()
{
  //initializing the LCD  
  lcd.init(); //initializing LCD
  lcd.backlight(); //turning the backlight on for the LCD

  //initializing sensor pins
  pinMode(VOLTMETER, INPUT); //configuring sensor pin as input for voltmeter
  pinMode(TEMPERATURE, INPUT); //configuring sensor pin as input for temperature sensor
  pinMode(CURRENTMETER, INPUT); //configuring sensor pin as input for currentmeter
  pinMode(RESISTANCEMETER, INPUT); //configuring sensor pin as input for resistancemeter
  pinMode(RELAY, OUTPUT); //configuring pin as output for relay

  //initializing button pins
  pinMode(VOLT_BUTTON, INPUT_PULLUP); //configuring button pin as input with pullup resistor for voltmeter
  pinMode(CURRENT_BUTTON, INPUT_PULLUP); //configuring button pin as input with pullup resistor for currentmeter
  pinMode(RES_BUTTON, INPUT_PULLUP); //configuring button pin as input with pullup resistor for resistancemeter
  pinMode(TEMP_BUTTON, INPUT_PULLUP); //configuring button pin as input with pullup resistor for temperature sensor

  //initializing unused pins as input with pullup resistors
  pinMode(PIN_PD7, INPUT_PULLUP); //configuring pin as input with pullup resistor
  pinMode(PIN_PB0, INPUT_PULLUP); //configuring pin as input with pullup resistor
  pinMode(PIN_PB1, INPUT_PULLUP); //configuring pin as input with pullup resistor
  pinMode(PIN_PB2, INPUT_PULLUP); //configuring pin as input with pullup resistor
  pinMode(PIN_PB3, INPUT_PULLUP); //configuring pin as input with pullup resistor
  pinMode(PIN_PB4, INPUT_PULLUP); //configuring pin as input with pullup resistor

  //welcome message
  lcd.setCursor(7,2); lcd.print("WELCOME!");
  lcd.setCursor(0, 3); lcd.print("BSC GROUP MULTIMETER");
  delay(3000);
  lcd.clear();
  delay(1000);
  
  //battery level check
  battery_check();
  if(battery)
  {
    lcd.setCursor(2,2); lcd.print("BATTERY LEVEL OK"); //displaying a message to show that the battery level is ok
  }
  else //displaying a message to suggest to replace the battery
  {
    lcd.setCursor(2,0); lcd.print("BATTERY LEVEL LOW");
    lcd.setCursor(3,1); lcd.print("Please replace");
    lcd.setCursor(4,2); lcd.print("the battery");
  }
  delay(3000);
  lcd.clear();
  delay(1000);
  menu(); //showing the main menu
}

void loop()
{
  if(digitalRead(TEMP_BUTTON) == LOW)
  {
    if(millis() >= menu_timer)
    {  
      if(flag != 0) //if the first button if pressed within a measurment option, the menu will be shown
      {
        menu();
        flag = 0;
      }
      else //setting the variable which keeps track of which button has been pressed (flag) accordingly
      {
        flag = 1;
        lcd.clear();
      }
      menu_timer = millis() + MENU_PERIOD;
    }
  }
  if(digitalRead(RES_BUTTON) == LOW)
  {
    if(flag == 0) //setting the variable which keeps track of which button has been pressed (flag) accordingly
    {
      flag = 2;
      lcd.clear();
    }
  }
  if(digitalRead(CURRENT_BUTTON) == LOW)
  {
    if(flag == 0) //setting the variable which keeps track of which button has been pressed (flag) accordingly
    {
      flag = 3;
      lcd.clear();
    }
  }
  if(digitalRead(VOLT_BUTTON) == LOW)
  {
    if(flag == 0) //setting the variable which keeps track of which button has been pressed (flag) accordingly
    {
      flag = 4;
      lcd.clear();
    }
  }
  if((digitalRead(RES_BUTTON) == LOW) && (digitalRead(CURRENT_BUTTON) == LOW))
  {
    if((flag == 2) || (flag == 3)) //if both the second and the third buttons are pressed, the multimeter will show the battery level 
    {
      flag = 10;
      lcd.clear();
    }
  }
  if((digitalRead(TEMP_BUTTON) == LOW) && (digitalRead(VOLT_BUTTON) == LOW))
  {
    if((flag == 1) || (flag == 4))  //if both the first and the fourth buttons are pressed, the multimeter will show a stopwatch 
    {
      flag = 11;
      lcd.clear();
    }
  }

  switch (flag)
  {
    case 1:
      lcd.setCursor(0,0); lcd.print("Press 1 - Menu");
      lcd.setCursor(0,1); lcd.print("Between -55 - +150"); lcd.print((char)223); lcd.print("C");
      lcd.setCursor(0, 2); // Display the measured temperature on the LCD
      lcd.print("Temperature ("); lcd.print((char)223); lcd.print("C):");
      lcd.setCursor(0, 3);
      lcd.print("                    ");
      lcd.setCursor(0, 3); lcd.print(calculate_temperature());
    break;

    case 2:
      result = calculate_resistance();
      lcd.setCursor(0,0); lcd.print("Press 1 - Menu");
      lcd.setCursor(0,1); lcd.print("Between 120-180k Ohm");
      lcd.setCursor(0, 2); // Display the measured resistance on the LCD
      lcd.print("Resistance (Ohm):");
      lcd.setCursor(0, 3);
      lcd.print("                    ");
      lcd.setCursor(0, 3);
      if (result > 180000 || result < 120)
      lcd.print("Cannot calculate");
      else lcd.print(result);
    break;

    case 3:
      lcd.setCursor(0,0); lcd.print("Press 1 - Menu");
      lcd.setCursor(0,1); lcd.print("Do not exceed 500mA");
      lcd.setCursor(0, 2); // Display the measured current on the LCD
      lcd.print("Current (mA):");
      lcd.setCursor(0, 3);
      lcd.print("                    ");
      lcd.setCursor(0, 3); lcd.print(calculate_current());
    break;

    case 4:
      lcd.setCursor(0,0); lcd.print("Press 1 - Menu");
      lcd.setCursor(0,1); lcd.print("Do not exceed 20V");
      lcd.setCursor(0, 2); // Display the measured voltage on the LCD
      lcd.print("Voltage (V):");
      lcd.setCursor(0, 3);
      lcd.print("                    ");
      lcd.setCursor(0, 3); lcd.print(calculate_voltage());
    break;

    case 10:
      battery_check();
      lcd.setCursor(0,0); lcd.print("Press 1 - Menu");
      lcd.setCursor(0, 2); // Display the measured voltage of the battery on the LCD
      lcd.print("Battery level (V):");
      lcd.setCursor(0, 3);
      lcd.print("                    ");
      lcd.setCursor(0, 3); lcd.print(battery_level);
    break;

    case 11:
      lcd.setCursor(0,0); lcd.print("1-Menu,2-Run,3-Stop"); //showing how to operate the stopwatch
      lcd.setCursor(0, 1); lcd.print("4-Split, 2&3 - Reset");        
      if(digitalRead(RES_BUTTON) == LOW) //the second button is pressed - start/resume
      running=true;
      if(digitalRead(CURRENT_BUTTON) == LOW) //the third button is pressed - stop
      running=false;
      if(digitalRead(VOLT_BUTTON) == LOW) //the fourth button is pressed - split
      print(12, 3, counter, false);
      if(digitalRead(CURRENT_BUTTON) == LOW && digitalRead(RES_BUTTON) == LOW) //the second and third button are pressed - reset
      {
        running=false;
        reset();
        lcd.clear();
      }
      lcd.setCursor(0, 2);
      if (running == true) //if the stopwatch is running, it will state that and it will print the current time
      {
        lcd.print("Running:            ");
        print(0, 3, counter, true); //the time is printed by calling this function
        counter.msec += 200; //time is increased with this variable
        delay(78);
      }
      else
      {
        lcd.print("The counter is:     "); //if the stopwatch is stoped, it will state that and print the time
        print(0, 3, counter, false); //the time is printed by calling this function
      }
    break;

    default:
    break;
  }
}
