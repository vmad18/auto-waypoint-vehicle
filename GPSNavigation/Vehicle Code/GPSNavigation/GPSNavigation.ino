#include <Wire.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <QMC5883L.h>
#include <LocVec.h>

#define RX 16
#define TX 15
#define ENA 3
#define ENB 9
#define MotorA1 4
#define MotorA2 5
#define MotorB1 6
#define MotorB2 7

#define toRad PI/180
#define toDegree 180/PI

const int wps = 10; 

LocVec curr(0,0);
LocVec lv[10]; 

//waypoint pos
int wp = 0;

int heading;
double angle;

struct RecieveData {
  int xAxis;
  int yAxis;
  bool setWayPoint = false;
  bool returnHome = false;
  bool goToWayPoints = false;
};

SoftwareSerial sw(RX, TX);
TinyGPSPlus gps;
QMC5883L compass;

void setup() {
  Serial.begin(9600);
  sw.begin(9600);
  Wire.begin();
  compass.init();
  startCommunication();

  Serial.println("<------>STARTING<------>");
  pinMode(ENA, OUTPUT);
  pinMode(MotorA1, OUTPUT);
  pinMode(MotorA2, OUTPUT);
  pinMode(MotorB1, OUTPUT);
  pinMode(MotorB2, OUTPUT);
  pinMode(ENB, OUTPUT);
}

void loop() {
  while (sw.available()) {
    smartd(0);
    if (isAvailable()) {
      if (gps.location.isValid()) {
        //get data from rf24
        RecieveData d = getData();
        if (d.setWayPoint) {
          //set waypoint of current loc
          if (wp == wps) {
            Serial.println("CANNOT SET ANYMORE WAYPOINTS");
            Serial.println("Changing Set Waypoints");
            wp = 1;
          } else {
            Serial.println("WAYPOINT SET");
            addWayPoint();
          }
        } else if (d.returnHome) {
          //return to home command
          if (!(lv[0].isSet())) {
            Serial.println("No Return Home Available.");
          } else {
            GoWayPoint(lv[0]);
          }
        } else if (d.goToWayPoints) {
          //traverse way points.
          for (LocVec loc : lv) {
            GoWayPoint(loc);
          }
          smartd(1000);
        } else {
          //move vehicle
          if (380 > d.yAxis && d.yAxis >= 370 && 365 >= d.xAxis && d.xAxis > 321) {
            moveForward();
          } else if (390 > d.yAxis && d.yAxis >= 380 && 365 >= d.xAxis && d.xAxis > 321) {
            digitalWrite(MotorA1, LOW);
            digitalWrite(MotorA2, HIGH);
            digitalWrite(MotorB1, LOW);
            digitalWrite(MotorB2, HIGH);
            analogWrite(ENA, 145);
            analogWrite(ENB, 145);
          } else if (400 > d.yAxis && d.yAxis >= 390 && 365 >= d.xAxis && d.xAxis > 321) {
            digitalWrite(MotorA1, LOW);
            digitalWrite(MotorA2, HIGH);
            digitalWrite(MotorB1, LOW);
            digitalWrite(MotorB2, HIGH);
            analogWrite(ENA, 180);
            analogWrite(ENB, 180);
          } else if (d.yAxis >= 400 && 365 >= d.xAxis && d.xAxis > 321) {
            digitalWrite(MotorA1, LOW);
            digitalWrite(MotorA2, HIGH);
            digitalWrite(MotorB1, LOW);
            digitalWrite(MotorB2, HIGH);
            analogWrite(ENA, 255);
            analogWrite(ENB, 255);
          } else if (d.xAxis >= 370 && 370 > d.yAxis) {
            digitalWrite(MotorA1, LOW);
            digitalWrite(MotorA2, HIGH);
            digitalWrite(MotorB1, LOW);
            digitalWrite(MotorB2, HIGH);
            analogWrite(ENA, 250);
            analogWrite(ENB, 60);
          } else if (320 > d.xAxis && 370 <= d.yAxis) {
            digitalWrite(MotorA1, LOW);
            digitalWrite(MotorA2, HIGH);
            digitalWrite(MotorB1, LOW);
            digitalWrite(MotorB2, HIGH);
            analogWrite(ENA, 60);
            analogWrite(ENB, 250);
          } else {
            stop();
          }
        }
      }
    }
  }
}

void smartd(unsigned long ms) {
  unsigned long int start = millis();
  do {
    while (sw.available()) {
      gps.encode(sw.read());
    }
  } while (millis() - start < ms);
}
