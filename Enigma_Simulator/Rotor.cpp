#include "Rotor.h"
#include <algorithm>

using namespace std;

Rotor::Rotor(int rotorNum, bool isFirst, char startingPos, char ring)
{
	setRotor(rotorNum);
	if (isFirst)
		isFirstRotor = true;
	numRotations = startingPos - 65; // Assuming default startng position is 1 1 1 or A A A
	moveRotor(numRotations);
	ringSetup(ring);
}

void Rotor::setRotor(int rotorNum)
{
	vector<pair<int, int>> r1 = { {1,5}, {2,11}, {3,13}, {4,6}, {5,12}, {6,7}, {7,4}, {8,17}, {9,22}, {10,26}, {11,14}, {12,20}, {13,15}, {14, 23}, {15,25}, {16,8}, {17,24}, {18,21}, {19,19}, {20,16}, {21,1}, {22,9}, {23,2}, {24,18}, {25,3}, {26,10} };

	vector<pair<int, int>> r2 = { {1,1}, {2,10}, {3,4}, {4,11}, {5,19}, {6,9}, {7,18}, {8,21}, {9,24}, {10,2}, {11,12}, {12,8}, {13,23}, {14, 20}, {15,13}, {16,3}, {17,17}, {18,7}, {19,26}, {20,14}, {21,16}, {22,25}, {23,6}, {24,22}, {25,15}, {26,5} };

	vector<pair<int, int>> r3 = { {1,2}, {2,4}, {3,6}, {4,8}, {5,10}, {6,12}, {7,3}, {8,16}, {9,18}, {10,20}, {11,24}, {12,22}, {13,26}, {14,14}, {15,25}, {16,5}, {17,9}, {18,23}, {19,7}, {20,1}, {21,11}, {22,13}, {23,21}, {24,19}, {25,17}, {26,15} };

	vector<pair<int, int>> r4 = { {1,5}, {2,19}, {3,15}, {4,22}, {5,16}, {6,26}, {7,10}, {8,1}, {9,25}, {10,17}, {11,21}, {12,9}, {13,18}, {14,8}, {15,24}, {16,12}, {17,14}, {18,6}, {19,20}, {20,7}, {21,11}, {22,4}, {23,3}, {24,13}, {25,23}, {26,2} };

	vector<pair<int, int>> r5 = { {1,22}, {2,26}, {3,2}, {4,18}, {5,7}, {6,9}, {7,20}, {8,25}, {9,21}, {10,16}, {11,19}, {12,4}, {13,14}, {14,8}, {15,12}, {16,24}, {17,1}, {18,23}, {19,13}, {20,10}, {21,17}, {22,15}, {23,6}, {24,5}, {25,3}, {26,11} };

	switch (rotorNum)
	{
	case 1:
		rotor = r1;
		notch = 17;
		break;
	case 2:
		rotor = r2;
		notch = 5;
		break;
	case 3:
		rotor = r3;
		notch = 22;
		break;
	case 4:
		rotor = r4;
		notch = 10;
		break;
	case 5:
		rotor = r5;
		notch = 0;
		break;
	}
}

void Rotor::moveRotor(int numRotations)
{
	for (int i = 0; i < numRotations; i++)
	{
		pair<int, int> temp = rotor[0];
		rotor.erase(rotor.begin());
		rotor.push_back(temp);
	}
}

void Rotor::ringSetup(char ring)
{
	for (int i = 0; i < rotor.size();  i++) {
		if (ring != 'A') {
			rotor[i].second = rotor[i].second % 26 + (ring - 65);
		}
	}
}

void Rotor::firstEncrypt(int* letter)
{
	if (rotate || isFirstRotor)
	{
		moveRotor();
		numRotations++;
		rotate = false;
	}

	//cout << (char)(rotor[*letter - 1].first + 96) << ' ';
	//cout << (char)(rotor[*letter - 1].second + 96) << " First encrypt" << endl;

	int a = rotor[*letter - 1].second - numRotations;
	if (numRotations < rotor[*letter - 1].second)
		*letter = a;
	else
		*letter = 26 - abs(a) % 26;
}

void Rotor::secondEncrypt(int* letter)
{
	for (int i = 0; i < 26; i++)
	{
		int a = (*letter + numRotations) % 26;
		if (a == 0)
			a = 26;
		if (a == rotor[i].second)
		{
			int b = rotor[i].first - numRotations;
			if (numRotations >= rotor[i].first)
				b = 26 - abs(b) % 26;
			*letter = b;

			//cout << (char)(rotor[i].second + 96) << ' ';
			//cout << (char)(rotor[i].first + 96) << " Second encrypt" << endl;
			break;
		}
	}
}


