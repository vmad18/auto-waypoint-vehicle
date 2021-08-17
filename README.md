# Auto Waypoint Vehicle
Arduino autonomous GPS waypoint vehicle. 

# About 

This arduino based auto vehcile can set waypoints of its current location and traverse those waypoints. 

Additionally, it can do a "return to home" to go to the "home" waypoint. 

The vehcile can be operated via 'gesture control' or more specifically put, accelerometer orientation to control the way in which the vehcile will move (forward, left, right, nothing). 

Of course, you can always change the controller, prehaps something that uses potentiometers to emulate the same effect. 

# Components
- Arduino Nano (UNO would work as well) 
- L298N motor driver (A cheap H-Bridge type motor controller) 
- ADXL345 Accelerometer (Used for controller)
- RF24 (2) (Used for wireless communication) 
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

