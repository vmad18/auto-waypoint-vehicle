
int getHeading() {
    while (!(compass.ready()));
    heading = (compass.readHeading());
    return compass.readHeading();
}

void updateLoc() {
    smartd(0);
    curr.setLoc(gps.location.lat(), gps.location.lng());
}

void addWayPoint() {
    updateLoc();
    lv[wp] = curr;
    lv[wp].setV();
    wp++;
    smartd(1000);
}

double getDistance(LocVec lv) {
    updateLoc();
    return gps.distanceBetween(curr.getLat(), curr.getLng(), lv.getLat(), lv.getLng());
}

/**
 * @param lv
 * @return
 * The azimuth is the heading between North and a gps location.
 **/
int getAzimuth(LocVec lv) {
    getHeading();
    double dLong = (lv.getLng() - gps.location.lng()) * toRad;
    double y = sin(dLong) * cos(lv.getLat() * toRad);
    double x = cos(gps.location.lat() * toRad) * sin(lv.getLat() * toRad) -
               sin(lv.getLat() * toRad) * cos(lv.getLat() * toRad) * cos(dLong);
    int delta = atan2(y, x);
    delta *= toDegree;
    delta += 360;
    delta %= 360;
    return delta;
}
