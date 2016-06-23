#include "cj.h"

namespace cj {

	XmlTag::XmlTag() {

	}

	XmlParser::XmlParser() {

	}

	void XmlParser::setString(String xml) {
		this->xml = xml;
	}

	bool XmlParser::isBukva(Char ch) {
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


	int XmlParser::parseTag(List &lstTag) {
		// return -1 : error
		//         0 : end
		//         1 : ok

		//find <
		skipNull();
		Char ch = xml.getChar(pos);
		char c = ch.get();
		if (ch != '<') return -1;
		pos++;

		//get Tag name 
		skipNull();
		string name = "";
		while (true) {
			Char ch = xml.getChar(pos);
			if (!isBukva(ch)) break;
			name += ch.get();
			pos++;
		}

		if (name == "") return -1;

		XmlTag *xmlTag = new XmlTag();
		xmlTag->name = name;
		lstTag.add(xmlTag);
		
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
			int result = parseTag(xmlTag->lstTag);
			if (result < 1) return result;
		}

	}

	int XmlParser::parseAttrs(XmlTag *xmlTag) {
		while (true) {
			skipNull();

			string name = "";
			while (true) {
				Char ch = xml.getChar(pos);
				if (!isBukva(ch)) break;
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

	void XmlParser::parse() {
		lstTag.clear();
		pos = 0;

		parseTag(lstTag);
	}

}