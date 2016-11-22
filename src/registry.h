#ifdef OS_WINDOWS
#pragma once

namespace cj {

class Registry : public Object {
protected:
	HKEY hRootKey;
	HKEY hCurKey;
public:
	Registry();
	virtual void setRootKey(HKEY hkey);
	virtual bool openKey(String key);
	virtual bool createKey(String key);
	//BOOL createKeyDontVirtualizeFlag(LPCTSTR keyPath);
	virtual bool deleteKey(String key);
	virtual bool closeKey();

	virtual String getStringValue(String name);
	virtual string getAnsiStringValue(String name);
	virtual bool setStringValue(String name, String value);
	virtual bool setAnsiStringValue(String name, string value);
	virtual bool deleteValue(String name);
};

}
#endif
