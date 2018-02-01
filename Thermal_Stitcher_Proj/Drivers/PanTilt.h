#ifndef PANTILT_H_
#define PANTILT_H_

class PanTilt
{
	public:
		PanTilt();
		virtual ~PanTilt();
		bool Initialize ();
		void ProcessCommand (const char command [], int size);
};

#endif /* PANTILT_H_ */
