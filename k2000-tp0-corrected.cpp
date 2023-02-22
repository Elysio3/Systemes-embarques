/**
 * Project K2000 - V1
 * @title : Make leds wave-blink
 * @Author : Elysio / Maël KERVICHE
 **/

// time between each led
int delayTime = 750;

// the led id (start at 0)
int currentLED = 0;

// trajectory's direction (+1/-1)
int direction = 1;

// led's id array
byte led[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

void setup()
{
    // setup code, run once

    // for each led
    for (int i = 0; i < 9; i++)
    {
        // init OUTPUT
        pinMode(led[i], OUTPUT);
    }

    Serial.begin(9600);
}

void loop()
{
    // main code, run repeatedly

    // time interval (read from 'potentiometre')
    // with security 5ms delay if time equals 0
    delay(analogRead(0));
    delay(5);

    // turn off all leds
    for (int i = 0; i < 10; i++)
    {
        digitalWrite(led[i], LOW);
    }

    // blink current led once
    digitalWrite(led[currentLED], HIGH);
    delay(100);
    digitalWrite(led[currentLED], LOW);

    // move to next led
    currentLED = currentLED + direction;

    // if moved to last id
    if (currentLED <= 0)
    {
        // change direction
        direction = 1;
    }
    else if (currentLED >= 9)
    {
        // change direction
        direction = -1;
    }
}
