#include "ofMain.h"
#include "settings.h"
#include "Drone.h"

Drone::Drone() {

  box.setParent(node);
  forward.setParent(node);
  direction.setParent(node);

  forward.move(DRONE_ORIENTATION_VECTOR,0,0);
  box.set(DRONE_BOX_X, DRONE_BOX_Y, DRONE_BOX_Z);
  node.setPosition(DRONE_START_X,DRONE_START_Y, DRONE_START_Z);

  setFlightMode(TAKEOFF);
  setDroneMode(LANDED);

  for(int i = 0; i < DRONE_COUNT; i++) {
    view[i].setParent(node);
  }

  float angleZ = tan(ofDegToRad(DRONE_VIEW_Z_ANGLE/2))*DRONE_VIEW_OFFSET;
  float angleY = tan(ofDegToRad(DRONE_VIEW_Y_ANGLE/2))*DRONE_VIEW_OFFSET;

  view[0].setPosition(DRONE_VIEW_OFFSET,-angleZ,angleY);
  view[1].setPosition(DRONE_VIEW_OFFSET,angleZ,angleY);
  view[2].setPosition(DRONE_VIEW_OFFSET,angleZ,-angleY);
  view[3].setPosition(DRONE_VIEW_OFFSET,-angleZ,-angleY);

}

void Drone::draw() {

  // The Drone
  ofSetColor(255,0,255);
  box.drawWireframe();

  // Draw Forward Direction
  ofDrawArrow(node.getGlobalPosition(), forward.getGlobalPosition(), 10);

  // Draw Destination Vector
  ofDrawArrow(node.getGlobalPosition(), destination, 0);

  drawView();

}

void Drone::drawView() {

  ofSetColor(ofColor::cyan);

  for(int i = 0; i < DRONE_COUNT; i++) {

    ofDrawArrow(node.getGlobalPosition(),view[i].getGlobalPosition());

    ofDrawArrow(view[i].getGlobalPosition(),view[(i+1)%4].getGlobalPosition());

  }

}

void Drone::update() {

  // Destination Offset

  destinationOffset = destination - node.getGlobalPosition();

  direction.setGlobalPosition(destination);

  // Rotation

  angleOffset = (direction.getPosition() * ofVec3f(1,0,1)).angle(forward.getPosition());

  //printf("Angle Offset %f.\n",angleOffset);

  if(angleOffset > DRONE_ANGLE_OFFSET && flightmode != TAKEOFF && flightmode != LANDING) {

    ofVec3f angleRotationDirection = (direction.getPosition() * ofVec3f(1,0,1)).getCrossed(forward.getPosition());

    float angleRotation = DRONE_ROTATION_SPEED;

    if(angleRotation > angleOffset) angleRotation = angleOffset;

    if(angleRotationDirection.y < 0) {

      //printf("Turn Left.\n");

      node.rotate(angleRotation,0,1,0);

    }

    else {

      //printf("Turn Right.\n");

      node.rotate(-angleRotation,0,1,0);

    }

  }

  if(angleOffset > 90) return;

  if(destinationOffset.length()) {

    //printf("Moving drone.\n");

    float moveDistance = destinationOffset.length();

    //printf("Destination offset: %f.\n",moveDistance);

    if(destinationOffset.length() < speed) moveDistance = destinationOffset.length();

    else moveDistance = speed;

    node.move(moveDistance * destinationOffset.getNormalized());

  }
}

ofVec3f Drone::getPosition() {

  return node.getGlobalPosition();

}
ofVec3f Drone::setPosition(ofVec3f position) {

  ofVec3f difference = position - node.getGlobalPosition();

  node.setGlobalPosition(position);

  return difference;

}
ofVec3f Drone::getDestination() {
 return destination;
}
ofVec3f Drone::setDestination(ofVec3f _destination) {

  ofVec3f result = _destination - destination;

  direction.setGlobalPosition(_destination);

  destination = _destination;

  return result;

}
float Drone::getDestinationDistance() {

  //printf("Distance: %f.\n", destinationOffset.length());

  return destinationOffset.length();
}

void Drone::setFlightMode(FlightMode _flightmode) {
  flightmode = _flightmode;

  switch(flightmode) {
    case NOTFLYING:
      speed = 0;
      break;
    case STEADY:
    case LANDING:
      speed = DRONE_STEADY_SPEED;
      break;
    case NORMAL:
    case TAKEOFF:
      speed = DRONE_NORMAL_SPEED;
      break;
    case FAST:
      speed = DRONE_FAST_SPEED;
      break;
    case INSANE:
      speed = DRONE_INSANE_SPEED;
      break;
    case LUDICROUS:
      speed = DRONE_LUDICROUS_SPEED;
      break;
    default:
      speed = DRONE_NORMAL_SPEED;
      break;
  }
}

int Drone::getSpeed() {
  return speed;
}

FlightMode Drone::getFlightMode() {
  return flightmode;
}

void Drone::setDroneMode(DroneMode _dronemode) {
  dronemode = _dronemode;
}

DroneMode Drone::getDroneMode() {
  return dronemode;
}

void printFlightMode(FlightMode flightmode) {

  switch(flightmode) {
    case FAST:
      printf("FAST\n");
      break;
    case NORMAL:
      printf("NORMAL\n");
      break;
    case STEADY:
      printf("STEADY\n");
      break;
    case TAKEOFF:
      printf("STEADY\n");
      break;
    case LANDING:
      printf("LANDING\n");
      break;
    case NOTFLYING:
      printf("NOTFLYING\n");
      break;
    case INSANE:
      printf("INSANE\n");
      break;
    case LUDICROUS:
      printf("LUDICROUS\n");
      break;
    default:
    break;

  }

}
