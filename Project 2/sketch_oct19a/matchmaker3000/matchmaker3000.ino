#include <LiquidCrystal.h>/* defining the library for the LCD*/

LiquidCrystal lcd(6, 7, 8, 9, 10, 11); //rs, en, d4, d5, d6, d7/
//need to make a list of questionslong


float matchCount = 0; // this is the count of matches

int tracker = 0;

double finalrationcount; // this is the % of the matches


int buttonstate1Red;
int buttonState1Green;
int buttonState2Red;
int buttonState2Green;

void setup(){

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Ice Breaker ");
  lcd.setCursor(0, 1);
  // print to the second line

  /*
  float a = (float) 2/10;
  lcd.print(a);
  */

  lcd.print("3000!!");
}


void loop() {
  /*
  buttonStateNext = digitalRead(4); // this is the start or next button for the question


  buttonstate1Red = digitalRead(2); // this detects the user 1 red button
  buttonState1Green = digitalRead(3); // this detects the user 1 green button

  buttonState2Red = digitalRead(13); // this detects the user 2 red button
  buttonState2Green = digitalRead(12); // this detects the user 2 green button

  */

  if(digitalRead(2) == HIGH){
    buttonState1Green = 1;
  }

  if(digitalRead(3) == HIGH){
    buttonstate1Red = 1;
  }

  if(digitalRead(12) == HIGH){
    buttonState2Green = 1;
  }

  if(digitalRead(13) == HIGH){
    buttonState2Red = 1;
  }




  // if the next question button is pressed, it goes to the next questions
  if(digitalRead(4) == HIGH){
    question();
    
  }

      
  delay(300);

}


void question(){

                  // left green         left red        right green         right red
   scoreTracker(buttonState1Green, buttonstate1Red, buttonState2Green, buttonState2Red); // this tracks the matching scores from each question
                  // left green         left red        right green         right red
   resetScore(buttonState1Green, buttonstate1Red, buttonState2Green, buttonState2Red); // once the score is tracked, it is then reset for the next round


    tracker += 1;
    lcd.clear();

    //tracker increase cuasing the options to change
    switch(tracker){
    
    case 1:
      lcd.setCursor(0, 0);
      lcd.print("Green = Left");
      lcd.setCursor(0, 1);

      lcd.print("Red = Right");
      

      break;

    case 2:
      lcd.setCursor(0, 0);
      lcd.print("Cats or Dogs");
      lcd.setCursor(0, 1);

      break;

    case 3:
      lcd.setCursor(0, 0);
      lcd.print("Noodles or Rice");
      lcd.setCursor(0, 1);

      break;

    case 4:
      lcd.setCursor(0, 0);
      lcd.print("Beach or Pool");
      lcd.setCursor(0, 1);

      break;
      


    case 5:
      lcd.setCursor(0, 0);
      lcd.print("Wine or Beer");
      lcd.setCursor(0, 1);

      break;


    case 6:
      lcd.setCursor(0, 0);
      lcd.print("Summer/Winter");
      lcd.setCursor(0, 1);

      break;


    case 7:
      lcd.setCursor(0, 0);
      lcd.print("Coffee or Tea");
      lcd.setCursor(0, 1);

      break;


    case 8:
      lcd.setCursor(0, 0);
      lcd.print("Drive or Walk");
      lcd.setCursor(0, 1);

      break;


    case 9:
      lcd.setCursor(0, 0);
      lcd.print("Burger or Pizza");
      lcd.setCursor(0, 1);

      break;


    case 10:
      lcd.setCursor(0, 0);
      lcd.print("Sweet / Salty?");
      lcd.setCursor(0, 1);

      break;


    case 11:
      lcd.setCursor(0, 0);
      lcd.print("Morning or Night");
      lcd.setCursor(0, 1);

      break;


    case 12:
      lcd.setCursor(0, 0);
      lcd.print("You are: ");
      lcd.setCursor(0, 1);
      float finalrationcount = (matchCount/10) * 100;

      lcd.print(String(finalrationcount) + String("% match")); // String("1234 ") + String(number)

      break;

    case 13:
      lcd.setCursor(0, 0);
      lcd.print("Press Restart");
      lcd.setCursor(0, 1);
      lcd.print("to play again");


      break;
    
  }

  //return an item from the list
}


// when both users press the same type of button it is recorded as a match, 
int scoreTracker(int u1red, int u1green, int u2red, int u2green){
  if(u1red == 1 && u2red==1){
    matchCount ++;
  }

  if(u1green == 1 && u2green==1){
    matchCount ++;
  }

}

// this resets the button state after each question
void resetScore(int u1green, int u1red, int u2green, int u2red){
  if(u1red == 1){
    buttonstate1Red -= buttonstate1Red;
  }

  if(u1green == 1){
    buttonState1Green -=buttonState1Green ;
  }

  if(u2red == 1){
    buttonState2Red -= buttonState2Red;
  }

  if(u2green == 1){
    buttonState2Green -=buttonState2Green;
  }

}










