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

/*
 * Using the determined Pan/Tilt of a given pixel, determine the
 * pixel it relates to in the final image.
*/
void Stitcher::CalculateFinalPx(int panDegree, int tiltDegree, int *panOffset, int *tiltOffset)
{
    *panOffset = nearbyint (((240/151.5)*panDegree) - 9);
    *tiltOffset = nearbyint (((240/152)*tiltDegree) + 1.5686);
}

/*
 * Using the current Pan/Tilt of the Positioner, determine the
 * Pan/Tilt being viewed by a single pixel.
*/
void Stitcher::CalculateFinalDegrees (int panDegree, int panPx,
                            int tiltDegree, int tiltPx,
                            int* finalPanDegree, int* finalTiltDegree)
{
    *finalPanDegree = nearbyint (panDegree + ((_centerPan - panPx)) * ANGLE_CONVERSION_MULTIPLIER);
    *finalTiltDegree = nearbyint (tiltDegree + ((_centerTilt - tiltPx)) * ANGLE_CONVERSION_MULTIPLIER);
}

void Stitcher::SaveImage ()
{
    cv::imwrite("finalImage.jpg", _finalImage);
}

void Stitcher::UpdateFinalImage(int panDegree, int tiltDegree)
{
  int finalPanDegree, finalTiltDegree;
  int finalPanPx, finalTiltPx;
  _currentImage = cv::imread ("./Modules/Captures/raw_capture.png");
  CalculateFinalDegrees(panDegree, _centerPan,
                         tiltDegree, _centerTilt,
                         &finalPanDegree, &finalTiltDegree);

  CalculateFinalPx(finalPanDegree, finalTiltDegree, &finalPanPx, &finalTiltPx);

  std::cout<<finalPanPx<<": "<<finalTiltPx<<"\n";
  for (int row = 0; row < _imageHeight; row++)
      for (int col = 0; col < _imageWidth; col++)
      {
        _currentImage.row(row).col(col).copyTo
                (_finalImage.row(row + finalTiltPx).col(col + finalPanPx));
      }
}
