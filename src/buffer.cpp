#include "core.h"

namespace core {

	Buffer::Buffer() {

	}

	Buffer::~Buffer() {

	}

	int Buffer::getReadPos() {
		return read_pos;
	}

	void Buffer::setReadPos(int value) {
		read_pos = value;
	}

	bool Buffer::isEmpty() {
		if (pos == read_pos) return true;
		return false;
	}

	void Buffer::clear() {
		setPos(0);
		setReadPos(0);
	}

	bool Buffer::eof() {
		int size = getSize();
		return read_pos >= size;
	}

	int Buffer::read(void *buffer, int count) {
		if (data == NULL) return 0;
		if (buffer == NULL) return 0;
		if (count <= 0) return 0;
		char *aData = (char*)data;
		aData += read_pos;
		memcpy(buffer, aData, count);
		read_pos += count;
		return count;
	}
}