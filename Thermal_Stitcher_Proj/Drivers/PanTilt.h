#ifndef PANTILT_H_
#define PANTILT_H_

class PanTilt
{
	public:
		PanTilt();
		virtual ~PanTilt();
		bool Initialize ();
        bool ProcessCommand (const char command [], int size);
    private:
        bool PanRight ();
        bool PanLeft ();
        bool PanStop ();
        bool TiltUp ();
        bool TiltDown ();
        bool TiltStop ();
        bool PanVelocity ();
        bool TiltVelocity ();
        bool PanPosition ();
        bool TiltPosition ();
};

#endif /* PANTILT_H_ */
