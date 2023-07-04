#include <SPI.h>  
#include "RF24.h" 

// Motor A connections
int enA = 3;
int in1 = 2;
int in2 = 4;


// Motor B connections
int enB = 5;
int in3 = 9;
int in4 = 6;



RF24 myRadio (7, 8); 
byte addresses[][6] = {"1"};

struct package {
  int x = 0;
  int y = 0;
}; 

typedef struct package Package;
Package data;

void setup() {
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
  myRadio.setDataRate( RF24_250KBPS );
  
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop()  {
  if ( myRadio.available()) {
   
      myRadio.read( &data, sizeof(data) );
    
    
    int x = data.x;
    int y = data.y;
    Serial.print("\n");
    Serial.println(x);
    Serial.println(y);
    if(x > 10){
      int mp_x = abs(data.x);
      Serial.println("FORWARD");
      moveForward(mp_x, mp_x);
    }
     else if(x < -10){
      int mp_x = abs(data.x);
      Serial.println("BACKWARD");
      moveBackward(mp_x, mp_x);
    } 
     else if(y > 10){
      int mp_y = abs(data.y);
      Serial.println("RIGHT");
      moveRight(mp_y, mp_y);
    }
     else if(y < -10){
      int mp_y = abs(data.y);
      Serial.println("LEFT");
      moveLeft(mp_y, mp_y);
    }
    else{
      stopMotors();
    }
    
  }
}

void moveForward(int a, int b) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, a); // Set motor A speed
  analogWrite(enB, b); // Set motor B speed
}

void moveBackward(int a, int b) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, a); // Set motor A speed
  analogWrite(enB, b); // Set motor B speed
}
void moveRight(int a, int b) {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enA, a); // Set motor A speed
  analogWrite(enB, b); // Set motor B speed
}
void moveLeft(int a, int b) {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, a); // Set motor A speed
  analogWrite(enB, b); // Set motor B speed
}

void stopMotors() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  analogWrite(enA, 0); // Set motor A speed to 0 (stop)
  analogWrite(enB, 0); // Set motor B speed to 0 (stop)
}
