#include <iostream>

using namespace std;

const int MAX_CHANNELS = 512;
const int MAX_PROJECTORS = 64;

void clear(char* arr);
void print(char* arr);
void commands(char* dmx);
void add(char* dmx, unsigned serial, unsigned start, unsigned len, int projectorInfo[3][MAX_PROJECTORS], unsigned& countProjectors);
void remove(char* dmx, unsigned serial, int projectorInfo[3][MAX_PROJECTORS], unsigned& countProjectors);
void move(char* dmx, unsigned serial, unsigned start, int projectorInfo[3][MAX_PROJECTORS], unsigned& countProjectors);

void swap(int& a, int& b);

bool checkInvalidSerial(unsigned serial);
bool checkInvalidInterval(unsigned len, unsigned start);
bool checkInvalidCount(unsigned count);
bool checkIfSerialExists(unsigned serial, int projectorInfo[3][MAX_PROJECTORS], unsigned countProjectors);
bool checkIfDuplicate(unsigned len, unsigned start, int projectorInfo[3][MAX_PROJECTORS], unsigned countProjectors);


unsigned getOnesInBinary(unsigned number);
size_t getProjectorIndex(unsigned serial, int projectorInfo[3][MAX_PROJECTORS], unsigned count);
unsigned getProjectorsCountOnOneChannel(size_t channel, int projectorInfo[3][MAX_PROJECTORS], unsigned countProjectors);
unsigned getDuplicateProjectorsCountOnOneChannel(size_t channel, int projectorInfo[3][MAX_PROJECTORS], unsigned countProjectors);

int main()
{
	char dmx[MAX_CHANNELS];
	commands(dmx);
	
}

void clear(char* arr)
{
	for (size_t i = 0; i < MAX_CHANNELS; i++)
	{
		arr[i] = '_';                              //clears all the channels
	}
}
void print(char* arr)
{
	for (size_t i = 0; i < MAX_CHANNELS; i++)
	{
		cout << arr[i] << ((i + 1) % 50 == 0 ? "\n" : "");			//shows all the channels
	}
	cout << "\n";
}
void commands(char* dmx)
{
	clear(dmx);
	int projectorInfo[3][MAX_PROJECTORS];				// keeps info for 1 projector on 3 rows 
	unsigned serial, len, start, countProjectors = 0;	//[0][projectID] -> serial |[1][projID] -> len of proj |[2][projID] -> start of proj
	char cmd;
	do
	{
		cout << "Enter a new command: ";
		cin >> cmd;
		switch (cmd)
		{
		case 'a':
			cin >> serial >> len >> start;
			add(dmx, serial, len, start, projectorInfo, countProjectors);
			break;
		case 'r':
			cin >> serial;
			remove(dmx, serial, projectorInfo, countProjectors);
			break;
		case 'm':
			cin >> serial >> start;
			move(dmx, serial, start, projectorInfo, countProjectors);
			break;
		case 'p':
			print(dmx);
			break;
		}
	} while (cmd != 'e');
}
void add(char* dmx, unsigned serial, unsigned len, unsigned start, int projectorInfo[3][MAX_PROJECTORS], unsigned& countProjectors)
{
	if (checkInvalidSerial(serial))
	{
		cout << "Invalid serial number.\n";
		return;
	}
	if (checkInvalidCount(countProjectors))
	{
		cout << "Too much projectors.\n";
		return;
	}
	if (checkInvalidInterval(len, start))
	{
		cout << "Invalid channels.\n";
		return;
	}
	if (checkIfSerialExists(serial, projectorInfo, countProjectors))
	{
		cout << "This serial number already exists.\n";
		return;
	}
	if (checkIfDuplicate(len, start, projectorInfo, countProjectors))
	{
		for (size_t i = start; i < start + len; i++)
		{
			dmx[i] = dmx[i] != 'x' ? '+' : 'x';
		}
		
	}
	else
	{
		for (size_t i = start; i < start + len; i++)
		{
			dmx[i] = dmx[i] == '_' ? 'o' : 'x';
		}
	}
	projectorInfo[0][countProjectors] = serial;
	projectorInfo[1][countProjectors] = len;
	projectorInfo[2][countProjectors] = start;
	countProjectors++;
	
}
void remove(char* dmx, unsigned serial, int projectorInfo[3][MAX_PROJECTORS], unsigned& countProjectors)
{
	if (!checkIfSerialExists(serial, projectorInfo, countProjectors))
	{
		cout << "Serial number doesn't exists.\n";
		return;
	}

	size_t index = getProjectorIndex(serial, projectorInfo, countProjectors);
	unsigned start = projectorInfo[2][index];
	unsigned finish = projectorInfo[2][index] + projectorInfo[1][index];

	for (size_t i = 0; i < 3; i++)
	{
		swap(projectorInfo[i][countProjectors - 1], projectorInfo[i][index]);
	}
	countProjectors--;

	for (size_t i = start; i < finish; i++)
	{
		unsigned dupliProjCountOnOneChannel = getDuplicateProjectorsCountOnOneChannel(i, projectorInfo, countProjectors);
		unsigned projCountOnOneChannel = getProjectorsCountOnOneChannel(i, projectorInfo, countProjectors);

		switch (dmx[i])
		{
		case 'o':
			dmx[i] = '_';
			break;
		case 'x':
			dmx[i] = projCountOnOneChannel >= 2 ? (projCountOnOneChannel == dupliProjCountOnOneChannel ? '+' : 'x') : 'o';
			break;
		case '+':
			dmx[i] = dupliProjCountOnOneChannel < 2 ? 'o' : '+';
			break;
		}
	}
	
}
void move(char* dmx, unsigned serial, unsigned start, int projectorInfo[3][MAX_PROJECTORS], unsigned& countProjectors)
{
	size_t index = getProjectorIndex(serial, projectorInfo, countProjectors);
	unsigned len = projectorInfo[1][index];
	remove(dmx, serial, projectorInfo, countProjectors);
	add(dmx, serial, len, start, projectorInfo, countProjectors);
}
void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

