#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

const int LED = 13;
const int valve = 12;
const int btnSetTime = 2;
bool turnOn = false;

void setup()
{
  //Start the serial port
  Serial.begin(9600);

  //Start the I2C interface
  Wire.begin();

  //Set led
  pinMode(LED, OUTPUT);

  //Set Valve
  pinMode(valve, OUTPUT);

  //Set Button Set Time and handle interrupt
  pinMode(btnSetTime, INPUT_PULLUP);
}

// display time on Serial and check Alarm
void displayTime() {
  displayDate();
  tmElements_t tm;
  if (RTC.read(tm))
  {
    turnOn = alarm(tm.Hour, tm.Minute);
    if (turnOn == true) {
      Serial.println("The valve is turned on");
      digitalWrite(valve, HIGH);
      digitalWrite(LED, HIGH);
    } if (turnOn == false)
    {
      digitalWrite(valve, LOW);
      digitalWrite(LED, LOW);
    }
  }
}

void loop()
{
  if (digitalRead(btnSetTime) == HIGH)
  {
    setThisDate();
    Serial.println("===Time is reseted===");
  } else {
    displayTime();
  }
}
