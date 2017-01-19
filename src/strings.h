#pragma once

namespace cj {

	class Char {
		friend String;
		char32_t ch;
	public:
		Char();
		Char(char32_t ch);
		virtual ~Char() {}
		char32_t get() {
			return ch;
		}
		virtual bool operator==(const Char value);
		virtual bool operator!=(const Char value);
		virtual bool operator>(const Char value);
		virtual bool operator>=(const Char value);
		virtual bool operator<(const Char value);
		virtual bool operator<=(const Char value);
	};

	class Str : public Object {
	protected:
		string s;
	public:
		Str();
		Str(const Str& value);
		Str(Str& value);
		Str(string value);
		Str(const char *value);
		Str(char *value);
		Str(char value);
		Str(int value);
		Str(real value);
		Str(bool value);

		char operator[](size_t index) const;
		char& operator[](size_t index);
		Str& operator=(const Str& value);
		Str operator+(Str value);
		friend Str operator+(const char* value, Str stvalue);
		Str operator+=(Str value);
		bool operator==(Str value);
		bool operator!=(Str value);
		bool operator>(Str value);
		bool operator>=(Str value);
		bool operator<(Str value);
		bool operator<=(Str value);
		int length();
		void resize(int value);
		Str substr(int pos, int count);
		Str substr(int pos);
		virtual size_t find(const Str& str, size_t start = 0);
		size_t rfind(const Str& str, size_t pos = -1) const;

		virtual string to_string();

		virtual ~Str();
	};

	class String : public Object
	{
	protected:
		u32string s;
	public:
		//string s8;
		String();
		String(const String& value);
		String(String& value);
		String(string value);
		String(u32string value);
		String(char32_t value);
		String(const char *value);
		String(char *value);
		String(char value);
		String(int value);
		String(real value);
		String(bool value);
		virtual ~String();

		virtual Char getChar(int index);
		virtual String getCharString(int index);
		virtual void setChar(int index, Char ch);
		virtual void setChar(int index, String ch);

		virtual int getCharCode(int index);
		virtual void setCharCode(int index, int code);
		virtual String& operator=(const String& value);
		virtual String operator+(String value);
		friend String operator+(const char* value, String stvalue);
		virtual String operator+=(String value);
		virtual bool operator==(String value);
		virtual bool operator!=(String value);
		virtual bool operator>(String value);
		virtual bool operator>=(String value);
		virtual bool operator<(String value);
		virtual bool operator<=(String value);
		virtual int getLength();
		virtual void setLength(int value);
		virtual String subString(int pos, int count);
		virtual String subString(int pos);

		virtual int getPos(String str);
		virtual int getPosBack(String str);
		virtual size_t find(const String& str, size_t start = 0);

		virtual string to_string();
		virtual wstring to_wstring();
		virtual char* c_str();
		virtual int toInt();
		virtual real toFloat();
		virtual String upperCase();
		virtual String lowerCase();
		virtual String firstUpperCase();
		virtual String firstLowerCase();
		virtual String allTrim();
		virtual void fromFloat(real value, int digit);
	};



}