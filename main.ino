#include <Arduino.h>

#define BRUSHCOUNTER 5
#define BLINKINT 200

//boolean newDay = true;

int brushTime = BRUSHCOUNTER *1000 / BLINKINT;

struct Brush
{   boolean timerStarted;
    boolean newDay;
    int inputPin;
    int redPin;
    int greenPin;
    int counter;
    int pinState;
    unsigned long startTime;
    const char text[22];

};

struct Brush BrushA =
    {
    .timerStarted = false,
    .newDay = true,
     .inputPin = 5,
     .redPin = 3,
     .greenPin = 10,
     .counter = 0,
     .pinState = 1,
     .startTime = 0,
     .text = "this is from struct A"
     };

struct Brush BrushB =
    {
    .timerStarted = false,
    .newDay = true,
     .inputPin = 6,
     .redPin = 2,
     .greenPin = 10,
     .counter = 0,
     .pinState = 1,
     .startTime = 0,
     .text = "this is from struct B"
     };



void checkState(struct Brush *brush)
{
    int tmpBrush = brush->inputPin; //Does not change

    if (digitalRead(tmpBrush) == LOW && brush->newDay)
    {
        brush->newDay = false;

        brush->startTime = millis();

        brush->timerStarted = true;
    }

    if (brush->timerStarted)
    {
        unsigned long currentTime = millis();

        if (currentTime - brush->startTime > BLINKINT)
        {
            brush->startTime = currentTime;

            brush->pinState ^= 1;

            digitalWrite(brush->redPin, brush->pinState);

            brush->counter++;

            //countTime(&counter);

            Serial.println(brush->counter);

            if (brush->counter == brushTime)
            {
                Serial.println("Done");

                brush->counter = 0;

                brush->timerStarted = false;

                brush->newDay = true;

                //digitalWrite(3, LOW);

                digitalWrite(brush->redPin, HIGH);
            }
        }
    }
}


void setup()
{
    // put your setup code here, to run once:

    pinMode(2, OUTPUT);
    pinMode(3, OUTPUT);

    pinMode(5, INPUT_PULLUP);
    pinMode(6, INPUT_PULLUP);

    Serial.begin(9600);

    Serial.println(BrushA.inputPin);
}

void loop()
{
     checkState(&BrushA);
     checkState(&BrushB);
   
}
