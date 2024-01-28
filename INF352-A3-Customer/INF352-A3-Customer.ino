#include <Wire.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

const int scrollButtonPin = 2;
const int addButtonPin = 3;
const int confirmButtonPin = 4;

int selectedItemIndex = 0;
const String menuItems[] = {"Gamjatang", "Filipino Spaghetti", "Butter Chicken", "Lamb Skewers", "Stinky Tofu", "Jerk Chicken", "Milk Tea", "Oat Matcha", "Coffee", "Redbull"};
const int menuPrices[] = {15, 12, 17, 9, 7, 20, 3, 4, 2, 5};
String order = "";

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

void loop() {
  displayMenu();

  // wait for user input
  int buttonState;
  while (true) {
    buttonState = digitalRead(scrollButtonPin);
    if (buttonState == HIGH) {
      selectedItemIndex = (selectedItemIndex + 1) % 10; // this cycles through the menu items
      displayMenu();
      delay(500);
    }

    buttonState = digitalRead(addButtonPin);
    if (buttonState == HIGH) {
      order += menuItems[selectedItemIndex] + " - $" + String(menuPrices[selectedItemIndex]) + ", "; //appends to the order string so customer can add items from menu with the price
      lcd.clear();
      lcd.print("Order: $");
      lcd.setCursor(0, 1);
      lcd.print(order);
      delay(500);
    }

    buttonState = digitalRead(confirmButtonPin);
    if (buttonState == HIGH) {
      sendOrder();
      delay(3000);
      break;
    }
  }
}

void displayMenu() {
  lcd.clear();
  lcd.print(menuItems[selectedItemIndex]);
  lcd.setCursor(0, 1);
  lcd.print("Add: ");
  lcd.print(menuItems[(selectedItemIndex + 1) % 10]);
  lcd.print("  Confirm: ");
  lcd.print(menuItems[(selectedItemIndex + 2) % 10]);
  delay(2000);
}

void sendOrder() {
  Wire.beginTransmission(address); // this will be changed as we find the "address"
  Wire.write(order.c_str()); // this will send the order as a string to the restaurant
  Wire.endTransmission();

  lcd.clear();
  lcd.print("Order has been sent!");

  order = "";
  selectedItemIndex = 0;
}

}