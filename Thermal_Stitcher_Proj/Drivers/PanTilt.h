#ifndef PANTILT_H_
#define PANTILT_H_

class PanTilt
{
	public:
		bool Initialize ();
        bool ProcessCommand (const char command [], int size);
    private:
        bool PanPosition ();
        bool TiltPosition ();
};

#endif /* PANTILT_H_ */
