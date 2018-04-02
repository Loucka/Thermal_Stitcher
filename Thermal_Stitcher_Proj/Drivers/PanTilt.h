#ifndef PANTILT_H_
#define PANTILT_H_
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "Third-Party/RS-232/rs232.h"

#define BUF_SIZE 5

class PanTilt
{
	public:
		bool Initialize ();
        bool ProcessCommand (const char command [], int size);
        bool PanPosition (int angle);
        bool TiltPosition (int angle);
    private:
        int BAUD_RATE = 57600; // 9600 baud
        char COMMAND_BEGIN = '$';
        char COMMAND_END {'~'};
        char COMMAND_PAN {'P'};
        char COMMAND_TILT {'T'};
        char COMMAND_REQUEST {'?'};
        char RESPONSE_QUERY [2] = {COMMAND_PAN, COMMAND_TILT};
        char COMMAND_QUERY [5] = {COMMAND_BEGIN,
                                    COMMAND_PAN,
                                    COMMAND_TILT,
                                    COMMAND_REQUEST,
                                    COMMAND_END};
};

#endif /* PANTILT_H_ */
