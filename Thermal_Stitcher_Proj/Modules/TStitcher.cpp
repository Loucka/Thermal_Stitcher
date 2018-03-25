#include "TStitcher.h"

TStitcher::TStitcher() {
	// TODO Auto-generated constructor stub

}

TStitcher::~TStitcher() {
	// TODO Auto-generated destructor stub
}

bool TStitcher::Initialize (void)
{
    Stitcher stitcher = Stitcher::createDefault (false);
	return true;
}

void TStitcher::ProcessCommand (const char command [], int size)
{
}
