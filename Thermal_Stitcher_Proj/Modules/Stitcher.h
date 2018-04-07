#ifndef STITCHER_H_
#define STITCHER_H_

#include <iostream>
#include <fstream>
#include <QString>
#include "opencv2/core/mat.hpp"
#include "opencv2/imgcodecs.hpp"

#define IMAGE_DIMENSION 240
#define ANGLE_CONVERSION_MULTIPLIER -0.64
#define CENTER_PAN_PX 39;
#define CENTER_TILT_PX 29;
#define IMAGE_HEIGHT 60;
#define IMAGE_WIDTH 80;
#define DEFAULT_RED 181
#define DEFAULT_GREEN 109
#define DEFAULT_BLUE 246

class Stitcher
{
	public:
		bool Initialize ();
        void UpdateFinalImage (int panStation, int tiltStation);
        void SaveImage ();
    private:
        cv::Mat _currentImage;
        cv::Mat _finalImage;
        int _centerPan;
        int _centerTilt;
        int _imageHeight;
        int _imageWidth;
        void CalculateFinalPx
            (int panDegree, int tiltDegree, int* finalPanPx, int* finalTiltPx);
        void CalculateFinalDegrees
            (int panDegree, int panPx,
             int tiltDegree, int tiltPx,
             int* finalPanDegree, int* finalTiltDegree);
        bool ObtainOffsets (int panStation, int tiltStation, int* panOffset, int* tiltOffset);
};

#endif /* Stitcher_H_ */
