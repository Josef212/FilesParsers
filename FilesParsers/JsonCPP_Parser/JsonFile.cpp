#include "JsonFile.h"



JsonFile::JsonFile()
{}

JsonFile::JsonFile(const char * buffer)
{
	Json::Reader r;
	r.parse(buffer, objRoot);
}

JsonFile::JsonFile(Json::Value& section) : objRoot(section)
{}


JsonFile::~JsonFile()
{
}

// -----------------------------------------------------

int JsonFile::GetArraySize(const char* name)
{
	Json::Value val = objRoot[name];
	return val.isArray() ? val.size() : -1;
}

// -----------------------------------------------------

JsonFile JsonFile::GetSection(const char * sectionName)
{
	return JsonFile(objRoot[sectionName]);
}


int JsonFile::GetInt(const char * name, int def, int index)
{
	Json::Value val = objRoot[name];
	return val.isInt() ? 
		val.asInt() : 
		(val.isArray() && index >= 0 && index < val.size()) ? val[index].asInt() : def;
}

unsigned int JsonFile::GetUInt(const char * name, unsigned int def, int index)
{
	Json::Value val = objRoot[name];
	return val.isUInt() ?
		val.asUInt() :
		(val.isArray() && index >= 0 && index < val.size()) ? val[index].asUInt() : def;
}

int64 JsonFile::GetInt64(const char * name, int64 def, int index)
{
	Json::Value val = objRoot[name];
	return val.isInt64() ?
		val.asInt64() :
		(val.isArray() && index >= 0 && index < val.size()) ? val[index].asInt64() : def;
}

uint64 JsonFile::GetUInt64(const char * name, uint64 def, int index)
{
	Json::Value val = objRoot[name];
	return val.isUInt64() ?
		val.asUInt64() :
		(val.isArray() && index >= 0 && index < val.size()) ? val[index].asUInt64() : def;
}

float JsonFile::GetFloat(const char* name, float def, int index)
{
	Json::Value val = objRoot[name];
	return val.isNumeric() ?
		val.asFloat() :
		(val.isArray() && index >= 0 && index < val.size()) ? val[index].asFloat() : def;
}

double JsonFile::GetDouble(const char* name, double def, int index)
{
	Json::Value val = objRoot[name];
	return val.isDouble() ?
		val.asDouble() :
		(val.isArray() && index >= 0 && index < val.size()) ? val[index].asDouble() : def;
}

bool JsonFile::GetBool(const char* name, bool def, int index)
{
	Json::Value val = objRoot[name];
	return val.isBool() ?
		val.asBool() :
		(val.isArray() && index >= 0 && index < val.size()) ? val[index].asBool() : def;
}

std::string JsonFile::GetString(const char* name, std::string def, int index)
{
	Json::Value val = objRoot[name];
	return val.isString() ?
		val.asString() :
		(val.isArray() && index >= 0 && index < val.size()) ? val[index].asString() : def;
}


JsonFile JsonFile::GetObjectFromArray(const char* name, unsigned int index)
{
	Json::Value val = objRoot[name];
	return val.isObject() ? JsonFile(val) : JsonFile();
}

// ======

void JsonFile::AddSection(const char* name, JsonFile& section)
{
	objRoot[name] = section.Value();
}


void JsonFile::AddInt(const char* name, int value)
{
	objRoot[name] = value;
}

void JsonFile::AddIntArray(const char* name, int* data, unsigned size)
{
	for (unsigned int i = 0; i < size; ++i) objRoot[name][i] = data[i];
}

void JsonFile::AddUInt(const char* name, unsigned value)
{
	objRoot[name] = value;
}

void JsonFile::AddUIntArray(const char* name, unsigned* data, unsigned size)
{
	for (unsigned int i = 0; i < size; ++i) objRoot[name][i] = data[i];
}

void JsonFile::AddInt64(const char* name, int64 value)
{
	objRoot[name] = value;
}

void JsonFile::AddInt64Array(const char* name, int64* data, unsigned size)
{
	for (unsigned int i = 0; i < size; ++i) objRoot[name][i] = data[i];
}

void JsonFile::AddUInt64(const char* name, uint64 value)
{
	objRoot[name] = value;
}

void JsonFile::AddUIntArray(const char* name, uint64* data, unsigned size)
{
	for (unsigned int i = 0; i < size; ++i) objRoot[name][i] = data[i];
}

void JsonFile::AddFloat(const char* name, float value)
{
	objRoot[name] = value;
}

void JsonFile::AddFloatArray(const char* name, float* data, unsigned size)
{
	for (unsigned int i = 0; i < size; ++i) objRoot[name][i] = data[i];
}

void JsonFile::AddDouble(const char* name, double value)
{
	objRoot[name] = value;
}

void JsonFile::AddDoubleArray(const char* name, double* data, unsigned size)
{
	for (unsigned int i = 0; i < size; ++i) objRoot[name][i] = data[i];
}

void JsonFile::AddBool(const char* name, bool value)
{
	objRoot[name] = value;
}

void JsonFile::AddBoolArray(const char* name, bool* data, unsigned size)
{
	for (unsigned int i = 0; i < size; ++i) objRoot[name][i] = data[i];
}

void JsonFile::AddString(const char* name, const char* value)
{
	objRoot[name] = value;
}

void JsonFile::AddCStringArray(const char* name, const char** data, unsigned size)
{
	for (unsigned int i = 0; i < size; ++i) objRoot[name][i] = data[i];
}

void JsonFile::AddString(const char* name, std::string value)
{
	objRoot[name] = value;
}

void JsonFile::AddStringArray(const char* name, std::string* data, unsigned size)
{
	for (unsigned int i = 0; i < size; ++i) objRoot[name][i] = data[i];
}


void JsonFile::AddValue(const char* name, Json::Value value)
{
	objRoot[name] = value;
}

void JsonFile::AddArrayValue(const char* name, Json::Value value, unsigned int index)
{
	objRoot[name][index] = value;
}

void JsonFile::AddEmptyArray(const char* name)
{

}

void JsonFile::AppendArrayValue(const char* name, Json::Value value)
{
	objRoot[name].append(value);
}

// -----------------------------------------------------

std::string JsonFile::Write(bool styled)
{
	
	std::string ret;
	styled ? WriteStyled(ret) : WriteFast(ret);
	return ret;
}

void JsonFile::WriteFast(std::string& val)const
{
	Json::FastWriter fw;
	val = fw.write(objRoot);
}

void JsonFile::WriteStyled(std::string& val)const
{
	Json::StyledWriter sw;
	val = sw.write(objRoot);
}

// -----------------------------------------------------
