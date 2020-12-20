#include <RTClib.h>
#include <LiquidCrystal.h>

#define alarmPin 8
#define alarmNum 4
#define hourSet 3
#define minSet 2
#define buzzer 10
#define numberOfAlarms 2
#define R_LED 6
#define G_LED 9
#define B_LED 11

LiquidCrystal lcd(A0,A1,A2,A3,12,13);
RTC_DS3231 RTC;

uint8_t brightness = 255;
const char* DOW[7] = {"Sun ", "Mon ", "Tue ", "Wed ", "Thu. ", "Fri ", "Sat "};

// mode 0 is neither, mode 1 is set alarm 1, mode 2 is set alarm 2
uint8_t alarmset_mode = 0;
// the hour set on alarm 1
uint8_t alarm_hr_1 = 0;
// the minute set on alarm 2
uint8_t alarm_min_1 = 0;
// the hour set on alarm 2
uint8_t alarm_hr_2 = 0;
// the minute set on alarm 2
uint8_t alarm_min_2 = 0;
// mode 0 is neither alarm, mode 1 is first alarm, mode 2 is second alarm, mode 3 is both
uint8_t alarm_active = 0;

uint16_t hourupg;
uint16_t minupg;
uint16_t secupg;
uint16_t yearupg;
uint16_t monthupg;
uint16_t dayupg;
uint16_t weekdayupg;

void setup() {
  // initialize LCD screen
  lcd.begin(20,4);
  lcd.clear();
  
  // pinmode sets
  pinMode(buzzer, OUTPUT);
  pinMode(R_LED, OUTPUT);
  pinMode(B_LED, OUTPUT);
  pinMode(G_LED, OUTPUT);
  pinMode(minSet, INPUT_PULLUP);
  pinMode(hourSet, INPUT_PULLUP);
  pinMode(alarmNum, INPUT_PULLUP);
  pinMode(alarmPin, INPUT_PULLUP);

  setBacklight(255,255,255);
  analogWrite(buzzer, 255);

  // clock and wire begin
  RTC.begin();

  // configure RTC
  if (RTC.lostPower()) {
    // set time at compile time
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
    alarmset_mode = 0;
  }

  
}

void loop() {
  // read four buttons and adjust values
  // alarmNum controls which alarm is being set right now
  if(digitalRead(alarmNum) == LOW) {
    alarmset_mode = alarmset_mode+1;
    alarmset_mode = alarmset_mode%(numberOfAlarms+1);
    beep(20, 150);
    delay(150);
  }
  // alarmPin/alarm_active controls which alarms are on
  if(digitalRead(alarmPin) == LOW){
    alarm_active = alarm_active+1;
    alarm_active = alarm_active%4;
    beep(20, 150);
    delay(150);
  }
  if(digitalRead(minSet) == LOW){
    if(alarmset_mode == 1){
      alarm_min_1 = alarm_min_1+1;
      alarm_min_1 = alarm_min_1%60;
       beep(20, 150);
    }
    if(alarmset_mode == 2){
      alarm_min_2 = alarm_min_2+1;
      alarm_min_2 = alarm_min_2%60;
      beep(20, 150);
    }
  }
  if(digitalRead(hourSet) == LOW){
    if(alarmset_mode == 1){
      alarm_hr_1 = alarm_hr_1+1;
      alarm_hr_1 = alarm_hr_1%24;
      beep(20, 150);
    }
    if(alarmset_mode == 2){
      alarm_hr_2 = alarm_hr_2+1;
      alarm_hr_2 = alarm_hr_2%24;
      beep(20, 150);
    }
  }
  // display clock face
  getTimeDate();
  showTime();
  showDate();
  showAlarm(0);
  showAlarm(1);
  alarmCheck();
  // delay between screen updates
  delay(150);
}

void getTimeDate(){
  // get current time
  DateTime currTime = RTC.now();

  // store time and dates
  hourupg = currTime.hour();
  minupg = currTime.minute();
  secupg = currTime.second();
  yearupg = currTime.year();
  monthupg = currTime.month();
  dayupg = currTime.day();
  weekdayupg = currTime.dayOfTheWeek();
}

