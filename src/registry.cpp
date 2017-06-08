#include "core.h"

namespace core {

Registry::Registry() {

}

void Registry::setRootKey(HKEY hkey) {
	hRootKey = hkey;
}

bool Registry::openKey(String key) {
	string k = key.to_string();
    LONG r = RegOpenKeyExA(hRootKey, k.c_str(), 0, KEY_ALL_ACCESS, &hCurKey);
	//LONG r1 = RegDisableReflectionKey(hCurKey);
	return r == ERROR_SUCCESS;
}

bool Registry::createKey(String key) {

	//key = key.OpenSubKey(keyname, RegistryKeyPermissionCheck.ReadWriteSubTree, RegistryRights.FullControl);
	DWORD disposition;
	//REG_KEY_DONT_VIRTUALIZE;
    LONG r = RegCreateKeyExA(hRootKey, key.to_string().c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
		&hCurKey, &disposition);
	//LONG r1 = RegDisableReflectionKey(hCurKey);
	return r == ERROR_SUCCESS;
}

bool Registry::deleteKey(String key) {
    return RegDeleteKeyA(hRootKey, key.to_string().c_str()) == ERROR_SUCCESS;
	//return RegDeleteKeyEx(hRootKey, key.to_string().c_str(), KEY_ALL_ACCESS, 0) == ERROR_SUCCESS;
}

bool Registry::closeKey() {
	return RegCloseKey(hRootKey) == ERROR_SUCCESS;
}

String Registry::getStringValue(String name) {
	/*
	char *value = (char*)malloc(8192);
	DWORD cbData = 8192;
	if (RegQueryValueEx(hCurKey, name.to_string().c_str(), NULL, NULL, (LPBYTE)value, &cbData) == ERROR_SUCCESS)
		return value;
	return "";
	*/

	return getAnsiStringValue(name.to_string());
}

string Registry::getAnsiStringValue(String name) {
	char *value = (char*)malloc(8192);

	DWORD cbData = 8192;
	LOGGER_SCREEN("getAnsiStringValue name = " + name);
    int rez = RegQueryValueExA(hCurKey, name.to_string().c_str(), NULL, NULL, (LPBYTE)value, &cbData);
	bool flag = rez == ERROR_SUCCESS;
	string v = value;
	free(value);
	if (flag) return v;
	return "";
}

bool Registry::setStringValue(String name, String value) {
    return RegSetValueExA(hCurKey, name.to_string().c_str(), 0, REG_SZ, (const BYTE*)value.to_string().c_str(),
		value.getLength()) == ERROR_SUCCESS;
}

bool Registry::setAnsiStringValue(String name, string value) {
    return RegSetValueExA(hCurKey, name.to_string().c_str(), 0, REG_SZ, (const BYTE*)value.c_str(),
		value.length()) == ERROR_SUCCESS;
}

bool Registry::deleteValue(String name) {
    return RegDeleteValueA(hCurKey, name.to_string().c_str()) == ERROR_SUCCESS;
}

}
