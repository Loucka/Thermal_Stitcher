#include "TStitcher.h"

TStitcher::TStitcher() {
	// TODO Auto-generated constructor stub

}

TStitcher::~TStitcher() {
	// TODO Auto-generated destructor stub
}

bool TStitcher::Initialize (void)
{
    // Initialize the stitcher.
    stitcher = cv::Stitcher::createDefault (false);
	return true;
}

void TStitcher::BeginStitching ()
{
    std::cout << "Beginning Stitching\n";
}

void TStitcher::PauseStitching ()
{

}

void TStitcher::ResetStitching ()
{

}

bool TStitcher::ProcessCommand (const char command [], int size)
{
    if (size == 1)
    {
        if (command [0] == 'B')
        {
            BeginStitching ();
            return true;
        }
        else if (command [0] == 'R')
        {
            ResetStitching ();
            return true;
        }
        else if (command [0] == 'P')
        {
            PauseStitching ();
            return true;
        }
        else
            return false;
    }
    else
        return false;
}
