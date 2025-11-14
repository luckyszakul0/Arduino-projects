#include <Servo.h>

//  Pins declarations
const int MOTOR_DIR_1 = 4;
const int MOTOR_DIR_2 = 3;
const int MOTOR_SPEED = 5;

const int BTN_PIN = 8;
const int SERVO_CONTROL = 10;

const int JOY_ANGLE = A0;
const int JOY_SPEED = A1;

Servo baseServo;

//  Variables declarations
int servoAngle = 90;
int motorSpeed = 190;
int joyAngle, joySpeed;
bool btnPrev, btnCur, motorOn = true;

//  Other constants declarations
const int JOY_CENTER = 512;
const int NOISE_REMOVAL = 100; // Used for denying any small noise when joystick is in center position
const int SERVO_STEP = 1;
const int SPEED_STEP = 2;

int updateValue(int readValue, const int VALUE_PIN, int outputValue, const int VALUE_STEP) {
  readValue = analogRead(VALUE_PIN);
  if(readValue > JOY_CENTER + NOISE_REMOVAL){
    outputValue += VALUE_STEP;
  }else if(readValue < JOY_CENTER - NOISE_REMOVAL){
    outputValue -= VALUE_STEP;
  }

  return outputValue;
}

void setup() {
  pinMode(MOTOR_DIR_1, OUTPUT);
  pinMode(MOTOR_DIR_2, OUTPUT);
  pinMode(MOTOR_SPEED, OUTPUT);

  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(JOY_ANGLE, INPUT);
  pinMode(JOY_SPEED, INPUT);

  baseServo.attach(SERVO_CONTROL);
}

void loop() {
  btnCur = !digitalRead(BTN_PIN);

  if(btnPrev == 1 && btnCur == 0){
    motorOn = !motorOn;
  }

  if(motorOn){
    digitalWrite(MOTOR_DIR_1, LOW);
    digitalWrite(MOTOR_DIR_2, HIGH);
  }else if(!motorOn){
    digitalWrite(MOTOR_DIR_1, LOW);
    digitalWrite(MOTOR_DIR_2, LOW);
  }

  servoAngle = updateValue(joyAngle, JOY_ANGLE, servoAngle, SERVO_STEP);
  servoAngle = constrain(servoAngle, 0, 180);
  baseServo.write(servoAngle);

  motorSpeed = updateValue(joySpeed, JOY_SPEED, motorSpeed, SPEED_STEP);
  motorSpeed = constrain(motorSpeed, 125, 255);
  analogWrite(MOTOR_SPEED, motorSpeed);

  btnPrev = btnCur;

  delay(10); //  Delay given because otherwise the servo moves too fast
}
