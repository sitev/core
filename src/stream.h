#pragma once

namespace cj {

class Stream : public Object
{
protected:
	int pos; 
	int size;
public:
	Stream();
	virtual ~Stream();
	virtual int read(void *buffer, int count) = 0;
	virtual int write(void *buffer, int count) = 0;
	virtual void set(Stream* source);
	virtual void set(Stream* source, int size);
	virtual int getSize();
	virtual void setSize(int value);
	virtual int getPos();
	virtual void setPos(int value);
	virtual bool getEnd();

	virtual int readInt(int &value);
	virtual int writeInt(int value);
	virtual int readUInt(uint &value);
	virtual int writeUInt(uint value);

	virtual int readChar(char &value);
	virtual int writeChar(char value);
	virtual int readUChar(uchar &value);
	virtual int writeUChar(uchar value);

	virtual int readShort(short &value);
	virtual int writeShort(short value);
	virtual int readUShort(ushort &value);
	virtual int writeUShort(ushort value);

	virtual int readLong(long &value);
	virtual int writeLong(long value);
	virtual int readULong(ulong &value);
	virtual int writeULong(ulong value);

	virtual int readBig(int &value);
	virtual int writeBig(int value);
	virtual int readUBig(ubig &value);
	virtual int writeUBig(ubig value);

	virtual int readFloat(float &value);
	virtual int writeFloat(float value);

	virtual int readDouble(double &value);
	virtual int writeDouble(double value);

	virtual int readReal(real &value);
	virtual int writeReal(real value);

	virtual int readBool(bool &value);
	virtual int writeBool(bool value);

	virtual int readString(String &value);
	virtual int writeString(String value);
};

class Memory : public Stream
{
public:
	void *data;
	Memory();
	virtual ~Memory();
	virtual int read(void *buffer, int count);
	virtual int write(void *buffer, int count);
	virtual void set(Stream* source);
	virtual void set(Stream* source, int size);
	virtual void setSize(int value);
};

class File : public Stream
{
protected:
	FILE *f;
	virtual bool open();
	string fileName;
	string mode;
public:
	File(String fileName, String mode);
	File(String fileName);
	File(string fileName, string mode);
	File(string fileName);
	~File();
	bool isOpen();

	String Class_getName();
	virtual int read(void *buffer, int count);
	virtual int readLine(String &str);
	virtual int readAll(String &str);
	virtual int seek(int offset, int origin);
	virtual int write(void *buffer, int count);
	virtual int write(String str);
	virtual int getSize();
	virtual void setSize(int value);
	virtual int getPos();
	virtual void setPos(int value);
	virtual bool eof();
	virtual void save();

	static void createDir(String dirName);
	static void createDir(string dirName);
	static void createNullFile(String fileName);
	static void createNullFile(string fileName);
	static String getExtention(String fileName);

	virtual FILE* getFILEPointer();
};

}