#include "cj.h"

namespace cj {

//--------------------------------------------------------------------------------------------------
//----------          Class Stream          --------------------------------------------------------
//--------------------------------------------------------------------------------------------------
Stream::Stream() {
}
Stream::~Stream() {
}
void Stream::set(Stream* source) {
}
void Stream::set(Stream* source, int size) {
}
int Stream::getSize() {
	return size;
}
void Stream::setSize(int value) {
	size = value;
}
int Stream::getPos() {
	return pos;
}
void Stream::setPos(int value) {
	pos = value;
}
bool Stream::getEnd() {
	return pos >= size;
}
int Stream::readInt(int &value) {
	int a;
	read(&a, sizeof(int));
	value = a;
	return 0;
}
int Stream::writeInt(int value) {
	int a = value;
	write(&a, sizeof(int));
	return 0;
}
int Stream::readUInt(uint &value) {
	uint a;
	read(&a, sizeof(uint));
	value = a;
	return 0;
}
int Stream::writeUInt(uint value) {
	uint a = value;
	write(&a, sizeof(uint));
	return 0;
}
int Stream::readChar(char &value) {
	read(&value, sizeof(char));
	return 0;
}
int Stream::writeChar(char value) {
	write(&value, sizeof(char));
	return 0;
}
int Stream::readUChar(uchar &value) {
	read(&value, sizeof(uchar));
	return 0;
}
int Stream::writeUChar(uchar value) {
	write(&value, sizeof(uchar));
	return 0;
}
int Stream::readShort(short &value) {
	read(&value, sizeof(short));
	return 0;
}
int Stream::writeShort(short value) {
	write(&value, sizeof(short));
	return 0;
}
int Stream::readUShort(ushort &value) {
	read(&value, sizeof(ushort));
	return 0;
}
int Stream::writeUShort(ushort value) {
	write(&value, sizeof(ushort));
	return 0;
}
int Stream::readLong(long &value) {
	read(&value, sizeof(long));
	return 0;
}
int Stream::writeLong(long value) {
	write(&value, sizeof(long));
	return 0;
}
int Stream::readULong(ulong &value) {
	read(&value, sizeof(ulong));
	return 0;
}
int Stream::writeULong(ulong value) {
	write(&value, sizeof(ulong));
	return 0;
}
int Stream::readBig(int &value) {
	read(&value, sizeof(int));
	return 0;
}
int Stream::writeBig(int value) {
	write(&value, sizeof(int));
	return 0;
}
int Stream::readUBig(ubig &value) {
	read(&value, sizeof(ubig));
	return 0;
}
int Stream::writeUBig(ubig value) {
	write(&value, sizeof(ubig));
	return 0;
}
int Stream::readFloat(float &value) {
	read(&value, sizeof(float));
	return 0;
}
int Stream::writeFloat(float value) {
	write(&value, sizeof(float));
	return 0;
}
int Stream::readDouble(double &value) {
	read(&value, sizeof(double));
	return 0;
}
int Stream::writeDouble(double value) {
	write(&value, sizeof(double));
	return 0;
}
int Stream::readBool(bool &value) {
	bool A;
	read(&A, sizeof(bool));
	value = A;
	return 0;
}
int Stream::writeBool(bool value) {
	bool A = value;
	write(&A, sizeof(bool));
	return 0;
}
int Stream::readString(String &value) {
	if (getSize() == 0)
	{
		value = "";
		return 0;
	}
	int size;
	readInt(size);
	value = "";
	for (int i = 0; i < size; i++)
	{
		char ch;
		read(&ch, 1);
		value += ch;
	}
	return size;
}
int Stream::writeString(String value) {
	int size = value.getLength();
	writeInt(size);
	for (int i = 0; i < size; i++)
	{
		char ch = value.toString8().c_str()[i];
		write(&ch, 1);
	}
	return 0;
}
int Stream::readReal(real &value) {
	long double A;
	read(&A, sizeof(long double));
	value = A;
	return 0;
}
int Stream::writeReal(real value) {
	real A = value;
	write(&A, sizeof(real));
	return 0;
}



//--------------------------------------------------------------------------------------------------
//----------          class Memory          --------------------------------------------------------
//--------------------------------------------------------------------------------------------------
Memory::Memory() {
	data = NULL;
	setPos(0);
	setSize(0);
}
Memory::~Memory() {
	/*
	if (data != NULL) {
		size = 0;
		free(data);
		data = NULL;
	}
	*/
}

int Memory::read(void *buffer, int count) {
	if (data == NULL) return 0;
	if (buffer == NULL) return 0;
	if (count <= 0) return 0;
	char *aData = (char*)data;
	aData += pos;
	memcpy(buffer, aData, count);
	pos += count;
	return count;
}
int Memory::write(void *buffer, int count) {
	if (data == NULL) return 0;
	if (count <= 0) return 0;
	setSize(size + count);
	char *aData = (char*)data;
	aData += pos;
	if (buffer == NULL) memset(aData, 0, count);
	else memcpy(aData, buffer, count);
	pos += count;
	return count;
}
void Memory::set(Stream *source) {
	set(source, source->getSize());
}
void Memory::set(Stream *source, int size) {
	setPos(0);
	write(((Memory*)source)->data, source->getSize());
}
void Memory::setSize(int value) {
	size = value;
	try {
		data = realloc(data, value);
	}
	catch(...) {
		printf("Memory: error realloc\n");
		data = NULL;
		size = 0;
	}

}



//--------------------------------------------------------------------------------------------------
//----------          class File          ----------------------------------------------------------
//--------------------------------------------------------------------------------------------------
File::File(String fileName, String mode) {
    this->fileName = fileName;
    this->mode = mode;
    open();
}
File::File(String fileName) {
    this->fileName = fileName;
    mode = "wb";
    if (!open()) {
		createNullFile(fileName);
		open();
    }
}
File::~File() {
	if (f != NULL)
		fclose(f);
}
bool File::isOpen() {
	if (f) return true;
	return false;
}
bool File::open() {
#ifdef OS_WINDOWS
	int pos = fileName.getPosBack("\\");
	if (pos < 0) pos = fileName.getPosBack("/");
	if (pos >= 0) {
		String dirName = fileName.subString(0, pos);
		string dirName8 = dirName.toString8();
		createDir(dirName);
	}
#endif
	string fn = fileName.toString8();
	string md = mode.toString8();
	f = fopen(fn.c_str(), md.c_str());
	if (f == NULL) return false;
	return true;
}
int File::getSize() {
#ifdef OS_WINDOWS
    big pos, size;
    fgetpos(f, &pos);
    fseek(f, 0, SEEK_END);
    fgetpos(f, &size);
    fseek(f, (int)pos, SEEK_SET);
    return (int)size;
#endif
#ifdef OS_LINUX
    big pos, size;
    pos = ftell(f);
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    fseek(f, (int)pos, SEEK_SET);
    return (int)size;
#endif
}

void File::setSize(int value) {
#ifdef OS_WINDOWS
	SetEndOfFile((HANDLE)f);
#endif
}

int File::getPos() {
#ifdef OS_WINDOWS
	big pos;
	fgetpos(f, &pos);
	return (int)pos;
#endif

#ifdef OS_LINUX
	big pos;
	pos = ftell(f);
	return (int)pos;
#endif
}

void File::setPos(int value) {
#ifdef OS_WINDOWS
	big pos = value;
	fsetpos(f, &pos);
#endif
#ifdef OS_LINUX
	fseek(f, value, SEEK_SET);
#endif
}

int File::read(void *buffer, int count) {
	return fread(buffer, count, 1, f);
}
int File::readLine(String &str) {
	str = "";
	char ch;
	while(1)
	{
		read(&ch, 1);
		//    if (ch == '\n' || ch == '\r') return str.getLength();
		if (ch == '\r') return str.getLength();
		if (ch != '\n') str = str + ch;
		if (eof())
		{
			return str.getLength();
		}
	}
}
int File::readAll(String &str) {
	setPos(0);
	int size = getSize();
	char *memblock = new char[size + 1];
	int result = fread(memblock, size, 1, f);
	memblock[size] = '\0';
	str = memblock;
	delete[] memblock;
	return result;
}
int File::seek(int offset, int origin) {
#ifdef OS_WINDOWS
	return _fseeki64(f, offset, origin);
#endif
#ifdef OS_LINUX
	return fseek(f, offset, origin);
#endif
}

int File::write(void *buffer, int count) {
	fwrite(buffer, count, 1, f);
	return 0;
}
int File::write(String str) {
	int len = str.getLength();
	return write((void*)str.toString8().c_str(), len);
}
bool File::eof() {
	int pos = getPos();
	int size = getSize();
	return pos >= size;
}
void File::save() {
	int pos = getPos();
	fclose(f);
	open();
	setPos(pos);
}

void File::createDir(String dirName) {
	String s = "";
	while (dirName.getLength() > 0)
	{
		int pos = dirName.getPos("\\");
		if (pos < 0) pos = dirName.getPos("/");
		if (pos < 0) break;
		s += dirName.subString(0, pos);
		string s8 = s.toString8();
		dirName = dirName.subString(pos + 1, dirName.getLength());
		String ss = s.subString(s.getLength() - 1, 1);
		s += "\\";
		if (ss == ":") continue;
#ifdef OS_WINDOWS
		CreateDirectory(s.toString8().c_str(), NULL);
#endif
#ifdef OS_LINUX

#endif
	}
}
void File::createNullFile(String fileName) {
//	HFILE f = _lcreat(fileName.toChars(), 0);
//	_lclose(f);
	FILE *ff;
	ff = fopen(fileName.toString8().c_str(), "w");
	fclose(ff);
}
String File::getExtention(String fileName) {
	int pos = fileName.getPos(".");
	if (pos == -1) return "";
	return fileName.subString(pos + 1, fileName.getLength());
}
FILE* File::getFILEPointer() {
	return f;
}

}
