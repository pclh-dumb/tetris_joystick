#include <Keyboard.h>

#define joyX A0
#define joyY A1
#define button 3
void setup() {
  Serial.begin(9600);
  pinMode(button, INPUT);
}
bool last_y, last_x, last_button, last_space;
int delay_y = 50, delay_x = 50, delay_button = 100;
void loop() {
  int xValue = analogRead(A0);
  int yValue = analogRead(A1);
 
  Serial.print(xValue);
  Serial.print("\t");
  Serial.print(yValue);
  Serial.print("\t");
  Serial.println(digitalRead(button));
  
  if (yValue > 900 && last_y) {
    Keyboard.press(0xD7); // right
    Serial.println("right");
    last_y = 0;
    delay(delay_y);
  }
  else if (yValue < 100 && last_y) {
    Keyboard.press(0xD8); // left
    Serial.println("left");
    last_y = 0;
  }
  else if (yValue >= 460 && yValue <= 560) {
    last_y = 1; 
    Keyboard.release(0xD8);
    Keyboard.release(0xD7);
  }
  
  if (xValue > 900 && last_x) {
    Keyboard.write(0xDA); // up(rotate clockwise)
    Serial.println("up");
    last_x = 0;
    delay(delay_x);
  }
  else if (xValue < 100 && last_x) {
    Keyboard.press(0xD9); // down
    Serial.println("down");
    last_x = 0;
  }
  else if (xValue >= 460 && xValue <= 560) {
    last_x = 1; 
    Keyboard.release(0xD9);
    Keyboard.release(0xDA);
  }

  if (digitalRead(button) == HIGH && last_button) {
    Keyboard.write(0x81); // shift(swap hold piece)
    Serial.println("shift");
    last_button = 0;
    delay(delay_button);
  }
  else {
    last_button = 1;
  }
}
