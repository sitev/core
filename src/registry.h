#pragma once

namespace cj {

class Registry : public Object {
protected:
	HKEY hRootKey;
public:
	Registry();
	virtual void setRootKey(HKEY hkey);
	virtual bool openKey(String key);
	virtual bool createKey(String key);
	virtual bool deleteKey(String key);
	virtual bool closeKey();
};

}