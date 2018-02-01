#ifndef STITCHER_H_
#define STITCHER_H_

class Stitcher
{
	public:
		Stitcher();
		virtual ~Stitcher();
		bool Initialize ();
		void ProcessCommand (const char command [], int size);
};

#endif /* Stitcher_H_ */
