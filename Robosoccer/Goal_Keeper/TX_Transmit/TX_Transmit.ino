#include <SPI.h>
#include "RF24.h"
#define joyX A0
#define joyY A1
#define LEFT_BTN 4
#define RIGHT_BTN 2
int xValue, yValue, lft, rght;

RF24 myRadio(9, 10);
byte addresses[][6] = { "1" };

struct JoystickData {
  int x = 0;
  int y = 0;
  int left = 0;
  int right = 0;
};

typedef struct JoystickData JoystickData;
JoystickData joystickData;

void setup() {
  Serial.begin(9600);
  delay(1000);

  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openWritingPipe(addresses[0]);
}

void loop() {
  // Read joystick values
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  lft = digitalRead(LEFT_BTN);
  rght = digitalRead(RIGHT_BTN);
  joystickData.x = map(xValue, -385, 1024, -255, 255);
  joystickData.y = map(yValue, -385, 1024, -255, 255);
  joystickData.left = lft;
  joystickData.right = rght;

  // Send joystick data
  myRadio.write(&joystickData, sizeof(joystickData));

  Serial.print("Joystick X: ");
  Serial.println(joystickData.x);
  Serial.print("Joystick Y: ");
  Serial.println(joystickData.y);
  Serial.print("Joystick LEFT: ");
  Serial.println(joystickData.left);
  Serial.print("Joystick RIGHT: ");
  Serial.println(joystickData.right);

  delay(100);
}