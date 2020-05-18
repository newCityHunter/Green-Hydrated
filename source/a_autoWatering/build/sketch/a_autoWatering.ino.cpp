#include <Arduino.h>
#line 1 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\a_autoWatering.ino"
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

int LED = 13;
int valve = 12;
bool turnOn = false;

#line 9 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\a_autoWatering.ino"
void setup();
#line 24 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\a_autoWatering.ino"
void loop();
#line 12 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\b_setTime.ino"
void setThisDate();
#line 46 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\b_setTime.ino"
bool getTime(const char *str);
#line 57 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\b_setTime.ino"
bool getDate(const char *str);
#line 4 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\c_getTime.ino"
void displayDate();
#line 36 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\c_getTime.ino"
void print2digits(int number);
#line 45 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\c_getTime.ino"
bool alarm(int Hour, int Minute , int Second);
#line 9 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\a_autoWatering.ino"
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

#line 1 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\b_setTime.ino"
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

tmElements_t tm;

void setThisDate()
{
  bool parse = false;
  bool config = false;

  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);
  if (parse && config) {
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } else if (parse) {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } else {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }
}

bool getTime(const char *str)
{
  int Hour, Min, Sec;

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}

bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

#line 1 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\c_getTime.ino"
#include <TimeLib.h>
#include <DS1307RTC.h>

void displayDate()
{
  tmElements_t tm;

  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
}

void print2digits(int number)
{
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

//Set Alarm to 07:00:00 and 19:00:00
bool alarm(int Hour, int Minute , int Second)
{
  if ((Hour == 7 || Hour == 19 ) && (Minute >= 00 && Minute <= 15)) return true;
  else return false;
}

