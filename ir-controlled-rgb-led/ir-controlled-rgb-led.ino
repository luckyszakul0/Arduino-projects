#include <IRremote.hpp>
#include <LiquidCrystal.h>

const int LCD_RS_PIN = 2;
const int LCD_ENABLE_PIN = 8;
const int LCD_D4_PIN = 4;
const int LCD_D5_PIN = 5;
const int LCD_D6_PIN = 12;
const int LCD_D7_PIN = 7;

const int RGB_RED_PIN = 6;
const int RGB_GREEN_PIN = 10;
const int RGB_BLUE_PIN = 9;

const int IR_OUT_PIN = 3;

LiquidCrystal LCD(LCD_RS_PIN, LCD_ENABLE_PIN, LCD_D4_PIN, LCD_D5_PIN, LCD_D6_PIN, LCD_D7_PIN);

void writeToRGB(int Rvalue, int Gvalue, int Bvalue, int brightnessPercentage, bool powerOn){
  if(!powerOn){
    analogWrite(RGB_RED_PIN, 0);
    analogWrite(RGB_GREEN_PIN, 0);
    analogWrite(RGB_BLUE_PIN, 0);
    return;
  }

  int brightness = map(brightnessPercentage, 0, 100, 255, 0);
  Rvalue = Rvalue - brightness;
  Gvalue = Gvalue - brightness;
  Bvalue = Bvalue - brightness;
  int RealRVal = constrain(Rvalue, 0, 255);
  int RealGVal = constrain(Gvalue, 0, 255);
  int RealBVal = constrain(Bvalue, 0, 255);

  analogWrite(RGB_RED_PIN, RealRVal);
  analogWrite(RGB_GREEN_PIN, RealGVal);
  analogWrite(RGB_BLUE_PIN, RealBVal);
}

void writeToLCD(int brightnessPercentage, String colorName, bool powerOn){
  LCD.clear();
  LCD.home();

  if(!powerOn){
    LCD.print("The LED is off");
    LCD.setCursor(0, 1);
    LCD.print("Press power btn");
    return;
  }

  LCD.print("Color is: ");
  LCD.print(colorName);
  LCD.setCursor(0, 1);
  LCD.print("Brightness: ");
  LCD.print(brightnessPercentage);
  LCD.print("%");
}

void setup() {
  Serial.begin(9600);
  LCD.begin(16, 2);
  
  pinMode(RGB_RED_PIN, OUTPUT);
  pinMode(RGB_GREEN_PIN, OUTPUT);
  pinMode(RGB_BLUE_PIN, OUTPUT);

  IrReceiver.begin(IR_OUT_PIN, ENABLE_LED_FEEDBACK);

  LCD.print("The LED is off");
  LCD.setCursor(0, 1);
  LCD.print("Press power btn");
}

void loop() {
  static int brightness;
  static int RVal, GVal, BVal;
  static String colorName;
  static bool powerOn = false;

  if(IrReceiver.decode()){

    IrReceiver.printIRResultShort(&Serial);

    switch(IrReceiver.decodedIRData.command){
      case 0x45: //Power button
        RVal = 255, GVal = 255, BVal = 255;
        brightness = 100;
        colorName = "White";
        powerOn = true;
        break;
      case 0x47: //Func/stop button
        powerOn = false;
        break;
      case 0x9: //Arrow up button
        brightness += 10;
        brightness = constrain(brightness, 0, 100);
        break;
      case 0x7: //Arrow down button
        brightness -= 10;
        brightness = constrain(brightness, 0, 100);
        break;
      case 0x16: //0 button
        RVal = 255, GVal = 255, BVal = 255;
        colorName = "White";
        break;
      case 0xC: //1 button
        RVal = 255, GVal = 0, BVal = 0;
        colorName = "Red";
        break;
      // case 0x18: //2 button
      // case 0x5E: //3 button
      // case 0x8: //4 button
      // case 0x1C: //5 button
      // case 0x5A: //6 button
    }
    writeToRGB(RVal, GVal, BVal, brightness, powerOn);
    writeToLCD(brightness, colorName, powerOn);
  
    IrReceiver.resume();
  }
}
