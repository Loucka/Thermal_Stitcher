#include "Retriever.h"

void Retriever::RetrievalThread ()
{
    std::cout << "Beginning Retrieval\n";
    int iCurrentRow;
    int iCurrentColumn;

    for (iCurrentRow = 0; iCurrentRow < _iRows; iCurrentRow++)
    {
        for (iCurrentColumn = 0; iCurrentColumn < _iColumns; iCurrentColumn++)
        {
            // Direct the PanTilt to the appropriate
            // station. Once approached, retrieve an image
            // and create a renamed copy that reflects its index.


            //# This is a test.
            std::this_thread::sleep_for (std::chrono::seconds(1));
            if (_imager.CaptureImage ())
            {
                //QFile::copy(ORIG_FILE, CAPTURE_DIRECTORY +
                          // "[" + std::to_string(iCurrentRow) + "],[" +
                            //std::to_string(iCurrentColumn) + "].png");
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

    RunningState = running;
    _retrievalThread = std::thread
            (&Retriever::RetrievalThread, this);
    _retrievalThread.join();
}

void Retriever::PauseCapture ()
{
    std::cout << "Capture Paused\n";
}

void Retriever::ResetCapture ()
{
    std::cout << "Capture Reset\n";
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
            return true;
        }
        else if (command [1] == 'P')
        {
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
