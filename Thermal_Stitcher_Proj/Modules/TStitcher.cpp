#include "TStitcher.h"

bool TStitcher::Initialize (void)
{
    // Initialize the stitcher.
    _stitcher = cv::Stitcher::createDefault (false);
    _stitcher.setPanoConfidenceThresh (0.3);
	return true;
}

void TStitcher::BeginStitching (int rows, int columns)
{
    std::cout << "Beginning Stitching\n";
    std::cout << "\tRows: " << rows << "\n";
    std::cout << "\tColumns: " << columns << "\n";

    // Begin by evaluating the number of rows and columns.
    // If more than one row, additional stitching must be done for each column
    // prior to stitching all columns together.

    if (rows > 1)
    {
    }

    // At this point, we should only have one row to stitch.
    // Whether that is by design, or due to additional stitching of
    // multiple rows.
    std::vector<cv::Mat> imgs;
    for (int i = 0; i < columns; i++)
    {
        QString file = QString ("./Modules/Captures/[0],[%1].png").arg(i);
        imgs.push_back (cv::imread (file.toUtf8().constData()));
    }

    cv::Mat result;
    cv::Stitcher::Status status = _stitcher.stitch (imgs, result);
    if (status != cv::Stitcher::OK)
    {
        std::cout<<"Fuck\n";
    }
    else
    {
        std::cout<<"Success\n";
        cv::imwrite("result.jpg", result);
    }
}

void TStitcher::PauseStitching ()
{

}

void TStitcher::ResetStitching ()
{

}
