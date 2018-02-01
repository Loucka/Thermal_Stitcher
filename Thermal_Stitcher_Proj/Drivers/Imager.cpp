#include <iostream>
#include "Imager.h"

Imager::Imager() {
	// TODO Auto-generated constructor stub

}

Imager::~Imager() {
	// TODO Auto-generated destructor stub
}

bool Imager::Initialize (void)
{
	return true;
}

void Imager::ProcessCommand (const char command [], int size)
{
	bool success = true;

	if (size == 1)
	{
		if (command [0] == 'C')
			std::cout << "Imager Capture";
		else
			success = false;
	}
	else
		success = false;

	if (!success)
		std::cout << "Imager Unknown";

	std::cout << "\n";
}
