#include <iostream>
#include "Imager.h"
#include "Third-Party/Lepton/SPI.h"

Imager::Imager() {
	// TODO Auto-generated constructor stub

}

Imager::~Imager() {
	// TODO Auto-generated destructor stub
}

bool Imager::Initialize (void)
{
    return SpiOpenPort (0);
}

void Imager::CaptureImage ()
{
    std::cout << "Imager Capture";
}

void Imager::ProcessCommand (const char command [], int size)
{
	bool success = true;

	if (size == 1)
	{
		if (command [0] == 'C')
            CaptureImage ();
		else
			success = false;
	}
	else
		success = false;

	if (!success)
		std::cout << "Imager Unknown";

	std::cout << "\n";
}
