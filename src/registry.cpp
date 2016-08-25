#include "cj.h"

namespace cj {

Registry::Registry() {

}

void Registry::setRootKey(HKEY hkey) {
	hRootKey = hkey;
}

bool Registry::openKey(String key) {
	return RegOpenKeyEx(hRootKey, key.to_string().c_str(), 0, KEY_ALL_ACCESS, &hCurKey) == ERROR_SUCCESS;
}

bool Registry::createKey(String key) {
	DWORD disposition;
	return RegCreateKeyEx(hRootKey, key.to_string().c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
		&hCurKey, &disposition) == ERROR_SUCCESS;
}

bool Registry::deleteKey(String key) {
	return RegDeleteKey(hRootKey, key.to_string().c_str()) == ERROR_SUCCESS;
}

bool Registry::closeKey() {
	return RegCloseKey(hRootKey) == ERROR_SUCCESS;
}

String Registry::getStringValue(String name) {
	char *value = (char*)malloc(8192);
	DWORD cbData;
	if (RegQueryValueEx(hCurKey, name.to_string().c_str(), NULL, NULL, (LPBYTE)value, &cbData) == ERROR_SUCCESS)
		return value;
	return "";
}

bool Registry::setStringValue(String name, String value) {
	return RegSetValueEx(hCurKey, name.to_string().c_str(), 0, REG_SZ, (const BYTE*)value.to_string().c_str(), 
		value.getLength()) == ERROR_SUCCESS;
}

}