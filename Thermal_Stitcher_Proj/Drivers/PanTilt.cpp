#include "PanTilt.h"

bool PanTilt::Initialize (void)
{
    // Begin by looping through all USB ports with the test message.
    std::cout <<"\n\t\tSearching for Arduino Serial Port...\n\t\t\t\t\t\t";

    char mode [] = {'8','N','1',0};
    unsigned char receiveBuffer [2];

    if (RS232_OpenComport(USB_PORT, BAUD_RATE, mode))
        return false;

    usleep(2000000);
    RS232_cputs(USB_PORT, COMMAND_QUERY);
    usleep(1000000);
    int n = RS232_PollComport(USB_PORT, receiveBuffer, 2);
    if (n == 2)
    {
        if (receiveBuffer [0] == COMMAND_PAN &&
                receiveBuffer [1] == COMMAND_TILT)
            return true;
    }
    return false;
}

char* PanTilt::RetrieveAngleHex(int angle)
{
    if (angle < 15 || angle > 180)
        return NULL;

    char* hex = {};
    std::string sHex;
    std::stringstream stream;
    stream << "0x"
           << std::setfill ('0') << std::setw(sizeof(int)*2)
           << std::hex << angle;
    sHex = stream.str ();
    //hex [0] = sHex [0];
    //hex [1] = sHex [1];
    return hex;
}

bool PanTilt::TiltPosition (int angle)
{
    std::cout << "Tilt Position\n";
    RetrieveAngleHex (angle);
    return true;
}

bool PanTilt::PanPosition (int angle)
{
    std::cout << "Pan Position\n";
    RetrieveAngleHex(angle);
    return true;
}

bool PanTilt::ProcessCommand (const char command [], int size)
{
    if (size == 4)               // Position (Tilt)
	{
		if (command [0] == 'T' && command [1] == 'P')
            return TiltPosition (100);
		else
            return false;
	}
    else if (size == 5)               // Position (Pan)
	{
		if (command [0] == 'P' && command [1] == 'P')
            return PanPosition (100);
		else
            return false;
	}

    return false;
}
