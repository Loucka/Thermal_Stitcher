#ifndef TFT_H_
#define TFT_H_

class TFT
{
	public:
		TFT();
		virtual ~TFT();
		bool Initialize ();
        bool ProcessCommand (const char command [], int size);
};

#endif /* TFT_H_ */
