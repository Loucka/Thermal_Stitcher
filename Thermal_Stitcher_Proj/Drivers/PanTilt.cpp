#include <iostream>
#include "PanTilt.h"

PanTilt::PanTilt()
{
	// TODO Auto-generated constructor stub

}

PanTilt::~PanTilt()
{
	// TODO Auto-generated destructor stub
}

bool PanTilt::Initialize (void)
{
	return true;
}

void PanTilt::ProcessCommand (const char command [], int size)
{
	bool success = true;

	if (size == 2)							// Direction
	{
		if (command [0] == 'P')
		{
			if (command [1] == 'R')
				std::cout << "Pan Right";
			else if (command [1] == 'L')
				std::cout << "Pan Left";
			else if (command [1] == 'S')
				std::cout << "Pan Stop";
			else
				success = false;
		}
		else if (command [0] == 'T')
		{
			if (command [1] == 'U')
				std::cout << "Tilt Up";
			else if (command [1] == 'D')
				std::cout << "Tilt Down";
			else if (command [1] == 'S')
				std::cout << "Tilt Stop";
			else
				success = false;
		}
		else
			success = false;
	}
	else if (size == 3)						// Velocity
	{
		if (command [1] == 'V')
		{
			if (command [0] == 'P')
				std::cout << "Pan Velocity";
			else if (command [0] == 'T')
				std::cout << "Tilt Velocity";
			else
				success = false;
		}
		else
			success = false;
	}
	else if (size == 4)						// Position (Tilt)
	{
		if (command [0] == 'T' && command [1] == 'P')
			std::cout << "Tilt Position";
		else
			success = false;
	}
	else if (size == 5)						// Position (Pan)
	{
		if (command [0] == 'P' && command [1] == 'P')
			std::cout << "Pan Position";
		else
			success = false;
	}
	else
		success = false;

	if (!success)
		std::cout << "Pan/Tilt Unknown";

	std::cout << "\n";
}
