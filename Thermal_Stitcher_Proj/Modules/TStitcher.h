#ifndef TSTITCHER_H_
#define TSTITCHER_H_

#include <iostream>
#include <fstream>
#include <QString>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

class TStitcher
{
	public:
		bool Initialize ();
        void BeginStitching (int rows, int columns);
        void PauseStitching ();
        void ResetStitching ();
    private:
        cv::Stitcher _stitcher;
};

#endif /* TStitcher_H_ */
