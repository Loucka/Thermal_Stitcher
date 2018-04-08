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
void Stitcher::CalculateFinalPx(double panDegree, double tiltDegree, double *panOffset, double *tiltOffset)
{
    *panOffset = ((240.00/151.50)*panDegree) - 9.00 - (_centerPan);
    *tiltOffset = ((240.00/152.00)*tiltDegree) + 1.5686 - (_centerTilt);
}

/*
 * Using the current Pan/Tilt of the Positioner, determine the
 * Pan/Tilt being viewed by a single pixel.
*/
void Stitcher::CalculateFinalDegrees (double panDegree, double tiltDegree,
                            double* finalPanDegree, double* finalTiltDegree)
{
    *finalPanDegree = panDegree + (_centerPan * (-2.00/3.00));
    *finalTiltDegree = tiltDegree + (_centerTilt * (-2.00/3.00));
}

void Stitcher::SaveImage ()
{
    cv::imwrite("finalImage.jpg", _finalImage);
}

void Stitcher::UpdateFinalImage(double panDegree, double tiltDegree)
{
  double finalPanDegree, finalTiltDegree;
  double finalPanPx, finalTiltPx;
  double currentPanPx, currentTiltPx;
  _currentImage = cv::imread ("./Modules/Captures/raw_capture.png");
  //CalculateFinalDegrees(panDegree,tiltDegree,
                         //&finalPanDegree, &finalTiltDegree);
  CalculateFinalPx(panDegree, tiltDegree, &finalPanPx, &finalTiltPx);

  for (double row = 0; row < _imageHeight; row++)
      for (double col = 0; col < _imageWidth; col++)
      {
          currentPanPx = col + finalPanPx;
          currentTiltPx = row + finalTiltPx;

          if (currentPanPx < 0.00)
              currentPanPx = 0.00;
          else if (currentPanPx > 239.00)
              currentPanPx = 239.00;

          if (currentTiltPx < 0.00)
              currentTiltPx = 0.00;
          else if (currentTiltPx > 239.00)
              currentTiltPx = 239.00;

          currentPanPx = nearbyint(currentPanPx);
          currentTiltPx = nearbyint(currentTiltPx);
          std::cout<<"\t\tFinal Degrees: P("<<panDegree<<")\tT("<<tiltDegree<<")\n";
          std::cout<<"\t\tFinal Px: P("<<currentPanPx<<")\tT("<<currentTiltPx<<")\n";

        _currentImage.row(row).col(col).copyTo
                (_finalImage.row(currentTiltPx).col(currentPanPx));
      }
}
