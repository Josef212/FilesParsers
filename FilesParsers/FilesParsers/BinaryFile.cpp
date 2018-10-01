#include "BinaryFile.h"
#include <cstring>
#include <cassert>


BinaryFile::BinaryFile()
{
	bufferSize = REALLOC_SIZE;
	buffer = new char[bufferSize];
}

BinaryFile::BinaryFile(char* data, uint size) : buffer(data), bufferSize(size)
{}

BinaryFile::~BinaryFile()
{
	if (buffer) delete[] buffer;
}

// -------------------------------------------------------------

void BinaryFile::AddData(const void* data, uint dataSize)
{
	if (bufferSize < head + dataSize) ReallocBuffer(bufferSize + REALLOC_SIZE);

	memcpy(buffer + head, data, dataSize);
	head += dataSize;
}

// -------------------------------------------------------------

void BinaryFile::AddInt(int value)
{
	AddData(&value, sizeof(int));
}

void BinaryFile::AddUInt(uint value)
{
	AddData(&value, sizeof(uint));
}

void BinaryFile::AddFloat(float value)
{
	AddData(&value, sizeof(float));
}

void BinaryFile::AddLong(long value)
{
	AddData(&value, sizeof(long));
}

void BinaryFile::AddULong(ulong value)
{
	AddData(&value, sizeof(ulong));
}

void BinaryFile::AddInt64(int64 value)
{
	AddData(&value, sizeof(int64));
}

void BinaryFile::AddUInt64(uint64 value)
{
	AddData(&value, sizeof(uint64));
}

void BinaryFile::AddDouble(double value)
{
	AddData(&value, sizeof(double));
}

void BinaryFile::AddBool(bool value)
{
	AddData(&value, sizeof(bool));
}

void BinaryFile::AddChar(char value)
{
	AddData(&value, sizeof(char));
}

void BinaryFile::AddString(std::string value)
{
	AddData(value.c_str(), value.size() * sizeof(char));
}

// -------------------------------------------------------------

void BinaryFile::GetData(void* data, uint size)
{
	assert(head + size < bufferSize);

	memcpy(data, buffer + head, size);
	head += size;
}

// -------------------------------------------------------------

void BinaryFile::GetInt(int& value)
{
	GetData(&value, sizeof(int));
}

void BinaryFile::GetUInt(uint value)
{
	GetData(&value, sizeof(uint));
}

void BinaryFile::GetFloat(float& value)
{
	GetData(&value, sizeof(float));
}

void BinaryFile::GetLong(long& value)
{
	GetData(&value, sizeof(long));
}

void BinaryFile::GetULong(ulong value)
{
	GetData(&value, sizeof(ulong));
}

void BinaryFile::GetInt64(int64 value)
{
	GetData(&value, sizeof(int64));
}

void BinaryFile::GetUInt64(uint64 value)
{
	GetData(&value, sizeof(uint64));
}

void BinaryFile::GetDouble(double& value)
{
	GetData(&value, sizeof(double));
}

void BinaryFile::GetBool(bool& value)
{
	GetData(&value, sizeof(bool));
}

void BinaryFile::GetChar(char& value)
{
	GetData(&value, sizeof(char));
}

void BinaryFile::GetString(std::string& value, uint length)
{
	char* tmp = new char[length];
	GetData(tmp, length * sizeof(char));
	value = tmp;
	value[length] = '\0';
	delete[] tmp;
}

// -------------------------------------------------------------

void BinaryFile::ReallocBuffer(uint newSize)
{
	char* tmp = new char[newSize];
	memcpy(tmp, buffer, bufferSize);
	bufferSize = newSize;
	delete[] buffer;
	buffer = tmp;
}
