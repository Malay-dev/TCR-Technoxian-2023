#include <SPI.h>  
#include "RF24.h" 
#define in3 A5
// Motor A connections
int in1 = 5;
int in2 = 6;


// Motor B connections
//int in3 = 0;
int in4 = 2;

// Motor C connections
int in5 = 3;
int in6 = 4;


// Motor D connections
int in7 = 9;
int in8 = 10;

RF24 myRadio (7, 8); 
byte addresses[][6] = {"1"};

struct package {
  int x = 0;
  int y = 0;
  int left = 1;
  int right = 1;
}; 


typedef struct package Package;
Package data;

void setup() {
  // put your setup code here, to run once:
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(in5, OUTPUT);
  pinMode(in6, OUTPUT);
  pinMode(in7, OUTPUT);
  pinMode(in8, OUTPUT);
  Serial.begin(9600);
  delay(1000);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS );
  
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}

void loop() {
  // put your main code here, to run repeatedly:
    if ( myRadio.available()) {
   
      myRadio.read( &data, sizeof(data) );
    
    
    int x = data.x;
    int y = data.y;
    int left = data.left;
    int right = data.right;
    Serial.print("\n");
    Serial.println(x);
    Serial.println(y);
    Serial.println(left);
    Serial.println(right);
    if(x < 0){
      int mp_x = abs(data.x);
      Serial.println("FORWARD");
      moveForward(255, 255);
    }
     else if(x > 20){
      int mp_x = abs(data.x);
      Serial.println("BACKWARD");
      moveBackward(255, 255);
    } 
     else if(y > 20){
      int mp_y = abs(data.y);
      Serial.println("RIGHT");
      moveRight(255, 255);
    }
     else if(y < 0){
      int mp_y = abs(data.y);
      Serial.println("LEFT");
      moveLeft(255, 255);
    }
    
     else if(right == 0){
      Serial.println("ORIENT_RIGHT");
      orientRight();
    }
     else if(left == 0){
      Serial.println("ORIENT_LEFT");
      orientLeft();
    }
    
    else{
      stopMotors();
    }
    
  }

}


void moveForward(int a, int b) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, 255);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}

void moveBackward(int a, int b) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, 0);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}
void moveRight(int a, int b) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, 0);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}
void moveLeft(int a, int b) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, 255);
  digitalWrite(in4, LOW);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}

void orientRight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, 255);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, HIGH);
  digitalWrite(in7, LOW);
  digitalWrite(in8, HIGH);
}

void orientLeft() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, 0);
  digitalWrite(in4, HIGH);
  digitalWrite(in5, HIGH);
  digitalWrite(in6, LOW);
  digitalWrite(in7, HIGH);
  digitalWrite(in8, LOW);
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(in3, 0);
  digitalWrite(in4, LOW);
  digitalWrite(in5, LOW);
  digitalWrite(in6, LOW);
  digitalWrite(in7, LOW);
  digitalWrite(in8, LOW);
}