#ifndef RETRIEVER_H_
#define RETRIEVER_H_

class Retriever
{
	public:
		Retriever();
		virtual ~Retriever();
		bool Initialize ();
		void ProcessCommand (const char command [], int size);
};

#endif /* Retriever_H_ */