bool checkInvalidSerial(unsigned serial)
{
	return serial % getOnesInBinary(serial) != 0 || serial > (1 << 16);
}
bool checkInvalidInterval(unsigned len, unsigned start)
{
	return len + start >= MAX_CHANNELS || start < 0;
}
bool checkInvalidCount(unsigned count)
{
	return count > MAX_PROJECTORS;
}
bool checkIfSerialExists(unsigned serial, int projectorInfo[3][MAX_PROJECTORS], unsigned countProjectors)
{
	for (size_t i = 0; i < countProjectors; i++)
	{
		if (serial == projectorInfo[0][i])
		{
			return true;
		}
	}
	return false;
}
bool checkIfDuplicate(unsigned len, unsigned start, int projectorInfo[3][MAX_PROJECTORS], unsigned countProjectors)
{
	for (size_t i = 0; i < countProjectors; i++)
	{
		if (projectorInfo[1][i] == len && projectorInfo[2][i] == start)
		{
			return true;
		}
	}
	return false;
}

unsigned getOnesInBinary(unsigned number)
{
	unsigned count = 0;
	while (number != 0)
	{
		count += ((number & 1) == 1 ? 1 : 0);
		number = number >> 1;
	}
	return count;
}
size_t getProjectorIndex(unsigned serial, int projectorInfo[3][MAX_PROJECTORS], unsigned count)
{
	for (size_t i = 0; i < count; i++)
	{
		if (projectorInfo[0][i] == serial)
		{
			return i;
		}
	}
	return -1;
}
unsigned getProjectorsCountOnOneChannel(size_t channel, int projectorInfo[3][MAX_PROJECTORS], unsigned countProjectors)
{
	unsigned count = 0, start, finish;
	
	for (size_t i = 0; i < countProjectors; i++)
	{
		start = projectorInfo[2][i];
		finish = projectorInfo[1][i] + projectorInfo[2][i];
		if (start <= channel && finish > channel)
		{
			count++;
		}
	}
	return count;
}
unsigned getDuplicateProjectorsCountOnOneChannel(size_t channel, int projectorInfo[3][MAX_PROJECTORS], unsigned countProjectors)
{
	unsigned count = 1, start, finish, currStart, currFinish;
	bool found = false;
	for (size_t i = 0; i < countProjectors; i++)
	{
		start = projectorInfo[2][i];
		finish = projectorInfo[1][i] + projectorInfo[2][i];

		for (size_t j = i + 1; j < countProjectors; j++)
		{
			currStart = projectorInfo[2][j];
			currFinish = projectorInfo[1][j] + projectorInfo[2][j];

			if (start <= channel && finish > channel && start == currStart && finish == currFinish)
			{
				count++;
				i = j - 1;
				break;
			}
		}
	}
	return count;
}
