#ifndef __BINARYFILE_H__
#define __BINARYFILE_H__

#include <string>

#define REALLOC_SIZE 512

class BinaryFile
{
	typedef unsigned int uint;
	typedef long long int64;
	typedef unsigned long ulong;
	typedef unsigned long long uint64;

public:
	BinaryFile();
	BinaryFile(char* data, uint size);
	virtual ~BinaryFile();

	// ----------------

	void AddData(const void* data, uint dataSize);

	void AddInt(int value);
	void AddUInt(uint value);
	void AddFloat(float value);
	void AddLong(long value);
	void AddULong(ulong value);
	void AddInt64(int64 value);
	void AddUInt64(uint64 value);
	void AddDouble(double value);
	void AddBool(bool value);
	void AddChar(char value);
	void AddString(std::string value);

	// ----------------

	void GetData(void* data, uint size);

	void GetInt(int& value);
	void GetUInt(uint value);
	void GetFloat(float& value);
	void GetLong(long& value);
	void GetULong(ulong value);
	void GetInt64(int64 value);
	void GetUInt64(uint64 value);
	void GetDouble(double& value);
	void GetBool(bool& value);
	void GetChar(char& value);
	void GetString(std::string& value, uint length);

	// ----------------

	char* Data()const { return buffer; }
	uint DataSize()const { return bufferSize; }


private:
	void ReallocBuffer(uint newSize);

private:
	char* buffer = nullptr;
	uint bufferSize = 0;
	uint head = 0;
};

#endif