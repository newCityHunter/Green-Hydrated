#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

int LED = 13;
int valve = 12;
bool turnOn = false;

void setup() {
  //Start the serial port
  Serial.begin(9600);

  //Start the I2C interface
  Wire.begin();

  //Set led
  pinMode(LED, OUTPUT);
  pinMode(valve, OUTPUT);

  //Set time
  setThisDate();
}

void loop() {
  displayDate();
  tmElements_t tm;

  if (RTC.read(tm))
  {
    turnOn = alarm(tm.Hour, tm.Minute, tm.Second);
    if(turnOn == true){
      Serial.println("The valve is turned on");
      digitalWrite(valve, HIGH);
      digitalWrite(LED, HIGH);
    } else
    {
      digitalWrite(valve, LOW);
      digitalWrite(LED, LOW);
    }
  }
}
