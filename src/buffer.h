#pragma once

namespace core {

	class Buffer : public Memory {
	protected:
		int read_pos = 0;
	public:
		Buffer();
		~Buffer();

		virtual int getReadPos();
		virtual void setReadPos(int value);

		virtual bool isEmpty();
		virtual void clear();
		virtual bool eof();
		virtual int read(void *buffer, int count);
	};

}