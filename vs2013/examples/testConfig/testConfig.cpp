// testConfig.cpp : Defines the entry point for the console application.
//

#include "cj.h"

using namespace cj;

#pragma comment(lib, "cjCore.lib")

int main(int argc, char* argv[])
{
	Config *cfg = new Config();
	bool flag = cfg->loadFromFile("test.cfg");
	if (flag) {
		int count = cfg->getCount();
		for (int i = 0; i < count; i++) {
			String name = cfg->getName(i);
			String value = cfg->getValue(i);
			printf("name = %s, value = %s\n", name.to_string().c_str(), value.to_string().c_str());
		}
	}
	else {
		printf("Config error!");
	}

	getchar();
	return 0;
}

