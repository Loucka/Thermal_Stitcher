#ifndef RETRIEVER_H_
#define RETRIEVER_H_
#include <QFile>
#include <QDir>
#include <QString>
#include <iostream>
#include <thread>
#include "Drivers/PanTilt.h"
#include "Drivers/Imager.h"
#include "Modules/TStitcher.h"

class Retriever
{
	public:
        enum RunningStates { running, paused, complete, failed, idle };
        RunningStates RunningState;   // Manages the state of running.

        bool Initialize (PanTilt &panTilt, Imager &imager, TStitcher &stitcher);
        bool ProcessCommand (const char command [], int size);
        void BeginCapture ();
        void PauseCapture ();
        void ResetCapture ();
        void SetRows (int rows);
        void SetColumns (int columns);
    private:
        const QString CAPTURE_DIRECTORY = QString ("./Modules/Captures/");
        const QString ORIG_FILE = QString (CAPTURE_DIRECTORY + "raw_capture.png");
        PanTilt _panTilt;               // Reference to PanTilt Driver.
        Imager _imager;                 // Reference to Imager Driver.
        TStitcher _stitcher;            // Reference to Stitching Module.
        int _iRows;                     // Number of rows to capture.
        int _iColumns;                  // Number of columns to capture.
        std::thread _retrievalThread;   // Manages the retrieving action.

        void RetrievalThread ();        // Executes actual retrieving
        bool CopyImage (std::string newName);
        void PurgeCaptureDirectory ();
};

#endif /* Retriever_H_ */
