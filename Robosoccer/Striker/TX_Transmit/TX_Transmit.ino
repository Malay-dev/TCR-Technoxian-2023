#include <SPI.h>
#include "RF24.h"

#define joyX A0
#define joyY A1
#define LEFT_BTN 5
#define RIGHT_BTN 3
#define FRONT_BTN 2
#define BACK_BTN 4
#define MAX_BTN 6

int xValue, yValue, lft, rght, frnt, bck, mx_m, flag = 0;

RF24 myRadio(9, 10);
byte addresses[][6] = {"2"};

struct JoystickData
{
  int x = 0;
  int y = 0;
  int left = 0;
  int right = 0;
  int front = 0;
  int back = 0;
  int MaxMode = 0;
};

typedef struct JoystickData JoystickData;
JoystickData joystickData;

void setup()
{
  Serial.begin(9600);
  delay(1000);

  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);
  myRadio.openWritingPipe(addresses[0]);
}

void loop()
{
  // Read joystick values
  xValue = analogRead(joyX);
  yValue = analogRead(joyY);
  lft = digitalRead(LEFT_BTN);
  rght = digitalRead(RIGHT_BTN);
  frnt = digitalRead(FRONT_BTN);
  bck = digitalRead(BACK_BTN);
  mx_m = digitalRead(MAX_BTN);

  joystickData.x = map(xValue, 0, 685, -255, 255);
  joystickData.y = map(yValue, 0, 685, -255, 255);

  if (mx_m == 0)
  {
    if (flag == 0)
    {
      flag = 1;
    }
    else
    {
      flag = 0;
    }
  }
  joystickData.left = lft;
  joystickData.right = rght;
  joystickData.front = frnt;
  joystickData.back = bck;
  if (flag == 1)
  {
    joystickData.MaxMode = 1;
  }
  else
  {
    joystickData.MaxMode = 0;
  }

  // Send joystick data
  myRadio.write(&joystickData, sizeof(joystickData));

//  Serial.println(xValue);
//  Serial.println(yValue);
  Serial.println(joystickData.x);
  Serial.println(joystickData.y);
  Serial.println(joystickData.left);
  Serial.println(joystickData.right);
  Serial.println(joystickData.front);
  Serial.println(joystickData.back);
  Serial.println(joystickData.MaxMode);
  delay(100);
}
