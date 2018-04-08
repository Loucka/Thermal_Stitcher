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
    int iCurrentTilt;
    int iCurrentPan;
    bool bContinue;
    bool bPanSkip = false;
    bool bTiltSkip = false;
    int iPanCounter = 4;
    int iTiltCounter = 4;

    for (iCurrentTilt = _angleStart; iCurrentTilt <= _angleEnd; iCurrentTilt++)
    {
        if (bTiltSkip)
        {
            if (iTiltCounter == 5)
            {
                iTiltCounter = 0;
                bTiltSkip = false;
            }
            else
                iTiltCounter++;

            continue;
        }
        else
        {
            iTiltCounter++;
            if (iTiltCounter == 10)
                bTiltSkip = true;
        }

        bContinue = false;
        for (iCurrentPan = _angleStart; iCurrentPan < _angleEnd; iCurrentPan++)
        {
            // Because the servos suck, we need to avoid problematic pan values.
            if (bPanSkip)
            {
                if (iPanCounter == 5)
                {
                    iPanCounter = 0;
                    bPanSkip = false;
                }
                else
                    iPanCounter++;

                continue;
            }
            else
            {
                iPanCounter++;
                if (iPanCounter == 10)
                    bPanSkip = true;
            }

            if (RunningState == idle)
                return;
            if (RunningState == paused)
            {
                bContinue = true;
                continue;
            }

            _panTilt.PanPosition(iCurrentPan);
            _panTilt.TiltPosition(iCurrentTilt);

            // Once approached, retrieve an image
            // and create a renamed copy that reflects its index.
            //# This is a test. We're only polling for test photos.
            std::this_thread::sleep_for (std::chrono::milliseconds(200));
            if (_imager.CaptureImage ())
            {
                _stitcher.UpdateFinalImage
                        (static_cast<double>(iCurrentPan),
                         static_cast<double>(iCurrentTilt));
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
            iCurrentTilt--;
            iCurrentPan--;
        }
    }

    // Once complete, change our running state.
    std::cout << "Retrieval Complete\n";
    RunningState = complete;

    // Pass off information to the Stitcher.//# Fix this shit.
    _stitcher.SaveImage ();
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
        _angleStart = ANGLE_START;
        _angleEnd = ANGLE_END;
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
