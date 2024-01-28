
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// set up a constant for the tilt switch pin
const int switchPin = 13;

// variable to hold the value of the switch pin
int switchState = 0;

// variable to hold previous value of the switch pin
int prevSwitchState = 0;

// a variable to choose which reply from the crystal ball
int reply;

signed short minutes, secondes;
char timeline[16];


void setup() {
  // set up the number of columns and rows on the LCD
  lcd.begin(16, 2);

  // set up the switch pin as an input
  pinMode(switchPin, INPUT);

  // Print a message to the LCD.
  lcd.print("Ask the");
  // set the cursor to column 0, line 1
  // line 1 is the second row, since counting begins with 0
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("Pasta Timer!");
}

void loop() {

  switchState = digitalRead(switchPin);

  // compare the switchState to its previous state
    // if the state has changed from HIGH to LOW you know that the ball has been
    // tilted from one direction to the other
  if (switchState == HIGH) {
    // randomly chose a reply
    reply = random(0);
    // clean up the screen before printing a new reply
    lcd.clear();
    // set the cursor to column 0, line 0
    lcd.setCursor(0, 0);
    // print some text
    lcd.print("firmness options:");
    // move the cursor to the second line
    lcd.setCursor(0, 1);


    // If statement would be clearn for this example
    
    // choose a saying to print based on the value in reply
    switch (reply) {

      case 0:
        lcd.setCursor(0, 0);
        lcd.print("Molto dente");

        long hour = 00, minute = 10, second = 00;
        long countdown_time = (hour*3600) + (minute * 60) + second;
        long countdowntime_seconds = countdown_time - (millis() / 1000);

        if (countdowntime_seconds >= 0) {
        long countdown_hour = countdowntime_seconds / 3600;
        long countdown_minute = ((countdowntime_seconds / 60)%60);
        long countdown_sec = countdowntime_seconds % 60;

        
        lcd.setCursor(0, 1);
        lcd.print("Cook time:");
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

      

      case 1:
        lcd.print("Al dente");
        break;

      case 2:
        lcd.print("Stracotto");
        break;

    }
  }
  
  // save the current switch state as the last state
  prevSwitchState = switchState;
}
