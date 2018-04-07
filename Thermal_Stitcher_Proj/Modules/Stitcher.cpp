#include "Stitcher.h"

bool Stitcher::Initialize (void)
{
    // Initialize the final image and apply a uniform color to
    // all indices. This will allow us to notice blank spots later on.
    _finalImage = cv::Mat (IMAGE_DIMENSION, IMAGE_DIMENSION, CV_8UC3,
                           cv::Scalar(DEFAULT_RED,DEFAULT_GREEN,DEFAULT_BLUE));
    _centerPan = CENTER_PAN_PX;
    _centerTilt = CENTER_TILT_PX;
    _imageHeight = IMAGE_HEIGHT;
    _imageWidth = IMAGE_WIDTH;
	return true;
}

bool Stitcher::ObtainOffsets(int panStation, int tiltStation, int *panOffset, int *tiltOffset)
{
    *panOffset = panStation * IMAGE_WIDTH;
    *tiltOffset = tiltStation * IMAGE_HEIGHT;
}

/*
 * Using the determined Pan/Tilt of a given pixel, determine the
 * pixel it relates to in the final image.
*/
void Stitcher::CalculateFinalPx(int panDegree, int tiltDegree,
                                int *finalPanPx, int *finalTiltPx)
{

}

/*
 * Using the current Pan/Tilt of the Positioner, determine the
 * Pan/Tilt being viewed by a single pixel.
*/
void Stitcher::CalculateFinalDegrees (int panDegree, int panPx,
                            int tiltDegree, int tiltPx,
                            int* finalPanDegree, int* finalTiltDegree)
{
    *finalPanDegree = panDegree + (_centerPan - panPx) * ANGLE_CONVERSION_MULTIPLIER;
    *finalTiltDegree = tiltDegree + (_centerTilt - tiltPx) * ANGLE_CONVERSION_MULTIPLIER;
}

void Stitcher::SaveImage ()
{
    cv::imwrite("finalImage.jpg", _finalImage);
}

void Stitcher::UpdateFinalImage(int panStation, int tiltStation)
{
  int panOffset, tiltOffset;
    //QString file = QString ("./Modules/Captures/raw_capture.png");
    _currentImage = cv::imread ("./Modules/Captures/raw_capture.png");
    //imgs.push_back (cv::imread (file.toUtf8().constData()))
  ObtainOffsets(panStation, tiltStation, &panOffset, &tiltOffset);

  for (int pan = 0; pan < _imageWidth; pan++)
      for (int tilt = 0; tilt < _imageHeight; tilt++)
      {
         _finalImage.at<uchar>(tilt + tiltOffset, pan + panOffset, 0) =
                 _currentImage.at<uchar>(tilt, pan, 0);
         _finalImage.at<uchar>(tilt + tiltOffset, pan + panOffset, 1) =
                 _currentImage.at<uchar>(tilt, pan, 1);
         _finalImage.at<uchar>(tilt + tiltOffset, pan + panOffset, 2) =
                 _currentImage.at<uchar>(tilt, pan, 2);
      }
}
