#ifndef RETRIEVER_H_
#define RETRIEVER_H_
#include <iostream>
#include <thread>
#include "Drivers/PanTilt.h"
#include "Drivers/Imager.h"

class Retriever
{
	public:
        enum RunningStates { running, paused, complete, failed, idle };
        bool Initialize (PanTilt &panTilt, Imager &imager);
        bool ProcessCommand (const char command [], int size);
        void BeginCapture ();
        void PauseCapture ();
        void ResetCapture ();
        void SetRows (int rows);
        void SetColumns (int columns);
        RunningStates RunningState;   // Manages the state of running.
    private:
        PanTilt _panTilt;               // Reference to PanTilt Driver.
        Imager _imager;                 // Reference to Imager Driver.
        int _iRows;                     // Number of rows to capture.
        int _iColumns;                  // Number of columns to capture.
        void RetrievalThread (int rows, int columns, PanTilt panTilt, Imager imager);        // Executes actual retrieving
        std::thread _retrievalThread;   // Manages the retrieving action.
};

#endif /* Retriever_H_ */
