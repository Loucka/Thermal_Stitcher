#ifndef TSTITCHER_H_
#define TSTITCHER_H_

#include <iostream>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

class TStitcher
{
	public:
        TStitcher();
        virtual ~TStitcher();
		bool Initialize ();
        bool ProcessCommand (const char command [], int size);
        void BeginStitching ();
        void PauseStitching ();
        void ResetStitching ();
    private:
        cv::Stitcher stitcher;

};

#endif /* TStitcher_H_ */
