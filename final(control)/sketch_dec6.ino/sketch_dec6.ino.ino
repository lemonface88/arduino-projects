lemonface
lemonface#0452
8⃣️2⃣️滴
Coding and not showering buddies

lemonface
 changed the channel name: 
Coding and not showering buddies
 — Yesterday at 4:26 PM
lemonface — Yesterday at 4:26 PM
yo yo
fanger_27 — Yesterday at 4:28 PM
yoooo
did u take a look at the code i sent
lemonface — Yesterday at 4:28 PM
looking at it now
david can u send ur file
lemonface — Yesterday at 4:48 PM
r u guys able ot meet tmr
and bang it out
cuz not really effective for us to be coding and not able to test it
fanger_27 — Yesterday at 4:54 PM
yeah my plan was to grind this shit out on campus with the computer tmr
dimmy — Yesterday at 5:54 PM
updated
// dependencies
#include <LCD.h>
#include <Wire.h>


#define MAX_STRING_LENGTH 15
Expand
Controller_Example.ino
3 KB
fanger_27 — Today at 3:42 PM
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int scrollButtonPin = 10;
Expand
sketch_dec6.ino.ino
4 KB
fanger_27 — Today at 3:53 PM
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

String receivedOrder = "";
int orderScrollIndex = 0;

const int scrollButtonPin = 11;
const int orderCompleteButtonPin = 12;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("  Casa Arduino");
  lcd.setCursor(0, 1);
  lcd.print(" Restaurant");

  pinMode(scrollButtonPin, INPUT);
  pinMode(orderCompleteButtonPin, INPUT);

  Wire.begin(9); // Set the I2C address to 9
  Wire.onReceive(receiveEvent);
}

void loop() {
  handleScrolling();
  handleOrderComplete();
}

void receiveEvent() {
  receivedOrder = "";

  while (Wire.available()) {
    char c = Wire.read();
    receivedOrder += c;
  }

  orderScrollIndex = 0; // Reset scroll index when a new order is received
  displayReceivedOrder();
}

void handleScrolling() {
  if (digitalRead(scrollButtonPin) == HIGH) {
    orderScrollIndex++;
    displayReceivedOrder();
    delay(500); // Adjust delay to control scrolling speed
  }
}

void handleOrderComplete() {
  if (digitalRead(orderCompleteButtonPin) == HIGH) {
    lcd.clear();
    lcd.print("Order Completed!");
    delay(2000); // Display "Order Completed!" for 2 seconds
    lcd.clear();
    receivedOrder = ""; // Clear the received order after completion
  }
}

void displayReceivedOrder() {
  lcd.clear();
  lcd.print("Received Order:");
  lcd.setCursor(0, 1);

  // Display the order with scrolling
  for (int i = orderScrollIndex; i < receivedOrder.length() && i < orderScrollIndex + 16; i++) {
    lcd.print(receivedOrder[i]);
  }

  if (orderScrollIndex + 16 < receivedOrder.length()) {
    orderScrollIndex++;
  } else {
    orderScrollIndex = 0; // Reset scroll index when the end of the order is reached
  }
}

Collapse
INF352-A3-Restaurant.ino
2 KB
dimmy — Today at 3:59 PM
https://prod.liveshare.vsengsaas.visualstudio.com/join?1F5CF3092F7AA2EC05F3A9D692B9D257049C
Visual Studio Code for the Web
Build with Visual Studio Code, anywhere, anytime, entirely in your browser.
fanger_27 — Today at 4:31 PM
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

const int scrollButtonPin = 10;
Expand
sketch_dec6.ino.ino
4 KB
dimmy — Today at 4:48 PM
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int address = 9;
Expand
sketch_dec6.ino.ino
4 KB
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

String receivedOrder = "";
Expand
peripheral.ino
2 KB
﻿
#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

int address = 9;

const int scrollButtonPin = 10;
const int addButtonPin = 11;
const int confirmButtonPin = 12;
const int buzzerPin = 8;

