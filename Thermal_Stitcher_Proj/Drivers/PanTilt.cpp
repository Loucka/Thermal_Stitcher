#include <iostream>
#include "PanTilt.h"

bool PanTilt::Initialize (void)
{
	return true;
}

bool PanTilt::TiltPosition ()
{
    std::cout << "Tilt Position\n";
    return true;
}

bool PanTilt::PanPosition ()
{
    std::cout << "Pan Position\n";
    return true;
}

bool PanTilt::ProcessCommand (const char command [], int size)
{
    if (size == 4)               // Position (Tilt)
	{
		if (command [0] == 'T' && command [1] == 'P')
            return TiltPosition ();
		else
            return false;
	}
    else if (size == 5)               // Position (Pan)
	{
		if (command [0] == 'P' && command [1] == 'P')
            return PanPosition ();
		else
            return false;
	}

    return false;
}
