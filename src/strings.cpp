#include "cj.h"

namespace cj {

	Char::Char() {
	}

	Char::Char(char32_t ch) {
		this->ch = ch;
	}

	bool Char::operator==(Char value) {
		return ch == value.ch;
	}
	bool Char::operator!=(const Char value) {
		return ch != value.ch;
	}
	bool Char::operator>(const Char value) {
		return ch > value.ch;
	}
	bool Char::operator>=(const Char value) {
		return ch >= value.ch;
	}
	bool Char::operator<(const Char value) {
		return ch < value.ch;
	}
	bool Char::operator<=(const Char value) {
		return ch <= value.ch;
	}

	//--- Str
	Str::Str() {

	}

	Str::Str(const Str& value) {
		s = value.s;
	}

	Str::Str(Str& value) {
		s = value.s;
	}

	Str::Str(string value) {
		s = value;
	}

	Str::Str(const char *value) {
		s = value;
	}

	Str::Str(char *value) {
		s = value;
	}

	Str::Str(char value) {
		s = value;
	}

	Str::Str(int value) {
		s = value;
	}

	Str::Str(real value) {
		s = value;
	}

	Str::Str(bool value) {
		s = value;
	}

	char Str::operator[](size_t index) const {
		return s[index];
	}

	char& Str::operator[](size_t index)	{
		return s[index];
	}

	Str& Str::operator=(const Str& value) {
		s = value.s;
		return *this;
	}
	Str Str::operator+(Str value) {
		return s + value.s;
	}
	Str operator+(const char* value, Str stvalue) {
		return value + stvalue;
	}
	Str Str::operator+=(Str value) {
		return s += value.s;
	}
	bool Str::operator==(Str value) {
		return s == value.s;
	}
	bool Str::operator!=(Str value) {
		return s != value.s;
	}
	bool Str::operator>(Str value) {
		return s > value.s;
	}
	bool Str::operator>=(Str value) {
		return s >= value.s;
	}
	bool Str::operator<(Str value) {
		return s < value.s;
	}
	bool Str::operator<=(Str value) {
		return s <= value.s;
	}
	int Str::length() {
		return s.length();
	}
	void Str::resize(int value) {
		s.resize(value);
	}
	Str Str::substr(int pos, int count) {
		return s.substr(pos, count);
	}
	Str Str::substr(int pos) {
		return s.substr(pos);
	}
	size_t Str::find(const Str& str, size_t start) {
		return s.find(str.s, start);
	}
	size_t Str::rfind(const Str& str, size_t pos) const {
		return s.rfind(str.s, pos);
	}


	Str::~Str() {

	}


	//--- String
	String::String() {
		//		s8 = this->to_string();
	}
	String::String(const String& value) {
		s = value.s;
		//		s8 = this->to_string();
	}
	String::String(String& value) {
		s = value.s;
		//		s8 = this->to_string();
	}
	String::String(string value) {
#ifndef USING_BOOST
		Convert32 convert32;
		s = convert32.from_bytes(value);
#else
		s = boost::locale::conv::utf_to_utf<char32_t>(value);
#endif
	}
	String::String(u32string value) {
		s = value;
		//		s8 = this->to_string();
	}
	String::String(char32_t value) {
		s = value;
		//		s8 = this->to_string();
	}
	String::String(const char *value) {

#ifndef USING_BOOST
		Convert32 convert32;
		string s8 = value;
		s = convert32.from_bytes(s8);
#else
		s = boost::locale::conv::utf_to_utf<char32_t>(value);
#endif

		//		s8 = this->to_string();
	}
	string String::to_string() {
#ifndef USING_BOOST
		Convert32 convert32;
		string s8 = convert32.to_bytes(s);
		return s8;
#else
		string s8 = boost::locale::conv::utf_to_utf<char>(s);
		return s8;
#endif
	}

	wstring String::to_wstring() {
		string s8 = to_string();
		wstring s16(s8.begin(), s8.end());
		return s16;
	}

	char* String::c_str() {
		string s = this->to_string();
		char* ss = (char*)s.c_str();
		return ss;
	}
	String::String(char *value) {

#ifndef USING_BOOST
		Convert32 convert32;
		s = convert32.from_bytes(value);
#else
		s = boost::locale::conv::utf_to_utf<char32_t>(value);
#endif
		//		s8 = this->to_string();
	}
	String::String(char value) {
		char mys[2];
		mys[0] = value;
		mys[1] = 0;

#ifndef USING_BOOST
		Convert32 convert32;
		s = convert32.from_bytes(mys);
#else
		s = boost::locale::conv::utf_to_utf<char32_t>(mys);
#endif
		//		s8 = this->to_string();
	}
	String::String(int value) {

#ifndef USING_BOOST
		Convert32 convert32;
		s = convert32.from_bytes(::to_string(value));
#else
		char values8[20];
		sprintf(values8, "%d", value);
		s = boost::locale::conv::utf_to_utf<char32_t>(values8);
#endif
		//		s8 = this->to_string();
	}
	String::String(real value) {
		fromFloat(value, 10);
		//		s8 = this->to_string();
	}
	String::String(bool value) {

#ifndef USING_BOOST
		Convert32 convert32;
		if (value) s = convert32.from_bytes("1");
		else s = convert32.from_bytes("0");
#else
		if (value) s = boost::locale::conv::utf_to_utf<char32_t>("1");
		else s = boost::locale::conv::utf_to_utf<char32_t>("0");
#endif
		//		s8 = this->to_string();
	}
	String::~String() {
	}

