#ifndef IMAGER_H_
#define IMAGER_H_

class Imager
{
	public:
		Imager();
		virtual ~Imager();
		bool Initialize ();
		void ProcessCommand (const char command [], int size);
    private:
        void CaptureImage ();
};

#endif /* IMAGER_H_ */
