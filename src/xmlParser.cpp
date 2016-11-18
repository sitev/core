#include "cj.h"

namespace cj {

XmlTag::XmlTag() {

}

XmlParser::XmlParser() {

}

void XmlParser::setString(String xml) {
	this->xml = xml;
}

bool XmlParser::isLetter(Char ch) {
	char c = ch.get();
	if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z') return true;
	return false;
}

int XmlParser::getChar(Char &ch) {
	ch = xml.getChar(pos);
	return 1;
}

bool XmlParser::isNull(Char ch) {
	if (ch <= 32) return true;
	return false;
}

void XmlParser::skipNull() {
	while (true) {
		Char ch = xml.getChar(pos);
		if (!isNull(ch)) return;
		pos++;
	}
}


int XmlParser::parseTag(XmlTag *owner) {
	// return -1 : error
	//         1 : ok
	//		   2: завершающий тег

	//find <
	skipNull();
	Char ch = xml.getChar(pos);
	char c = ch.get();
	if (ch != '<') return -1;
	pos++;

	//find /
	skipNull();
	ch = xml.getChar(pos);
	c = ch.get();
	if (ch == '/' && owner != NULL) {
		pos++;
		return 2;
	}

	//get Tag name 
	skipNull();
	String name = "";
	while (true) {
		Char ch = xml.getChar(pos);
		if (!isLetter(ch)) break;
		name += ch.get();
		pos++;
	}
	//printf("tag name = %s\n", name.to_string().c_str());

	if (name == "") return -1;

	XmlTag *xmlTag = new XmlTag();
	xmlTag->name = name;
	//lstTag.add(xmlTag);
	
	if (owner == NULL) {
		//printf("owner == NULL\n");
		lstTag.add(xmlTag);
	}
	else {
		//printf("owner != NULL\n");
		owner->lstTag.add(xmlTag);
	}
	skipNull();

	int result = parseAttrs(xmlTag);
	if (result < 1) return result;

	skipNull();

	//find > or />
	ch = xml.getChar(pos);
	if (ch == '/') {
		pos++;
		ch = xml.getChar(pos);
		if (ch == '>') {
			pos++;
			return 1;
		}
	}
	if (ch != '>') return -1;
	pos++;

	skipNull();

	//find sub Tags
	while (true) {
		result = parseTag(xmlTag);
		//if (result < 1) return result;
		if (result != 1) break;
	}

	if (result != 2) {
		xmlTag->value = "";
		while (true) {
			ch = xml.getChar(pos);
			pos++;
			if (ch == '<') {
				//printf("value = %s\n", xmlTag->value.to_string().c_str());

				//find /
				skipNull();
				ch = xml.getChar(pos);
				c = ch.get();
				if (ch == '/') {
					pos++;
					break;
				}
				else return -1;
			}
			xmlTag->value = xmlTag->value + ch.get();
		}
	}

	//Окончание тега
	//get node name 
	skipNull();
	String name2 = "";
	while (true) {
		Char ch = xml.getChar(pos);
		if (!isLetter(ch)) break;
		name2 = name2 + ch.get();
		pos++;
	}

	//printf("name = %s\n", name.to_string().c_str());
	//printf("name2 = %s\n", name2.to_string().c_str());
	if (name2 == "") return -1;
	if (name != name2) return -1;

	//find >
	skipNull();
	ch = xml.getChar(pos);
	if (ch != '>') return -1;
	pos++;

	//printf("return 1;\n");
	return 1;
}

int XmlParser::parseAttrs(XmlTag *xmlTag) {
	while (true) {
		skipNull();

		string name = "";
		while (true) {
			Char ch = xml.getChar(pos);
			if (!isLetter(ch)) break;
			name += ch.get();
			pos++;
		}

		if (name == "") return 1;

		skipNull();

		Char ch;
		int result = getChar(ch);
		if (result < 1) return result;
		if (ch != '=') return -1;
		pos++;

		result = getChar(ch);
		if (result < 1) return result;
		if (ch != '\"') return -1;
		pos++;

		string value = "";
		while (true) {
			Char ch;
			int result = getChar(ch);
			if (result < 1) return result;
			if (ch == '\"') {
				pos++;
				break;
			}
			value += ch.get();
			pos++;
		}

		xmlTag->attrs.add(name, value);
	}

	return 1;
}

bool XmlParser::parse() {
	lstTag.clear();
	pos = 0;

	int result = parseTag(NULL);
	return result == 1;
}

}
