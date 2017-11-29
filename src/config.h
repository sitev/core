#pragma once

namespace core {

class Config : public ParamList
{
public:
	Config();
	virtual ~Config();

	virtual bool loadFromFile(String fileName);
	virtual bool parse(String s);
};

}
