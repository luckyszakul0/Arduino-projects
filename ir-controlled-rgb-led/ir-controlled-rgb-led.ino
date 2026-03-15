#include <IRremote.h>
#include <LiquidCrystal.h>

const int LCD_RS_PIN = 2;
const int LCD_ENABLE_PIN = 8;
const int LCD_D4_PIN = 4;
const int LCD_D5_PIN = 5;
const int LCD_D6_PIN = 6;
const int LCD_D7_PIN = 7;
const int RGB_RED_PIN = 11;
const int RGB_GREEN_PIN = 10;
const int RGB_BLUE_PIN = 9;
const int IR_OUT_PIN = 3;

IRrecv IR(IR_OUT_PIN);
decode_results btnPressed;
LiquidCrystal LCD(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

void writeToRGB(int Rvalue, int Gvalue, int Bvalue, int brightnessPercentage){
  LCD.clear();
  int brightness = map(brightnessPercentage, 10, 100, 240, 0);

  analogWrite(RGB_RED_PIN, (Rvalue - brightness));
  analogWrite(RGB_GREEN_PIN, (Gvalue - brightness));
  analogWrite(RGB_BLUE_PIN, (Bvalue - brightness));
}

void writeToLCD(int brighntessPercentage, String colorName){
  LCD.clear();
  LCD.home();
  LCD.print("Color is: ");
  LCD.print(colorName);
  LCD.setCursor(0, 1);
  LCD.print("Brightness: ");
  LCD.print(brightnessPercentage);
  LCD.print("%");
}

void setup() {
  LCD.begin(16, 2);
  IR.enableIRIn();
  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);
}

void loop() {
  static int brightness = 100

  LCD.home();
  LCD.print("LED is off");
  while(IR.decode(&btnPressed)){}
  switch(btnPressed.value){
    case 0xFFA25D: //Power button
      writeToRGB(255, 255, 255, 100, "White");
      writeToLCD(100, "White");
      break;
    case 0xFFE21D: //Func/stop button
      writeToRGB();
    case 0xFF906F: //Arrow up button
    case 0xFFE01F: //Arrow down button
    case 0xFF6897: //0 button
    case 0xFF30CF: //1 button
    case 0xFF18E7: //2 button
    case 0xFF7A85: //3 button
    case 0xFF10EF: //4 button
    case 0xFF38C7: //5 button
    case 0xFF5AA5: //6 button
  }
  delay(250);
  IR.resume();
}
