#include "Retriever.h"

void Retriever::PurgeCaptureDirectory()
{
    QDir dir(CAPTURE_DIRECTORY);
    dir.setNameFilters(QStringList() << "*.*");
    dir.setFilter(QDir::Files);
    foreach(QString dirFile, dir.entryList())
    {
        dir.remove(dirFile);
    }
}

void Retriever::RetrievalThread ()
{
    std::cout << "Beginning Retrieval\n";
    int iCurrentRow;
    int iCurrentColumn;
    bool bContinue;

    for (iCurrentRow = 0; iCurrentRow < _iRows; iCurrentRow++)
    {
        bContinue = false;
        for (iCurrentColumn = 0; iCurrentColumn < _iColumns; iCurrentColumn++)
        {
            if (RunningState == idle)
                return;
            if (RunningState == paused)
            {
                bContinue = true;
                continue;
            }

            /*
            // Direct the PanTilt to the appropriate
            // station.
            _panTilt.PanPosition()
            _panTilt.TiltPosition();
            while (_panTilt.SeekingPan)
            {
                // wait until timeout. Bail if received.
                RunningState = failed;
            }
            */
            _panTilt.PanPosition(PAN_STATIONS[iCurrentColumn]);
            _panTilt.TiltPosition(TILT_STATIONS[iCurrentRow]);

            // Once approached, retrieve an image
            // and create a renamed copy that reflects its index.
            //# This is a test. We're only polling for test photos.
            std::this_thread::sleep_for (std::chrono::seconds(1));
            if (_imager.CaptureImage ())
            {
                //QString newFile = QString
                       // (CAPTURE_DIRECTORY + "[%1],[%2].png")
                        //.arg(iCurrentRow).arg(iCurrentColumn);
                //QFile::copy(ORIG_FILE, newFile);
                _stitcher.UpdateFinalImage (iCurrentColumn, iCurrentRow);
            }
            else
            {
                // Bail if an error is received.
                std::cout << "Error pulling in images. Bailing";
                RunningState = failed;
                return;
            }
        }

        if (bContinue)
        {
            iCurrentRow--;
            iCurrentColumn--;
        }
    }

    // Once complete, change our running state.
    std::cout << "Retrieval Complete\n";
    RunningState = complete;

    // Pass off information to the Stitcher.//# Fix this shit.
    _stitcher.SaveImage ();
}

void Retriever::SetColumns(int columns)
{
    _iColumns = columns;
}

void Retriever::SetRows(int rows)
{
    _iRows = rows;
}

void Retriever::BeginCapture ()
{
    if (RunningState == running)
        return;

    // Purge the capture directory before
    // beginning any new capture.
    PurgeCaptureDirectory();


    RunningState = running;
    _retrievalThread = std::thread
            (&Retriever::RetrievalThread, this);
    _retrievalThread.detach();
}

void Retriever::PauseCapture ()
{
    if (RunningState == paused)
    {
        std::cout << "Capture Resumed\n";
        RunningState = running;
    }
    else if (RunningState == running)
    {
        std::cout << "Capture Paused\n";
        RunningState = paused;
    }
    else
    {
        std::cout << "No Capture in progress\n";
    }
}

void Retriever::ResetCapture ()
{
    std::cout << "Capture Reset\n";
    RunningState = idle;
}

bool Retriever::Initialize (PanTilt &panTilt, Imager &imager, Stitcher &stitcher)
{
    try
    {
        _panTilt = panTilt;
        _imager = imager;
        _stitcher = stitcher;
        RunningState = idle;
        _iRows = TILT_COUNT;
        _iColumns = PAN_COUNT;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool Retriever::ProcessCommand (const char command [], int size)
{
    if (size == 1)
    {
        if (command [0] == 'B')
        {
            BeginCapture ();
            return true;
        }
        else if (command [0] == 'R')
        {
            ResetCapture ();
            return true;
        }
        else if (command [0] == 'P')
        {
            PauseCapture ();
            return true;
        }
        else
            return false;
    }
    else if (size == 3 && (command[2] >= '0' && command[2] <= '3')) // SR0 - SR3
    {
        return true;
    }
    else
        return false;
}
