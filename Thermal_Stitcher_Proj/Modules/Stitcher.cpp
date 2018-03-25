#include "Stitcher.h"

Stitcher::Stitcher() {
	// TODO Auto-generated constructor stub

}

Stitcher::~Stitcher() {
	// TODO Auto-generated destructor stub
}

bool Stitcher::Initialize (void)
{
    Stitcher stitcher = Stitcher::createDefault (false);
	return true;
}

void Stitcher::ProcessCommand (const char command [], int size)
{
}
