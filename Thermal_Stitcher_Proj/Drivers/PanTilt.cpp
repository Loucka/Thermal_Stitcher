#include "PanTilt.h"

bool PanTilt::Initialize (void)
{
    std::cout <<"\n\t\tSearching for Arduino Serial Port...\n\t\t\t\t\t\t";

    char mode [] = {'8','N','1',0};
    sendBuffer [0] = COMMAND_BEGIN;
    sendBuffer [1] = COMMAND_PAN;
    sendBuffer [2] = COMMAND_TILT;
    sendBuffer [3] = COMMAND_REQUEST;
    sendBuffer [4] = COMMAND_END;
    if (RS232_OpenComport(USB_PORT, BAUD_RATE, mode))
        return false;
    usleep(COM_DELAY);

    return ExecuteTransmission ();
}

bool PanTilt::ExecuteTransmission()
{
    std::cout<<"Sending: ";
    for (int i = 0; i < 5; i++)
        std::cout<<sendBuffer[i];
    std::cout<<"\n";
    RS232_cputs(USB_PORT, sendBuffer);
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

    return sHex;
}

bool PanTilt::SendPosition(std::string angle)
{
    int n = angle.length();
    char hex[n + 1];
    strcpy (hex, angle.c_str());

    sendBuffer [2] = hex [n - 2];
    sendBuffer [3] = hex [n - 1];

    return ExecuteTransmission();
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
