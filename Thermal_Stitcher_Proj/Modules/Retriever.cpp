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

    for (iCurrentRow = 0; iCurrentRow < _iRows; iCurrentRow++)
    {
        for (iCurrentColumn = 0; iCurrentColumn < _iColumns; iCurrentColumn++)
        {
            if (RunningState == idle)
                return;
            if (RunningState == paused)
            {
                while (RunningState == paused)
                {
                    // wait.
                }
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

            // Once approached, retrieve an image
            // and create a renamed copy that reflects its index.
            //# This is a test. We're only polling for test photos.
            std::this_thread::sleep_for (std::chrono::seconds(1));
            if (_imager.CaptureImage ())
            {
                QString newFile = QString
                        (CAPTURE_DIRECTORY + "[%1],[%2].png")
                        .arg(iCurrentRow).arg(iCurrentColumn);
                QFile::copy(ORIG_FILE, newFile);
            }
            else
            {
                // Bail if an error is received.
                std::cout << "Error pulling in images. Bailing";
                RunningState = failed;
                return;
            }
        }
    }

    // Once complete, change our running state.
    std::cout << "Retrieval Complete\n";
    RunningState = complete;
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
    else
    {
        std::cout << "Capture Paused\n";
        RunningState = paused;
    }
}

void Retriever::ResetCapture ()
{
    std::cout << "Capture Reset\n";
    RunningState = idle;
}

bool Retriever::Initialize (PanTilt &panTilt, Imager &imager)
{
    try
    {
        _panTilt = panTilt;
        _imager = imager;
        RunningState = idle;
        _iRows = 2;
        _iColumns = 4;
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
