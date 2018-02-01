#include <iostream>
#include "TFT.h"

TFT::TFT() {
	// TODO Auto-generated constructor stub

}

TFT::~TFT() {
	// TODO Auto-generated destructor stub
}

bool TFT::Initialize (void)
{
	return true;
}

void TFT::ProcessCommand (const char command [], int size)
{
	bool success = true;

	if (size == 11)
	{
		std::cout << "TFT Display";
	}
	else
		success = false;

	if (!success)
		std::cout << "TFT Unknown";

	std::cout << "\n";
}
