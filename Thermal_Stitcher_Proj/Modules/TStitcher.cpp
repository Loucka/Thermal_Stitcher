#include "TStitcher.h"

bool TStitcher::Initialize (void)
{
    // Initialize the stitcher.
    _stitcher = cv::Stitcher::createDefault (false);
	return true;
}

void TStitcher::BeginStitching (int rows, int columns)
{
    std::cout << "Beginning Stitching\n";
    std::cout << "\tRows: " << rows << "\n";
    std::cout << "\tColumns: " << columns << "\n";

    // Retrieve number of rows and columns.
    // Count number of files. Should be odd. Subtract 1.

}

void TStitcher::PauseStitching ()
{

}

void TStitcher::ResetStitching ()
{

}
