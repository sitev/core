#include "cj.h"

namespace cj {

Config::Config() {

}


Config::~Config() {
}

bool Config::loadFromFile(String fileName) {
	clear();
	File *f = new File(fileName, "rb");
	while (!f->eof()) {
		String s;
		f->readLine(s);
		string s1 = s.to_string();
		bool flag = parse(s);
		if (!flag) return false;
	}
	delete f;

	return true;
}

bool Config::parse(String s) {
	int pos = s.getPos("=");
	if (pos < 0) return false;
	String name = s.subString(0, pos);
	String value = s.subString(pos + 1);
	string n = name.to_string();
	string v = value.to_string();
	add(name, value);
}


}