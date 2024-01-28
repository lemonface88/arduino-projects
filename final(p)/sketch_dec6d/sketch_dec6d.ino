#include <LiquidCrystal.h>
#include <Wire.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

// This is the address of the peripheral device
// It could be any number as long as it matches the address declared in the controller code
const int address = 9;



void setup() {
  // put your setup code here, to run once:
  // Assigns address to this peripheral device
  Wire.begin(address);
  
  // Specifies which function to run whenever controller sends data to the peripheral
  Wire.onReceive(receiveEvent);
  
  // Specifies which function to run whenever controller requests data from the peripheral
  Wire.onRequest(requestEvent); 
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
