#include <iostream>
#include "TFT.h"

TFT::TFT()
{
	// TODO Auto-generated constructor stub

}

TFT::~TFT()
{
	// TODO Auto-generated destructor stub
}

bool TFT::Initialize (void)
{
	return true;
}

bool TFT::ProcessCommand (const char command [], int size)
{
    //# Use command to avoid warning for now.
    if (command [0] == command [0])
    {}

	if (size == 11)
	{
        std::cout << "TFT Display\n";
        return true;
	}

    return false;
}
