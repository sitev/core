// testXmlParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "cj.h"

using namespace cj;

#pragma comment(lib, "cjCore.lib")


int main()
{
	XmlParser *xmlParser = new XmlParser();
	String xml = "<servers>\n";
	xml += "<srv ip=\"1.2.3.4\" port=\"443\" />";
	xml += "<srv ip=\"3.4.5.6\" port=\"80\" />";
	xml += "<srv ip=\"5.6.7.8\" port=\"8080\" />";
	xml += "</servers>";
	xmlParser->setString(xml);
	xmlParser->parse();

	int count = xmlParser->lstTag.getCount();

	for (int i = 0; i < count; i++) {
		XmlTag *xmlTag = (XmlTag*)xmlParser->lstTag.getItem(i);
		printf("name = %s\n", xmlTag->name.to_string().c_str());

		int count = xmlTag->lstTag.getCount();
		for (int i = 0; i < count; i++) {
			XmlTag *xmlTag2 = (XmlTag*)xmlTag->lstTag.getItem(i);
			printf("  name2 = %s\n", xmlTag2->name.to_string().c_str());

			int count = xmlTag2->attrs.getCount();
			for (int i = 0; i < count; i++) {
				String name = xmlTag2->attrs.getName(i);
				String value = xmlTag2->attrs.getValue(i);
				printf("    name = %s, value = %s\n", name.to_string().c_str(), value.to_string().c_str());
			}

		}
	}

	getchar();
	return 0;
}