	Char String::getChar(int index) {
		Char ch(s[index]);
		return ch;
	}
	String String::getCharString(int index) {
		String mys = s[index];
		return mys;
	}
	void String::setChar(int index, Char ch) {
		s[index] = ch.ch;
	}
	void String::setChar(int index, String ch) {
		s[index] = ch.s.c_str()[0];
	}
	int String::getCharCode(int index) {
		return 0;
	}
	void String::setCharCode(int index, int code) {
	}
	String& String::operator=(const String& value) {
		s = value.s;
		//		s8 = this->to_string();
		return *this;
	}
	String String::operator+(String value) {
		u32string u32 = this->s + value.s;
		String str(u32);
		return str;
	}
	String operator+(const char* value, String stvalue) {
		String retString(value);
		retString += stvalue;
		return retString;
	}
	String String::operator+=(String value) {
		u32string u32 = s += value.s;
		String str(u32);
		//		s8 = str.to_string();
		return str;
	}
	bool String::operator==(String value) {
		return s == value.s;
	}
	bool String::operator!=(String value) {
		return s != value.s;
	}
	bool String::operator>(String value) {
		return s > value.s;
	}
	bool String::operator>=(String value) {
		return s >= value.s;
	}
	bool String::operator<(String value) {
		return s < value.s;
	}
	bool String::operator<=(String value) {
		return s <= value.s;
	}
	int String::getLength() {
		return s.length();
	}
	void String::setLength(int value) {
	}
	String String::subString(int pos, int count) {
		return s.substr(pos, count);

		if (pos < 0)
			return "";
		String s32;
		try {
			u32string u = s.substr(pos, count);
			s32 = u;
			string s8 = s32.to_string();
		}
		catch (...) {
			u32string u = s.substr(pos, count);
			s32 = u;
			string s8 = s32.to_string();
		}
		return s32;
	}
	String String::subString(int pos) {
		return s.substr(pos);

		if (pos < 0)
			return "";
		String s32;
		u32string u = s.substr(pos);
		s32 = u;
		string s8 = s32.to_string();
		return s32;
	}
	int String::getPos(String str) {
		int len = str.getLength();
		if (len <= 0) return -1;
		for (int i = 0; i <= getLength() - len; i++)
		{
			String s = subString(i, len);
			if (s == str) return i;
		}
		return -1;
	}
	int String::getPosBack(String str) {
		int len = str.getLength();
		if (len <= 0) return -1;
		for (int i = getLength() - len; i >= 0; i--)
		{
			String s = subString(i, len);
			if (s == str) return i;
		}
		return -1;
	}
	size_t String::find(const String& str, size_t start) {
		return s.find(str.s, start);
	}
	int String::toInt() {
		//s8 = "123";
		//int a = stoi(s8);
		String t = s;
		int a = strtol(t.to_string().c_str(), NULL, 0);
		return a;
	}
	real String::toFloat() {
		return 0;
	}
	String String::upperCase() {
		s[0] = towupper(s[0]);
		return *this;
	}
	String String::lowerCase() {
		int count = getLength();
		String s = *this;
		for (int i = 0; i < count; i++)
		{
			int Code = getCharCode(i);
			if (Code >= 65 && Code <= 90)
			{
				s.setCharCode(i, Code + 32);
			}
		}
		return s;
	}
	String String::firstUpperCase() {
		int count = getLength();
		if (count == 0) return "";

		String s = *this;
		int Code = getCharCode(0);
		if (Code >= 97 && Code <= 122)
		{
			s.setCharCode(0, Code - 32);
		}
		return s;
	}
	String String::firstLowerCase() {
		int count = getLength();
		if (count == 0) return "";

		String s = *this;
		int Code = getCharCode(0);
		if (Code >= 65 && Code <= 90)
		{
			s.setCharCode(0, Code + 32);
		}
		return s;
	}
	String String::allTrim() {
		String s = "";
		string ss = this->to_string();
		int count = getLength();
		for (int i = 0; i < count; i++) {
			Char ch = getChar(i);
			if (ch != 32) s += ch.get();
		}
		return s;
	}
	void String::fromFloat(real value, int digit) {
	}

}