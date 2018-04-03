#include "PanTilt.h"

bool PanTilt::Initialize (void)
{
    std::cout <<"\n\t\tSearching for Arduino Serial Port...\n\t\t\t\t\t\t";

    char mode [] = {'8','N','1',0};
    if (RS232_OpenComport(USB_PORT, BAUD_RATE, mode))
        return false;
    usleep(COM_DELAY);

    return ExecuteTransmission(COMMAND_QUERY);
}

bool PanTilt::ExecuteTransmission(char *message)
{
    RS232_cputs(USB_PORT, message);
    usleep(COM_DELAY);
    int n = RS232_PollComport(USB_PORT, receiveBuffer, REC_BUF_SIZE);
    if (n == REC_BUF_SIZE)
    {
        if (receiveBuffer [0] == RESPONSE_SUCCESS)
            return true;
    }
    return false;
}

char* PanTilt::RetrieveAngleHex(int angle)
{
    if (angle < 15 || angle > 180)
        return NULL;

    std::string sHex;
    std::stringstream stream;
    stream << "0x"
           << std::setfill ('0') << std::setw(sizeof(int)*2)
           << std::hex << angle;
    sHex = stream.str ();
    int n = sHex.length();
    char hex[n + 1];
    strcpy (hex, sHex.c_str());
    for (int i=0; i<n; i++)
          std::cout << hex[i];

    char* result = {};
    return result;
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
