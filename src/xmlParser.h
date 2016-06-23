#pragma once

namespace cj {

	class XmlTag : public Object {
	public:
		String name;
		ParamList attrs;
		List lstTag;
		XmlTag();
	};

	class XmlParser : public Object {
	public:
		String xml;
		int pos;
		List lstTag;
		XmlParser();
		virtual void setString(String xml);

		virtual bool isNull(Char ch);
		virtual void skipNull();
		virtual bool isBukva(Char ch);
		virtual int getChar(Char &ch);
		virtual int parseTag(List &lstTag);
		virtual int parseAttrs(XmlTag *xmlTag);
		virtual void parse();
	};

}