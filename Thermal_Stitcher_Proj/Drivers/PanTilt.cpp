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

bool PanTilt::PanRight ()
{
    std::cout << "Pan Right\n";
    return true;
}

bool PanTilt::PanLeft ()
{
    std::cout << "Pan Left\n";
    return true;
}

bool PanTilt::PanStop ()
{
    std::cout << "Pan Stop\n";
    return true;
}

bool PanTilt::PanVelocity ()
{
    std::cout << "Pan Velocity\n";
    return true;
}

bool PanTilt::TiltVelocity ()
{
    std::cout << "Tilt Velocity\n";
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
    if (size == 2)                    // Direction
	{
        if (command [0] == 'P')                 // Pan
		{
			if (command [1] == 'R')
                return PanRight ();
			else if (command [1] == 'L')
                return PanLeft ();
			else if (command [1] == 'S')
                return PanStop ();
			else
                return false;
		}
        else if (command [0] == 'T')            // Tilt
		{
			if (command [1] == 'U')
                std::cout << "Tilt Up\n";
			else if (command [1] == 'D')
                std::cout << "Tilt Down\n";
			else if (command [1] == 'S')
                std::cout << "Tilt Stop\n";
			else
                return false;
		}
		else
            return false;
	}
    else if (size == 3)               // Velocity
	{
		if (command [1] == 'V')
		{
			if (command [0] == 'P')
                return PanVelocity ();
			else if (command [0] == 'T')
                return TiltVelocity ();
			else
                return false;
		}
		else
            return false;
	}
    else if (size == 4)               // Position (Tilt)
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
