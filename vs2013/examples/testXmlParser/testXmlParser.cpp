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

	int count = xmlParser->lstNode.getCount();

	for (int i = 0; i < count; i++) {
		XmlNode *xmlNode = (XmlNode*)xmlParser->lstNode.getItem(i);
		printf("name = %s\n", xmlNode->name.to_string().c_str());

		int count = xmlNode->lstNode.getCount();
		for (int i = 0; i < count; i++) {
			XmlNode *xmlNode2 = (XmlNode*)xmlNode->lstNode.getItem(i);
			printf("  name2 = %s\n", xmlNode2->name.to_string().c_str());

			int count = xmlNode2->params.getCount();
			for (int i = 0; i < count; i++) {
				String name = xmlNode2->params.getName(i);
				String value = xmlNode2->params.getValue(i);
				printf("    name = %s, value = %s\n", name.to_string().c_str(), value.to_string().c_str());
			}

		}
	}

	getchar();
	return 0;
}