int selectedItemIndex = 0;
const String menuItems[] = {"Gamjatang", "Spaghetti", "Butter Chicken", "Lamb Skewers", "Stinky Tofu", "Jerk Chicken", "Milk Tea", "Oat Matcha", "Coffee", "Redbull"};
const int menuPrices[] = {15, 12, 17, 9, 7, 20, 3, 4, 2, 5};
const String order = "";

int tracker = 0;
int orderTracker = 0;

int a = 0;
char end = e;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("  Welcome to");
  lcd.setCursor(0, 1);
  lcd.print("  Casa Arduino");

  pinMode(scrollButtonPin, INPUT);
  pinMode(addButtonPin, INPUT);
  pinMode(confirmButtonPin, INPUT);

  Wire.begin(); 
}

bool orderSubmitted = false;

void loop() {
  if (!orderSubmitted)  {
    if(digitalRead(scrollButtonPin) == HIGH){
      orderList();
    }

    if(digitalRead(addButtonPin)==HIGH){
      sendOrder();
    }

    if(digitalRead(confirmButtonPin)==HIGH){
      confirmOrder();
      lcd.clear();
      lcd.print(" Order has been sent");
      lcd.setCursor(4, 1);
      lcd.print(" SENT!");
    }
  } else {
    Wire.requestFrom(address, 1);
    while (Wire.available()) {
      bool x = Wire.read();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print('order done');
      tone(buzzerPin, 500);
      delay(250);
      noTone(buzzerPin);
      orderSubmitted = false;
    }
  }
  delay(500);
}

void confirmOrder(){
  Wire.beginTransmission(address); // this will be changed as we find the "address"
  Wire.write(end); // this will send the order as a string to the restaurant
  Wire.endTransmission();

}

void sendOrder() {
  Wire.beginTransmission(address); // this will be changed as we find the "address"
  Wire.write(tracker-1); // this will send the order as a string to the restaurant
  Wire.endTransmission();

  lcd.clear();
  lcd.print("Order has been sent!");

  order = "";
  selectedItemIndex = 0;
}


void orderList(){

    tracker += 1;
    lcd.clear();

    //tracker increase cuasing the options to change
    switch(tracker){
    
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Gamjatang");
      lcd.setCursor(0, 1);
      

      lcd.print("15 Dollars");
      

      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Spaghetti");
      lcd.setCursor(0, 1);
      lcd.print("12 Dollars");
  
      break;

    case 3:
      lcd.setCursor(0, 0);
      lcd.print("Butter Chicken");
      lcd.setCursor(0, 1);
      lcd.print("17 Dollars");

      break;

    case 4:
      lcd.setCursor(0, 0);
      lcd.print("Lamb Skewers");
      lcd.setCursor(0, 1);
      lcd.print("9 Dollars");

      break;
      


    case 5:
      lcd.setCursor(0, 0);
      lcd.print("Stinky Tofu");
      lcd.setCursor(0, 1);
      lcd.print("7 Dollars");

      break;


    case 6:
      lcd.setCursor(0, 0);
      lcd.print("Jerk Chicken");
      lcd.setCursor(0, 1);
      lcd.print("20 Dollars");

      break;


    case 7:
      lcd.setCursor(0, 0);
      lcd.print("Milk Tea");
      lcd.setCursor(0, 1);
      lcd.print("3 Dollars");

      break;


    case 8:
      lcd.setCursor(0, 0);
      lcd.print("Oat Matcha");
      lcd.setCursor(0, 1);
      lcd.print("4 Dollars");

      break;


    case 9:
      lcd.setCursor(0, 0);
      lcd.print("Coffee");
      lcd.setCursor(0, 1);
      lcd.print("2 Dollars");

      break;


    case 10:
      lcd.setCursor(0, 0);
      lcd.print("Redbull");
      lcd.setCursor(0, 1);
      lcd.print("5 Dollars");

      break;

    
  }
  if(tracker > 10){
    tracker -= 10;
  }
  //return an item from the list
}
