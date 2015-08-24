#pragma once

namespace cj {

	class Object;
	class String;
	class List;


	int round(real value);
	void swap(int &A, int &B);
	void swap(real &A, real &B);
	void showMessage(String msg);
	real random(); // 0..1
	int random(int count); // 0..count-1
	String generateUUID();
#ifdef OS_WINDOWS
	void usleep(big usec);
#endif
	ulong getUsageMemory();
	void sendMail(String toEMail, String fromEMail, String subject, String message);
	void sendMail_s(string toEMail, string fromEMail, string subject, string message);
	String dtRus(String dtUsa, int format);

	class Object {
	public:
		Object();
		virtual ~Object();

		virtual String getClassName();
		virtual String getObjectName();
		virtual void setObjectName(String value);

		virtual bool isParentClassExist(String className);
	};

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

	class String : public Object
	{
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

		virtual string toString8();
		virtual int toInt();
		virtual real toFloat();
		virtual String upperCase();
		virtual String lowerCase();
		virtual String firstUpperCase();
		virtual String firstLowerCase();
		virtual void fromFloat(real value, int digit);
	};

#define LIST_CAPACITY_STEP 256
	class List : public Object
	{
		int count, capacity;
		Object **memory;
	public:
		List();
		virtual ~List();
		virtual void assign(List *list);

		virtual int getCapacity();
		virtual void setCapacity(int value);
		virtual int getCount();
		virtual Object* add(Object* item);
		virtual void insert(int index, Object* item);
		virtual Object* getItem(int index);
		virtual Object* getFirst();
		virtual Object* getLast();
		virtual void setItem(int index, Object* item);
		virtual void change(int index1, int index2);
		virtual void moveTo(int index1, int index2);
		virtual int indexOf(Object* item);
		virtual void del(int index);
		virtual int del(Object *item);
		virtual void remove(int index);
		virtual int remove(Object* item);
		virtual void clear();
		virtual void kill();
	};


	class StringList : public List
	{
	public:
		StringList();
		String getClassName();
		void add(String* str);
		void add(String str);
		void insert(int index, String str);
		String* getItem(int index);
		String getString(int index);
		void setItem(String* str, int index);
		void setString(String str, int index);
		int indexOf(String* Item);
		int remove(String* Item);
		int remove(String str);
		bool find(String str);
	};

	class ParamList : public Object {
	public:
		map<string, string> pars;
		ParamList();
		virtual ~ParamList();

		virtual void add(String name, String value);
		virtual void insert(String name, String value);
		virtual void clear();
		virtual int getCount();
		virtual bool parse(String s);
		virtual String getValue(String name);
		virtual String getName(int index);
		virtual String getValue(int index);

		virtual void add(string name, string value);
		virtual void insert(string name, string value);
		virtual string getValue_s(string name);
		virtual string getName_s(int index);
		virtual string getValue_s(int index);
	};

	class Map : public ParamList {

	};

	enum DateTimeFormat { dtfRus, dtfDatabase, dtfYMDhm, dtfMilisecond };

	class DateTime : public Object {
		time_t rawDateTime;
	public:
		DateTime();
		DateTime(int day, int month, int year);
		DateTime(String s, DateTimeFormat dtf);
		virtual void now();
		virtual void setDate(int day, int month, int year);
		virtual void setTime(int hour, int minute, int second);
		virtual void set(String s, DateTimeFormat dtf);
		virtual void getDate(int &day, int &month, int &year);
		virtual void getTime(int &hour, int &min, int &sec);
		virtual String toString();
		virtual String toString(DateTimeFormat dtf);
		virtual bool isCorrect();
		virtual long getRawDateTime();
		virtual long getDifference(DateTime dt);
		virtual int getAge();
		virtual int minusDay();
		virtual bool operator==(DateTime value);
		virtual bool operator!=(DateTime value);
		virtual bool operator>(DateTime value);
		virtual bool operator>=(DateTime value);
		virtual bool operator<(DateTime value);
		virtual bool operator<=(DateTime value);
	};

	
	//  Базовый класс для запрещения операций копирования объектов
	class NonCopyable
	{
	protected:
		NonCopyable() {}
	private:
		NonCopyable(const NonCopyable&);
		NonCopyable& operator = (const NonCopyable&);
	};
	
}
