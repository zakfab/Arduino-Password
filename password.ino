#include <Keypad.h>
#include <LiquidCrystal_I2C.h>

const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows

int cursorColumn = 0;

const String password = "12052012"; // the password
String input_password;

void setup(){
  lcd.init(); // initialize the lcd
  lcd.backlight();
  lcd.print("Enter password:");
  lcd.setCursor(0, 1);
}

void loop(){
  char key = keypad.getKey(); // defining 'key' as the key pressed on the keypad

  if (key){
    lcd.print(key); //show the key pressed on the screen

    if(key == '*') { // * is used to clear the password you have input
      lcd.clear();  // clear screen
      input_password = ""; // clear input password
    } else if(key == '#') { // press # after typing password
      if(password == input_password) {
        lcd.clear();  //clear screen
        lcd.print("Correct");
        lcd.setCursor(0, 1);         // move cursor to start of bottom row
        lcd.print("Welcome!");
        lcd.setCursor(0, 0);  // move cursor back to start of top row
        
      } else {
        lcd.clear(); // clear screen
        lcd.print("Incorrect");
        lcd.setCursor(0, 1);         // move cursor to start of bottom row
        lcd.print("Try again");
        lcd.setCursor(0, 0);  // move cursor to start of top row
      }

      input_password = ""; // clear input password
    } else {
      input_password += key; // append new character to input password string
    }
  }
}
