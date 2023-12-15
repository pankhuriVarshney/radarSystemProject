
#include <Servo.h>
#include <SPI.h>
#include <TFT.h>

const int trigPin = 6;
const int echoPin = 5;
long duration;
int distance, prevDistance=0;
Servo myServo; 

#define CS   9
#define DC   10
#define RESET  8

TFT screen = TFT(CS, DC, RESET);
int width=screen.width();
int height=screen.height();

void setup() {
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  Serial.begin(9600);
  myServo.attach(2); 

  screen.begin();
  screen.background(0,0,0);
  fix();
}

void loop() {
  int y=0;
  for(int i=0;i<=180;i++){ 
  myServo.write(i);
  delay(10);
  distance = calculateDistance();
  if(distance<40)
    screen.stroke(0,68,255);
  else
    screen.stroke(0,255,68);
  screen.noFill();
  screen.line(screen.width()/2,0,-200*cos(radians(i)),200*sin(radians(i)));
  
  if(prevDistance<40)
  screen.stroke(0,0,100);
  else
  screen.stroke(0,100,0);

  screen.line(screen.width()/2,0,-200*cos(radians(y)),200*sin(radians(y)));
  
  screen.stroke(0,255,68);
  screen.noFill();
  screen.circle(screen.width()/2,0,screen.width()/2-0.5);
  y=i;
  prevDistance=distance;

  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }

  fix();
  y=0;
  prevDistance=0;

  for(int i=180;i>0;i--){  
   myServo.write(i);
  delay(10);
  distance = calculateDistance();
  if(distance<40)
    screen.stroke(0,68,255);
  else
    screen.stroke(0,255,68);
  screen.noFill();
  screen.line(screen.width()/2,0,-200*cos(radians(i)),200*sin(radians(i)));
  
  if(prevDistance<40)
  screen.stroke(0,0,100);
  else
  screen.stroke(0,100,0);

  screen.line(screen.width()/2,0,-200*cos(radians(y)),200*sin(radians(y)));
  
  screen.stroke(0,255,68);
  screen.noFill();
  screen.circle(screen.width()/2,0,screen.width()/2-0.5);
  y=i;
  prevDistance=distance;

  Serial.print(i);
  Serial.print(",");
  Serial.print(distance);
  Serial.print(".");
  }
  fix();
}

int calculateDistance(){ 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(1);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(5);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH); 
  distance= duration*0.034/2;
  return distance;
}

void fix(){
  screen.fillRect(0, 0, screen.width(), screen.height(), (0,0,0));
  screen.stroke(0,255,68);
  screen.noFill();
  screen.circle(screen.width()/2,0,screen.width()/2-0.5);
  }