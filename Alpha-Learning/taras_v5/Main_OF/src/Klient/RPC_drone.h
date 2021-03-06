#pragma once

#ifndef RPC_Drone_H
#define RPC_Drone_H
class rpc_drone {
public:
	// setup functions 
	void rpc_innit();
	void rpc_exit();

	// elipse functions  
	int askHoops();
	int askHoopX(int n); // X position on camera
	int askHoopY(int n); // Y position on camera
	int askHoopH(int n); // Vertical Radius
	int askHoopW(int n); // Horizontal Radius


	// CV - QR
	int askQR();
	int askQRX(int n);
	int askQRY(int n);
	int askQRsize(int n);


	// Drone Sensors
	int askYaw();
	int askHeight();
	int askPitch();
	int askRoll();

	// drone control 
	int inctruct(int x, int y, int z, int alfa);
	int takeOff(void);
	int land(void);
};
#endif