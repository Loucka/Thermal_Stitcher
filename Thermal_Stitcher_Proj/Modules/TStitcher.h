#ifndef TSTITCHER_H_
#define TSTITCHER_H_

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

class TStitcher
{
	public:
        TStitcher();
        virtual ~TStitcher();
		bool Initialize ();
		void ProcessCommand (const char command [], int size);
};

#endif /* TStitcher_H_ */
