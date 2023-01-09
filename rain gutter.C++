#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

Servo servomotor;

int trig = 8;
int echo = 9;

float t = 30.0;
float d = 20.0;
float a = 0;

float safe = 50.0;
 
void setup() {
   // Serial 통신을 설정합니다.
  Serial.begin(9600);      
 
  while (!Serial) {
  }

  Serial.println("Goodnight moon!");
 
  mySerial.begin(9600);
  mySerial.println("Hello, world?");                     

  //초음파
  pinMode(trig, OUTPUT);  
  pinMode(echo, INPUT);
                                           
  Serial.println("Servor Mortor");
  servomotor.attach(7);
}
 
 

void loop() { // run over and over
  if (mySerial.available()) {
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    mySerial.write(Serial.read());
  }
}

void loop() {
  float Length, distance;
  digitalWrite(trig, LOW);
  delay(10);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  Length = pulseIn(echo, HIGH);
  distance = ((float)(340 * Length) / 10000) / 2;
 
  delay(1000); 
  char car = Serial.read();  
 
    if(car == 'F'){                         // 'F'를 입력하면 전진
      Serial.println("forward");
      forward();   
      }
    else if(car == 'B'){                   // 'R'를 입력하면 우회전
      Serial.println("Back");
      back();   
      }
    else if(car == 'S'){
      Serial.println("Stop");
      STOP();
    }
    
  if(t<distance&&distance<safe&&distance!=a){
    Serial.println("Safe");
  }
    

  if(d<distance&&distance<t&&distance!=a){
      Serial.println("Warinng! Warinng!");
  }

   if(distance<d&&distance!=a){
      Serial.println("Clear Please!");
  }
 
}

void forward(){
      servomotor.write(180);
      delay(1000);
    Serial.print("speed : ");
    Serial.println("MAXL");
}

void back(){
  servomotor.write(0);
  delay(1000);
  Serial.print("speed : ");
    Serial.println("MAXR");
  
}

void STOP(){
  servomotor.write(92);
  delay(1000);
  Serial.print("speed : ");
    Serial.println("STOP");
}