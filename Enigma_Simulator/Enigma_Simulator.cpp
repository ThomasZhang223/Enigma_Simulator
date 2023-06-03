#include <iostream>
#include <vector>
#include <map>
#include <iterator>
#include <fstream>
#include <string>
#include <ctype.h>
#include "Rotor.h"

using namespace std;
#define	FAST_IO ios_base::sync_with_stdio(false); cin.tie(0); 

//For generating the rotor maps
void generateRotorArray(string s)
{
	string t;
	for (int i = 0; i < 26; i++)
	{
		int a = s.at(i) - 64;
		string temp = '{' + to_string(i + 1) + ',' + to_string(a) + "}, ";
		t += temp;
	}
	cout << t;
}

//Friend functions
void rotate(Rotor& r2, Rotor& r1)
{
	if (r1.isFirstRotor)
	{
		if (r1.numRotations % 26 == r1.notch)
		{
			r2.rotate = true;
		}
	}
	else
	{
		if (r1.numRotations % 26 == r1.notch - 1)
		{
			r2.rotate = true;
			r1.rotate = true;
		}
	}
}
void displayRotors(Rotor& r1, Rotor& r2, Rotor& r3)
{
	//Shows window number/letter
	/*
	r3.moveRotor();
	r3.numRotations++;
	rotate(r2, r3);
	rotate(r1, r2);
	if (r1.rotate)
	{
		r1.moveRotor();
		r1.numRotations++;
		r1.rotate = false;
	}
	if (r2.rotate)
	{
		r2.moveRotor();
		r2.numRotations++;
		r2.rotate = false;
	}
	*/
	cout << (char)(r1.rotor[0].first + 64) << " " << r1.numRotations << " " << (char)(r2.rotor[0].first + 64) << " " << r2.numRotations << " " << (char)(r3.rotor[0].first + 64) << " " << r3.numRotations << endl;;

	//Shows rotor array order
	/*
	for (int i = 0; i < 26; i++)
	{
		cout << '{' << (char)(r1.rotor[i].first + 64) << ',' << (char)(r1.rotor[i].second + 64) << "} " << '{' << (char)(r2.rotor[i].first + 64) << ',' << (char)(r2.rotor[i].second + 64) << "} " << '{' << (char)(r3.rotor[i].first + 64) << ',' << (char)(r3.rotor[i].second + 64) << '}' << endl;
	}
	*/
}

//Initialization functions
map<int, int> initPlugboard()
{
	map<int, int> plugboard = { {1,1}, {2,2},{3,3},{4,4},{5,5},{6,6},{7,7},{8,8},{9,9},{10,10},{11,11},{12,12},{13,13},{14,14},{15,15},{16,16},{17,17},{18,18},{19,19},{20,20},{21,21},{22,22},{23,23},{24,24},{25,25},{26,26}, };
	cout << "How many cables: ";
	int n = 0;  cin >> n;
	if (n != 0)
	{
		cout << "Enter plugboard configuration: ";
		for (int i = 0; i < n; i++)
		{
			char a, b;
			cin >> a >> b;
			a = tolower(a); b = tolower(b);
			int x = a - 96;
			int y = b - 96;
			plugboard[x] = y;
			plugboard[y] = x;
		}
	}
	return plugboard;
}
map<int, int> initReflector()
{
	map<int, int> reflectorB = { {1,25}, {2,18},{3,21},{4,8},{5,17},{6,19},{7,12},{8,4},{9,16},{10,24},{11,14},{12,7},{13,15},{14,11},{15,13},{16,9},{17,5},{18,2},{19,6},{20,26},{21,3},{22,23},{23,22},{24,10},{25,1},{26,20} };
	map<int, int> reflectorC = { {1,6}, {2,22}, {3,16}, {4,10}, {5,9}, {6,1}, {7,15}, {8,25}, {9,5}, {10,4}, {11,18}, {12,26}, {13,24}, {14,23}, {15,7}, {16,3}, {17,20}, {18,11}, {19,21}, {20,17}, {21,19}, {22,2}, {23,14}, {24,13}, {25,8}, {26,12} };

	cout << "\nChoose a reflector: " << endl;
	cout << "1 - Reflector B" << endl;
	cout << "2 - Reflector C" << endl;
	cout << "Enter reflector number: ";
	int a; cin >> a;
	if (a == 1)
		return reflectorB;
	else
		return reflectorC;
}
Rotor initRotors(int rPosition)
{
	int rotorNum; char startingPos; bool isFirst = false; char ring;
	cout << "Enter rotor number for rotor position " << rPosition << ": ";
	cin >> rotorNum;
	cout << "Enter starting position for rotor position " << rPosition << ": ";
	cin >> startingPos;
	cout << "Enter ring letter to advance to for rotor position " << rPosition << ": ";
	cin >> ring;
	cout << endl;

	if (rPosition == 3)
		isFirst = true;
	Rotor temp(rotorNum, isFirst, toupper(startingPos),toupper(ring));
	return temp;
}

//Simulator 
void enigma(Rotor& r1, Rotor& r2, Rotor& r3, int* letter, map<int, int>& plugboard, map<int, int>& reflector)
{
	*letter = plugboard[*letter];
	r3.firstEncrypt(letter);
	rotate(r2, r3);
	rotate(r1, r2);
	r2.firstEncrypt(letter);
	r1.firstEncrypt(letter);

	//cout << (char)(*letter + 96) << " ";
	*letter = reflector[*letter];
	//cout << (char)(*letter + 96) << " Reflector" << endl;

	r1.secondEncrypt(letter);
	r2.secondEncrypt(letter);
	r3.secondEncrypt(letter);
	//cout << (char)(*letter + 64) << endl;
	*letter = plugboard[*letter];
}

int main()
{
	FAST_IO;

	Rotor r1 = initRotors(1);
	Rotor r2 = initRotors(2);
	Rotor r3 = initRotors(3);
	map<int, int> plugboard = initPlugboard();
	map<int, int> reflector = initReflector();

	int* letter = new int();
	string encrypt;

	cout << "\nEnter message: ";
	string s; getline(cin >> ws, s);
	for (char c : s)
	{
		c = tolower(c);
		*letter = c - 96;
		if (*letter > 26 || *letter < 1)
			encrypt.push_back(c);
		else
		{
			enigma(r1, r2, r3, letter, plugboard, reflector);
			encrypt.push_back(*letter + 96);
		}
	}
	cout << "\nYour encrypted message is: " << encrypt << endl;
}

