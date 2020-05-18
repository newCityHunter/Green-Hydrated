# 1 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\a_autoWatering.ino"
# 2 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\a_autoWatering.ino" 2
# 3 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\a_autoWatering.ino" 2
# 4 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\a_autoWatering.ino" 2

int LED = 13;
int valve = 12;
bool turnOn = false;

void setup() {
  //Start the serial port
  Serial.begin(9600);

  //Start the I2C interface
  Wire.begin();

  //Set led
  pinMode(LED, 0x1);
  pinMode(valve, 0x1);

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
      digitalWrite(valve, 0x1);
      digitalWrite(LED, 0x1);
    } else
    {
      digitalWrite(valve, 0x0);
      digitalWrite(LED, 0x0);
    }
  }
}
# 1 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\b_setTime.ino"
# 2 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\b_setTime.ino" 2
# 3 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\b_setTime.ino" 2
# 4 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\b_setTime.ino" 2

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
  if (getDate("May 18 2020") && getTime("10:21:33")) {
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
    Serial.print("10:21:33");
    Serial.print(", Date=");
    Serial.println("May 18 2020");
  } else if (parse) {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } else {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print("10:21:33");
    Serial.print("\", Date=\"");
    Serial.print("May 18 2020");
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
  tm.Year = ((Year) - 1970);
  return true;
}
# 1 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\c_getTime.ino"
# 2 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\c_getTime.ino" 2
# 3 "E:\\workSpace\\Personal_Project\\Auto_Watering\\source\\a_autoWatering\\c_getTime.ino" 2

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
    Serial.print(((tm.Year) + 1970) /* full four digit year */);
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
