#include<SPI.h>
#include<nRF24L01.h>
#include<RF24.h>


//SPI Pins
#define CE 8
#define CSN 10 

RF24 radio(CE,CSN);

const int x_out = A0;
const int y_out = A1;
const byte address[6] = "00001";

struct Data{
  int xAxis;
  int yAxis;
  bool setWayPoint=false;
  bool returnHome=false;
  bool goToWayPoints=false;
};

Data controld;

int prev1=0;
int prev2=0;
int prev3=0;

void setup() {
  Serial.begin(9600);
  Serial.println("STARTING");
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening();
  pinMode(2,INPUT); //Set WayPoint Pin 
  pinMode(3,INPUT); //Return Home Pin
  pinMode(4,INPUT); //Traverse WayPoints Pin
}

void loop() {
  digitalWrite(2,HIGH);
  digitalWrite(3,HIGH);
  digitalWrite(4,HIGH);
  int b1=digitalRead(4);
  int b2=digitalRead (2);
  int b3=digitalRead(3); 
  controld.xAxis = analogRead(x_out);
  controld.yAxis = analogRead(y_out);
   
  controld.setWayPoint = b2==1 && prev2==0;
  controld.returnHome = b1==1 && prev1==0;
  controld.goToWayPoints = b3==1 && prev3==0;

  prev1 = b1;
  prev2 = b2;
  prev3 =  b3;
  radio.write(&controld, sizeof(Data));
}
