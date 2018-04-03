#include "PanTilt.h"

bool PanTilt::Initialize (void)
{
    std::cout <<"\n\t\tSearching for Arduino Serial Port...\n\t\t\t\t\t\t";

    char mode [] = {'8','N','1',0};
    sendBuffer [0] = COMMAND_BEGIN;
    sendBuffer [SEND_BUF_SIZE - 1] = COMMAND_END;
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

std::string PanTilt::RetrieveAngleHex(int angle)
{
    if (angle < 15 || angle > 180)
        return NULL;

    std::string sHex;
    std::stringstream stream;
    stream << "0x"
           << std::setfill ('0') << std::setw(sizeof(int)*2)
           << std::hex << angle;
    sHex = stream.str ();
    /*
    int n = sHex.length();
    char hex[n + 1];
    strcpy (hex, sHex.c_str());
    */

    return sHex;
}

bool PanTilt::SendPosition(std::string angle)
{
    int n = angle.length();
    char hex[n + 1];
    strcpy (hex, angle.c_str());

    sendBuffer [2] = hex [n - 1];
    sendBuffer [3] = hex [n - 1];

    std::cout << hex [1];

    return true;
}

bool PanTilt::TiltPosition (int angle)
{
    std::cout << "Tilt Position\n";
    sendBuffer [1] = COMMAND_TILT;
    return SendPosition (RetrieveAngleHex (angle));
}

bool PanTilt::PanPosition (int angle)
{
    std::cout << "Pan Position\n";
    sendBuffer [1] = COMMAND_PAN;
    return SendPosition (RetrieveAngleHex(angle));
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
