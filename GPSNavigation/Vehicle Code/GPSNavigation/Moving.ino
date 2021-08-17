
void GoWayPoint(LocVec loc) {
    setPitch(getAzimuth(loc));
    moveTo(loc);
}

void setPitch(int goal) {
    while (abs(goal - getHeading()) > 12) {
        turn();
    }
    smartd(1000);
    stop();
}

void moveTo(LocVec lv) {
    while (getDistance(lv) <= 5) {
        moveForward();
    }
    smartd(1000);
    stop();
}

void moveForward() {
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, HIGH);
    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, HIGH);
    analogWrite(ENA, 150);
    analogWrite(ENB, 150);
}

void turn() {
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, HIGH);
    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, HIGH);
    analogWrite(ENA, 150);
    analogWrite(ENB, 30);
    Serial.println(angle);
}

void stop() {
    digitalWrite(MotorA1, LOW);
    digitalWrite(MotorA2, LOW);
    digitalWrite(MotorB1, LOW);
    digitalWrite(MotorB2, LOW);
    analogWrite(ENA, 0);
    analogWrite(ENB, 0);
}


/** loc.subtract(curr)*toDegree*-1 **/
