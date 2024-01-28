
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
long hour = 00, minute = 10, second = 00;
long countdown_time = (hour*3600) + (minute * 60) + second;

void setup() {
lcd.begin(16, 2);
}


void loop() {

  long countdowntime_seconds = countdown_time - (millis() / 1000);
  if (countdowntime_seconds >= 0) {
    long countdown_minute = ((countdowntime_seconds / 60)%60);
    long countdown_sec = countdowntime_seconds % 60;

    lcd.setCursor(0, 1);
    
    lcd.print("Cook time: ");
    if (countdown_minute < 10) {
      lcd.print("0");
    }
    lcd.print(countdown_minute);
    lcd.print(":");
    if (countdown_sec < 10) {
      lcd.print("0");
    }
    lcd.print(countdown_sec);
    }



}
