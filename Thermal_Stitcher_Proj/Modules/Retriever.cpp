#include "Retriever.h"

void Retriever::RetrievalThread (int rows, int columns, PanTilt panTilt, Imager imager)
{
    std::cout << "Beginning Retrieval\n";
    int iCurrentRow;
    int iCurrentColumn;

    for (iCurrentRow = 0; iCurrentRow < rows; iCurrentRow++)
    {
        for (iCurrentColumn = 0; iCurrentColumn < columns; iCurrentColumn++)
        {
            // Direct the PanTilt to the appropriate
            // station. Once approached, retrieve an image
            // and create a renamed copy that reflects its index.
            std::this_thread::sleep_for (std::chrono::seconds(1));
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
    std::cout << "Capture Initiated\n";
    RunningState = running;
    _retrievalThread = std::thread
            (&Retriever::RetrievalThread, this, _iRows, _iColumns, _panTilt, _imager);
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
