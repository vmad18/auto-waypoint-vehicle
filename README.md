# Auto Waypoint Vehicle
Arduino autonomous GPS waypoint vehicle. 

# About 

This arduino based autonomous vehcile can set waypoints of its current location and traverse those waypoints -autonomously.- 

Additionally, it can do a "return to home" to go to the "home" waypoint. 

The vehcile can be operated via 'gesture control' or more specifically put, accelerometer orientation to control the way in which the vehcile will move (forward, left, right, nothing). 

Of course, you can always change the controller, prehaps something that uses potentiometers to emulate the same effect. 

# Components
- Arduino Nano (UNO would work as well) 
- L298N motor driver (A cheap H-Bridge type motor controller) 
- ADXL345 Accelerometer (Used for controller)
- RF24 (2) (Used for wireless communication. SPI communication protocol) 
- GPS Module (I suggest the GT-U7) 
- QMC5883L Magnetometer (Used for getting the orientation of the vehicle. It used an I2C communication protocol) 
- Three (3) Push Switch Buttons
- 12V Power Supply

# Theory 

The inclusion of the compass helps with the orientation of the vehcile and is "North" (0 degrees) referenced. 


The Haversine Formula, a mathematical formula used for spherical geometery and navigation, can find the angle or pitch relative to two coordinates (lattiudes and longitudes) that is "North" referenced. 

So knowing the orientation of the vehcile and the desired pitch needed, one can turn the vehcile and get to the desired pitch. 

Additionally, the formula can be used to get the distance between two coordinates. 

# Build 

When building, note, make sure to keep the magnetometer (compass) elevated in such a way that it is away from the motors as there could be magnetic interference that could cause inaccurate data. 

The GPS module may take time to connect with the satellites and also needs to have a clear view of the sky. 

Motors:
- Motor 1 & Motor 2 Hot Wires to OUT1 
- Motor 1 & Motor 2 Ground Wires to OUT2
- Motor 3 & Motor 4 Hot Wires to OUT3 
- Motor 3 & Motor 4 Ground Wires to OUT4

L298N: 
- ENA to D3 
- ENB to D9
- IN1 to D4
- IN2 to D5
- IN3 to D6
- IN4 to D7

Magnetometer (I2C Pins):
- SCL to A5
- SDA to A4 

GPS Module:
- TX to A1
- RX to A2

RF24 (SPI Pins):
- CE to 8
- CNS to 10
- SCK to 13
- MISO to 12
- MOSI to 11
