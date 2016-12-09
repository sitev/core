#pragma once

namespace cj {

	class Object;
	class String;
	class List;


	class Object {
	public:
		Object();
		virtual ~Object();

		virtual String getClassName();
		virtual String getObjectName();
		virtual void setObjectName(String value);

		virtual bool isParentClassExist(String className);
	};

	enum DateTimeFormat { dtfRus, dtfDatabase, dtfYMDhm, dtfMilisecond };

	class DateTime : public Object {
	protected:
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
		virtual void setRawDateTime(long rawDT);
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
