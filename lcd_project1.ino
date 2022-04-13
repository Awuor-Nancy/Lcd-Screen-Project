//Include the LCD Library.
#include <Wire.h> 

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int buttonPin1 = 2;     // Charachter change button
const int buttonPin2 = 3;     // Move button
const int buttonPin3 = 4;     // Reset screen button
const int ledPin1 =  13;      // Charachter change LED pin
const int ledPin2 =  12;      // Move LED pin
const int ledPin3 =  11;      // Reset LED pin
const char chars[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','O','P','Q','R','S','U','V','W','X','Y','Z','.',',','1','2','3','4','5','6','7','8','9','0','-','*','@'};//add any additional characters

int charindex = 0;
int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;
int charsSize = 0;
int cx = 0;
int cy = 0;



void setup() {
	//init LCD
  lcd.begin();
  lcd.clear();
	lcd.setCursor(0, 0);
  lcd.blink();  
	//Charachters array size
  charsSize = sizeof(chars);
  //LED init
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  pinMode(buttonPin3, INPUT);
  
}

void loop() {
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  //
  if (buttonState1 == HIGH) {
    if(charindex == charsSize){
      charindex = 0;
    }
    // change char and turn led on:
    digitalWrite(ledPin1, HIGH);
    lcd.print(chars[charindex]);
    lcd.setCursor(cx, cy);
    charindex++;
  } else {
    digitalWrite(ledPin1, LOW);
  }
  //Move to next pixel
  if (buttonState2 == HIGH) {
    digitalWrite(ledPin2, HIGH);
    charindex = 0;
    cx++;
    if(cx == 16){
      cx = 0;
      cy++;
    }
    if(cy == 2){
      cy = 0;
    }
    lcd.setCursor(cx, cy);
  }else {
    digitalWrite(ledPin2, LOW);
  }
  //reset
  if (buttonState3 == HIGH) {
    digitalWrite(ledPin3, HIGH);
    charindex = 0;
    cx = 0;
    cy = 0;
    lcd.setCursor(cx, cy);
    lcd.clear();
  }else {
    digitalWrite(ledPin3, LOW);
  } 
  delay(170);
}