#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);

int pastaState = 0, groupButtonIndex = 0; 
int timerButtonState = 0, lastTimerButtonState = 0;
unsigned long startTime, elapsedTime;

bool type1 = false;
bool type2 = false;
bool type3 = false;

int tracker = 0;  


String millisToHHMM(long millisecond) {
  int hour, minute;
  String hour_s, minute_s;
  hour = floor(millisecond / 60000);
  minute = floor((millisecond % 60000) / 1000);

  hour_s = String(hour);
  minute_s = String(minute);

  if (hour < 10) {
    hour_s = "0" + hour_s;
  }

  if (minute < 10) {
    minute_s = "0" + minute_s;
  }

  return hour_s + ":" + minute_s;
}

// timer 1 for 8 minutes
void timer1() {

  unsigned long currentTime = millis();
  
  elapsedTime = currentTime - startTime;
  lcd.setCursor(7, 1);

  if (elapsedTime >= 480000) {
    lcd.print("Pasta Done!");
  }
  else {
    lcd.print(millisToHHMM(480000 - elapsedTime));
  }
}

// timer 2 for 10 minutes
void timer2() {
  
  unsigned long currentTime = millis();
  
  elapsedTime = currentTime - startTime;
  lcd.setCursor(7, 1);

  if (elapsedTime >= 600000) {
    lcd.print("Pasta Done!");
  }
  else {
    lcd.print(millisToHHMM(600000 - elapsedTime));
  }
}

// timer 3 for 12 minutes
void timer3() {
  
  unsigned long currentTime = millis();
  
  elapsedTime = currentTime - startTime;
  lcd.setCursor(7, 1);

  if (elapsedTime >= 720000) {
    lcd.print("Pasta Done!");
  }
  else {
    lcd.print(millisToHHMM(720000 - elapsedTime));
  }
}



void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Ask the");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("Pasta Timer!");
}


void loop() {
  pastaState = digitalRead(12);
  timerButtonState = digitalRead(13);
  
  if (timerButtonState == 0) { // timer button not pressed
    if (lastTimerButtonState == 1&& type1 == true) { // continue timer if timer has started
        timer1();
      }
    if(lastTimerButtonState == 1 && type2 == true){
        timer2();
    }
    if(lastTimerButtonState == 1 && type3 == true){
        timer3();
    }
      
    if (pastaState == 1) {
        pastaFirm();
      }

    }
    
    else { // timer button pressed
      if (lastTimerButtonState == 0) { // if timer button has not been pressed before then start new timer
        startTime = millis(); // capture current "time"
        lastTimerButtonState = 1;
      }
    }


  delay(200);
}

void pastaFirm(){
    tracker += 1;
    lcd.clear();

    if(tracker > 3){
      tracker-=3;
    }

    //tracker increase cuasing the options to change
    switch(tracker){

    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Molto dente");
      type1 = true;
      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Al dente");
      type2 = true;
      break;

    case 3:
      lcd.setCursor(0, 0);
      lcd.print("Stracotto");
      type3 = true;
      break;
    
  }

}

