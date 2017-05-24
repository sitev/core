#include "cj.h"
#include "buffer.h"

namespace cj {

	Buffer::Buffer() {

	}

	Buffer::~Buffer() {

	}

	int Buffer::getReadPos() {
		return pos;
	}

	void Buffer::setReadPos(int value) {
		pos = value;
	}
}