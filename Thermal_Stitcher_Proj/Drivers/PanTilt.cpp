#include "PanTilt.h"

bool PanTilt::Initialize (void)
{
    // Begin by looping through all USB ports with the test message.
    std::cout <<"\n\t\tSearching for Arduino...\n";

    char mode [] = {'8','N','1',0};
    unsigned char receiveBuffer [2];
    for (int usbPort = 16; usbPort <=19; usbPort++)
    {
        std::cout << "\t\tQuerying USB Port: " << (usbPort - 16) << "\n";
        if (RS232_OpenComport(usbPort, BAUD_RATE, mode))
            continue;

        usleep(2000000);
        RS232_cputs(usbPort, COMMAND_QUERY);
        usleep(1000000);
        int n = RS232_PollComport(usbPort, receiveBuffer, 2);
        if (n == 2)
        {
            if (receiveBuffer [0] == COMMAND_PAN &&
                    receiveBuffer [1] == COMMAND_TILT)
                return true;
        }
    }
    return false;
}

bool PanTilt::TiltPosition (int angle)
{
    std::cout << "Tilt Position\n";
    return true;
}

bool PanTilt::PanPosition (int angle)
{
    std::cout << "Pan Position\n";
    return true;
}

bool PanTilt::ProcessCommand (const char command [], int size)
{
    if (size == 4)               // Position (Tilt)
	{
		if (command [0] == 'T' && command [1] == 'P')
            return TiltPosition (10);
		else
            return false;
	}
    else if (size == 5)               // Position (Pan)
	{
		if (command [0] == 'P' && command [1] == 'P')
            return PanPosition (10);
		else
            return false;
	}

    return false;
}
