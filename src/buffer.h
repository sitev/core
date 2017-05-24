#pragma once

namespace cj {

	class Buffer : public Memory {
	protected:
		int pos = 0;
	public:
		Buffer();
		~Buffer();

		virtual int getReadPos();
		virtual void setReadPos(int value);
	};

}