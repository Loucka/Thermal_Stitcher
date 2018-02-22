#ifndef RETRIEVER_H_
#define RETRIEVER_H_
#include "Drivers/PanTilt.h"
#include "Drivers/Imager.h"

class Retriever
{
	public:
		Retriever();
		virtual ~Retriever();
		bool Initialize ();
		void ProcessCommand (const char command [], int size);
    private:
        PanTilt _panTilt;   // Reference to PanTilt Driver.
        Imager _imager;     // Reference to Imager Driver.
        int _iRows;         // Number of rows to capture.
        int _iColumns;       // Number of columns to capture.
};

#endif /* Retriever_H_ */
