/**
 * Project Light Pet - Self Defense Edition
 * @title : Light-Pet with deadly counter-measures
 * @Author : Elysio / Maël KERVICHE
 * @description : find out yourself
 **/

// include libraries

// LCD (with initializattion)
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

// ServoMotor
#include <Servo.h>
#include <SoftwareSerial.h>

// global variables

// infraredSensor
const int infraredSensor_ID = 13;
int infraredSensor_Value = 0;

// UltraSoundSensor
const int ultraSoundSensorTrig_ID = 11;
const int ultraSoundSensorEcho_ID = 12;
int ultraSoundSensorTrig_Value = 0;
int ultraSoundSensorEcho_Value = 0;

// utilities for UltraSoundSensor
int mesure = 0;
int distance = 0;
int lastDistance = 101;

// ServoMotor
Servo servo;

// setup pins and utilities
void setup()
{
  // initializing serial monitor
  Serial.begin(9600);

  // initializing ServoMotor
  servo.attach(9);
  servo.write(0);

  // setup the UltraSoundSensor
  pinMode(ultraSoundSensorTrig_ID, OUTPUT);
  pinMode(ultraSoundSensorEcho_ID, INPUT);

  // setup the LCD mode to 1602
  lcd.begin(16, 2);
  lcd.print("Welcome, Slayer!");
  delay(3000);
}

// while running, reap-eat
void loop()
{

  infraredSensor_Value = digitalRead(infraredSensor_ID);

  // no enemies detected
  if (infraredSensor_Value == LOW)
  {

    // checking if target is still (something in range)
    // send a scan by ulstraSouund (10µs)
    digitalWrite(ultraSoundSensorTrig_ID, 1);
    delayMicroseconds(10);
    digitalWrite(ultraSoundSensorTrig_ID, 0);

    int currMesure = pulseIn(ultraSoundSensorEcho_ID, 1);
    int currDistance = ((mesure)*0.017);

    // target got still
    if ((lastDistance == currDistance) && (currDistance <= 100))
    {
      firing();
    }
    else
    {
      lcd.setCursor(0, 0);
      lcd.print("NoTargetDetected");
      lcd.setCursor(0, 1);
      lcd.print("Ready to Slay");
    }

    // enemies detected
  }
  else
  {
    firing();
  }
  delay(250);
}

void firing()
{

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Target Detected");

  // send a scan by ulstraSouund (10µs)
  digitalWrite(ultraSoundSensorTrig_ID, 1);
  delayMicroseconds(10);
  digitalWrite(ultraSoundSensorTrig_ID, 0);

  mesure = pulseIn(ultraSoundSensorEcho_ID, 1);
  distance = ((mesure)*0.017);

  // check distance to fire
  // if target closer than 100cm, firing
  if (distance <= 100)
  {
    lcd.setCursor(0, 1);
    lcd.print("Firing (" + String(distance) + ")");
    lastDistance = distance;

    // moving ServoMotor (shoot)
    for (int i = 0; i <= 180; i++)
    {
      servo.write(i);
      delay(15);
    }
    // moving ServoMotor (reset)
    for (int i = 0; i >= 180; i--)
    {
      servo.write(i);
      delay(15);
    }

    // if target is further than 100cm, waiting
  }
  else
  {
    lcd.setCursor(0, 1);
    lcd.print(String(distance) + " cm");
    lastDistance = distance;
  }
}
