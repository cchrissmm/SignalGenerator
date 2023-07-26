#include <Arduino.h>

const float FREQUENCY = 60;
const float DUTY_CYCLE = 0.5; 
const int OUTPIN = 13;
const int NUMCYCLES = 1000;



void squareWave()
{
  // Calculate the period of the wave based on the frequency
  float period = 1 / FREQUENCY;

  // Calculate the duration of the high state based on the duty cycle
  float highDuration = period * DUTY_CYCLE * 1000000;

  // Calculate the duration of the low state
  float lowDuration = period * (1 - DUTY_CYCLE) * 1000000;

  // Generate the square wave
  
  
  Serial.println("Starting");
  for (int i = 0; i < NUMCYCLES; i++)
  {
    digitalWrite(OUTPIN, HIGH);
    //Serial.println("high");
    delayMicroseconds((int)highDuration);
    digitalWrite(OUTPIN, LOW);
    //Serial.println("low");
    delayMicroseconds((int)lowDuration);
  }
  Serial.println("Finished");
  
  
}

void serialRX()
{
  if (Serial.available())
  {
    String str = Serial.readStringUntil('\n');

    if (str.startsWith("R")) // starting check for "VAR"
    {
      Serial.println("VAR recieved: " + str);
      squareWave();
    }
  }
}

void setup()
{
  Serial.begin(115200);
  pinMode(OUTPIN, OUTPUT); 
  digitalWrite(OUTPIN, LOW);
  Serial.println("Signal Generator");
  Serial.println("Frequency: " + String(FREQUENCY) + "Hz");
  Serial.println("Duty Cycle: " + String(DUTY_CYCLE * 100) + "%");
  Serial.println("Output Pin: " + String(OUTPIN));
  Serial.println("Press R to start");
}

void loop()
{
  serialRX();
  
}