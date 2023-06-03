#pragma once
#include <map>
#include <vector>
#include <iostream>
using namespace std;

class Rotor
{
private:
	int notch; //notch number for this rotor
	int numRotations; //number of times it already rotated
	bool rotate; //should current rotor rotate		NOTE: Could only be true if this rotor isn't the rightmost rotor
	bool isFirstRotor; //check if rotor is rightmost rotor
	vector<pair<int, int>> rotor;

	void moveRotor(int numRotations = 1); //rotate rotor by 1
	void setRotor(int rotorNum); //Set this->rotor to desired rotor
	void ringSetup(char ring);
public:
	Rotor(int rotorNum, bool isFirst, char startingPos, char ring);
	void firstEncrypt(int* letter); //before electricty enters deflector
	void secondEncrypt(int* letter); //after electricity enters deflector
	friend void displayRotors(Rotor &r1, Rotor &r2, Rotor &r3); //display window and rotor map
	friend void rotate( Rotor &r2,  Rotor &r1); //check if rotation is needed
};

