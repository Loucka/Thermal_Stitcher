#include <iostream>
#include "Drivers/PanTilt.h"
#include "Drivers/Imager.h"
#include "Drivers/TFT.h"
#include "Modules/Retriever.h"
#include "Modules/Stitcher.h"


PanTilt _panTilt;
Imager _imager;
TFT _tft;
Retriever _retriever;
Stitcher _stitcher;

void DisplayMessage (std::string message)
{
	std::cout << message;
}

bool ProcessCommand (std::string input)
{
	const char *cstr = input.c_str();
	int length = input.length();
	if (length > 0 && cstr [0] == '$')
	{
		length--;

		if (length == 1 && cstr [1] == 'X')
			return false;
		if (length > 1 && cstr [1] == 'P' && cstr [2] == 'T')
			_panTilt.ProcessCommand(cstr + 3, length - 2);	// Forward to PanTilt
		else if (length > 1 && cstr [1] == 'I' && cstr [2] == 'R')
			_imager.ProcessCommand(cstr + 3, length - 2);	// Forward to Imager
		else if (length > 0 && cstr [1] == 'D')
			_tft.ProcessCommand(cstr + 2, length - 1);
	}

	return true;
}

bool EvaluateInitialization (bool success)
{
	if (success)
		DisplayMessage ("Complete\n");
	else
		DisplayMessage ("Failed\n");

	return success;
}

bool InitializePanTilt ()
{
	DisplayMessage ("\tInitializing Pan/Tilt Driver\t\t");
	return EvaluateInitialization (_panTilt.Initialize ());
}

bool InitializeImager ()
{
	DisplayMessage ("\tInitializing Imager Driver\t\t");
	return EvaluateInitialization (_imager.Initialize ());
}

bool InitializeTFT ()
{
	DisplayMessage ("\tInitializing TFT Display Driver\t\t");
	return EvaluateInitialization (_tft.Initialize ());
}

bool InitializeRetriever ()
{
	DisplayMessage ("\tInitializing Retrieving Module\t\t");
	return EvaluateInitialization (_retriever.Initialize ());
}

bool InitializeStitcher ()
{
	DisplayMessage ("\tInitializing Stitching Module\t\t");
	return EvaluateInitialization (_stitcher.Initialize ());
}

int main()
{
	// Print splash output and.
    	DisplayMessage ("Beginning Thermal Stitcher...\n");

	// Initialize Pan/Tilt Driver
	if (!InitializePanTilt ())
		return -1;

	// Initialize Imager Driver
	if (!InitializeImager ())
		return -1;

	// Initialize TFT Driver
	if (!InitializeTFT ())
		return -1;

	// Initialize Retrieving Module
	if (!InitializeRetriever ())
		return -1;

	// Initialize Stitching Module
	if (!InitializeStitcher ())
		return -1;

	// Begin an infinite loop that will utilize these modules.
	std::string input;
	while (true)
	{
		std::cin >> input;
		if (!ProcessCommand (input))
			break;
	}

    return 0;
}
