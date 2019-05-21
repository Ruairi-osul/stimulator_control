// Used to control an electric stimulator

#include <Arduino.h>

// pin on arduino
const int Pin = 13;

void StimOn(double rate, double mins, double stimDur);

void setup()
{
  Serial.begin(9600);
  pinMode(Pin, OUTPUT);
}

void loop()
{
  double rate = 0.5;  // rate in hz
  double mins = 10;   // duration of stim
  double stimDur = 2; // in ms
  static bool haveIRun = false;

  if (!haveIRun)
  {
    StimOn(rate, mins, stimDur);
    haveIRun = true;
    Serial.println("I am done");
  }
}

void StimOn(double rate, double mins, double stimDur)
{
  double cycle = 1000 / rate;
  double offPeriod = cycle - stimDur;
  int numCycles = rate * 60 * mins;

  while (numCycles >= 0)
  {
    digitalWrite(Pin, HIGH);
    delay(stimDur);
    digitalWrite(Pin, LOW);
    delay(offPeriod);

    numCycles -= 1;
  }
}