void showTime(){
  // print out current time
  lcd.setCursor(0,0);
  lcd.print("   TIME: ");
  // hour with padded 0's
  if(hourupg < 10) {
    lcd.print("0");
  }
  lcd.print(hourupg);
  lcd.print(":");
  // minute
  if(minupg < 10) {
    lcd.print("0");
  }
  lcd.print(minupg);
  lcd.print(":");
  // second
  if(secupg < 10) {
    lcd.print("0");
  }
  lcd.print(secupg);
}

void showDate(){
  // print out current time
  lcd.setCursor(0,1);
  lcd.print("DATE: ");
  lcd.print(DOW[weekdayupg]);
  // hour with padded 0's
  if(monthupg < 10) {
    lcd.print("0");
  }
  lcd.print(monthupg);
  lcd.print("-");
  // minute
  if(dayupg < 10) {
    lcd.print("0");
  }
  lcd.print(dayupg);
  lcd.print("-");
  // second
  if(yearupg < 10) {
    lcd.print("0");
  }
  lcd.print(yearupg);
}

void showAlarm(int alarmSelect){
  if(alarmSelect == 0){
    lcd.setCursor(0,2);
    lcd.print("ALARM 1: ");
    if(alarm_hr_1 < 10) {
    lcd.print("0");
    }
    lcd.print(alarm_hr_1);
    lcd.print(":");
    // minute
    if(alarm_min_1 < 10) {
      lcd.print("0");
    }
    lcd.print(alarm_min_1);
    if((alarm_active == 1) || (alarm_active == 3)){
      lcd.print(" ON ");
    }
    else {
      lcd.print(" OFF");
    }
    // show alarmset character
    if(alarmset_mode == 1){
      lcd.print(" X");
    }
    else{
      lcd.print("  ");
    }
    
  }
  if(alarmSelect == 1){
    lcd.setCursor(0,3);
    lcd.print("ALARM 2: ");
    if(alarm_hr_2 < 10) {
    lcd.print("0");
    }
    lcd.print(alarm_hr_2);
    lcd.print(":");
    // minute
    if(alarm_min_2 < 10) {
      lcd.print("0");
    }
    lcd.print(alarm_min_2);
    if((alarm_active == 2) || (alarm_active == 3)){
      lcd.print(" ON ");
    }
    else {
      lcd.print(" OFF");
    }
    // show alarmset character
    if(alarmset_mode == 2){
      lcd.print(" X");
    }
    else{
      lcd.print("  ");
    }
  }
}

// check to see if either (active) alarm is triggered
void alarmCheck() {
  if((hourupg == alarm_hr_1) && (minupg == alarm_min_1) && ((alarm_active == 1) || (alarm_active == 3))){
    alarmTriggered(1);
  }
  if((hourupg == alarm_hr_2) && (minupg == alarm_min_2) && ((alarm_active == 2) || (alarm_active == 3))){
    alarmTriggered(2);
  }
}

// trigger an alarm cycle for 60 seconds or when alarm reset is pressed. turn off alarm (1 -> 0, 2 -> 0, 3 -> 1 or 2)
void alarmTriggered(int alarm_triggered){
  unsigned long triggerTime = millis();
  // buzzer cycle
  while(((millis() - triggerTime) < (unsigned long) 120000)){
    if(digitalRead(alarmPin) == LOW){
      break;
    }
    lcd.noDisplay();
    beep(100, 150);
    lcd.display();
    delay(250);
  }
  delay(200);
  // reset alarm
  switch(alarm_active){
    case 1:
    case 2:
      alarm_active = 0;
      break;
    case 3:
      alarm_active = alarm_active - alarm_triggered;
      break;
  }
}

// generate beep off pin 9 (buzzer)
void beep(uint16_t duration, uint8_t freq){
  // generate beep for duration (in ms) and of frequency
  analogWrite(buzzer, freq);
  delay(duration);
  analogWrite(buzzer, 255);
  delay(duration);
}

void setBacklight(uint8_t r, uint8_t g, uint8_t b) {
  // common anode so invert analog values
  r = map(r, 0, 255, 255, 0);
  g = map(g, 0, 255, 255, 0);
  b = map(b, 0, 255, 255, 0);
  
  analogWrite(R_LED, r);
  analogWrite(G_LED, g);
  analogWrite(B_LED, b);
}
