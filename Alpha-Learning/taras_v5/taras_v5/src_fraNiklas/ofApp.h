#pragma once

#include "ofMain.h"
#include "DroneRoom.h"
#include "Drone.h"
#include "DroneControl.h"
#include "DroneAI.h"
#include "UserInterface.h"
#include "ARDrone.h"
#include "CV.h"
#include "Klient\RPC_drone.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	private:

		int keys[256];

		ofEasyCam camera;
		ofLight light;

		ofNode originNode;

		rpc_drone rpc;
		// skal slettes 
		bool fly;
		ARDrone ardrone = ARDrone(&rpc);
		//CV cv = CV(&rpc);

		Drone drone;
		DroneRoom droneroom;
		//ARDrone ardrone;
		CV cv;
		DroneControl dronecontrol = DroneControl(&drone, &ardrone, &cv);
		DroneAI droneai = DroneAI(&drone, &droneroom, &dronecontrol);
		UserInterface userinterface = UserInterface(&dronecontrol, &droneai);



};