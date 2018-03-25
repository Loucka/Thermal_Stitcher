#ifndef STITCHER_H_
#define STITCHER_H_

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching.hpp"

class Stitcher
{
	public:
		Stitcher();
		virtual ~Stitcher();
		bool Initialize ();
		void ProcessCommand (const char command [], int size);
};

#endif /* Stitcher_H_ */
