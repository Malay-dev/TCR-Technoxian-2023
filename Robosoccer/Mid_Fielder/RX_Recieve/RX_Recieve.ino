#include <SPI.h>
#include "RF24.h"

// Motor A connections
int enA = 9;
int in1 = 5;
int in2 = 4;

// Motor B connections
int enB = 10;
int in3 = 3;
int in4 = 2;  

RF24 myRadio(7, 8);
byte addresses[][6] = {"2"};

struct package
{
  int x = 0;
  int y = 0;
  int left = 0;
  int right = 0;
  int front = 0;
  int back = 0;
  int MaxMode = 0;
};

typedef struct package Package;
Package data;

void setup()
{
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  Serial.begin(9600);
  delay(1000);

  myRadio.begin();
  myRadio.setChannel(115);
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate(RF24_250KBPS);

  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}

void loop()
{
  if (myRadio.available())
  {

    myRadio.read(&data, sizeof(data));

    int x = data.x;
    int y = data.y;
    int front = data.front;
    int back = data.back;
    int right = data.right;
    int left = data.left;
    int MaxMode = data.MaxMode;
    Serial.print("\n");
    Serial.println(x);
    Serial.println(y);
    Serial.println(front);
    Serial.println(back);
    Serial.println(right);
    Serial.println(left);
    Serial.println(MaxMode);
    if (y > 10)
    {
      int mp_x = abs(y);
      Serial.println("FORWARD");
      if (MaxMode)
      {
        moveForward(255, 255);
      }
      else
      {
        moveForward(mp_x, mp_x);
      }
    }
    else if (y < -10)
    {
      int mp_x = abs(y);
      Serial.println("BACKWARD");
      if (MaxMode)
      {
        moveBackward(255, 255);
      }
      else
      {
        moveBackward(mp_x, mp_x);
      }
    }
    else if (x > 10)
    {
      int mp_y = abs(x);
      Serial.println("RIGHT");
      if (MaxMode)
      {
        moveRight(255, 255);
      }
      else
      {
        moveRight(mp_y, mp_y);
      }
    }
    else if (x < -10)
    {
      int mp_y = abs(x);
      Serial.println("LEFT");
      if (MaxMode)
      {
        moveLeft(255, 255);
      }
      else
      {
        moveLeft(mp_y, mp_y);
      }
    }
    else if (left == 0)
    {
      moveLeft(255, 255);
    }
    else if (right == 0)
    {
      moveRight(255, 255);
    }
    else if (front == 0)
    {
      moveForward(255, 255);
    }
    else if (back == 0)
    {
      moveBackward(255, 255);
    }
    else
    {
      stopMotors();
    }
  }
}

void moveForward(int a, int b)
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, a); // Set motor A speed
  analogWrite(enB, b); // Set motor B speed
}

void moveBackward(int a, int b)
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, a); // Set motor A speed
  analogWrite(enB, b); // Set motor B speed
}
void moveRight(int a, int b)
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, a); // Set motor A speed
  analogWrite(enB, b); // Set motor B speed
}
void moveLeft(int a, int b)
{
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, a); // Set motor A speed
  analogWrite(enB, b); // Set motor B speed
}

void stopMotors()
{
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0); // Set motor A speed to 0 (stop)
  analogWrite(enB, 0); // Set motor B speed to 0 (stop)
}
