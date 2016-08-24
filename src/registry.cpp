#include "cj.h"

namespace cj {

Registry::Registry() {

}

void Registry::setRootKey(HKEY hkey) {
	hRootKey = hkey;
}

bool Registry::openKey(String key) {
	HKEY hkey;
	return RegOpenKeyEx(hRootKey, key.to_string().c_str(), 0, KEY_ALL_ACCESS, &hkey) == ERROR_SUCCESS;
}

bool Registry::createKey(String key) {
	HKEY hkey;
	DWORD disposition;
	return RegCreateKeyEx(hRootKey, key.to_string().c_str(), 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL,
		&hkey, &disposition) == ERROR_SUCCESS;
}

bool Registry::deleteKey(String key) {
	return RegDeleteKey(hRootKey, key.to_string().c_str()) == ERROR_SUCCESS;
}

bool Registry::closeKey() {
	return RegCloseKey(hRootKey) == ERROR_SUCCESS;
}

}