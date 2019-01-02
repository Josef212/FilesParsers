#include "XmlFile.h"

#include <assert.h>
#include <iostream>
#include <sstream> 


XmlFile::XmlFile(const char* rootName) : m_rootName(rootName)
{
	m_root = m_document.append_child(rootName);
}

XmlFile::XmlFile(const char * buffer, unsigned int size, const char* rootName) : m_rootName(rootName)
{
	assert(buffer && size > 0);

	auto result = m_document.load_buffer(buffer, size);

	if (result == NULL)
	{
		std::cout << "ERROR parsing data: " << result.description() << std::endl;
		return;
	}

	m_root = m_document.child(rootName);
}

XmlFile::XmlFile(pugi::xml_node node) : m_root(node), m_rootName(node.name())
{
}

XmlFile::~XmlFile()
{
	m_document.reset();
}

void XmlFile::AddChild(const char * name, XmlFile & node)
{
	m_root.append_child(name) = node.m_root;
}

 // =======================================================================

// TODO: Why the f*** this does not work
//XmlFile XmlFile::GetChild(const char * childName)
//{
//	return XmlFile(m_root.child(childName));
//}

pugi::xml_node XmlFile::GetPugiChild(const char * childName)
{
	return m_root.child(childName);
}

// --------------------

bool XmlFile::GetBool(const char * name, bool def)
{
	return m_root.attribute(name).as_bool(def);
}

int XmlFile::GetInt(const char * name, int def)
{
	return m_root.attribute(name).as_int(def);
}

unsigned int XmlFile::GetUInt(const char * name, unsigned int def)
{
	return m_root.attribute(name).as_uint(def);
}

float XmlFile::GetFloat(const char * name, float def)
{
	return m_root.attribute(name).as_float(def);
}

double XmlFile::GetDouble(const char * name, double def)
{
	return m_root.attribute(name).as_double(def);
}

const char * XmlFile::GetStringCStr(const char * name, const char * def)
{
	return m_root.attribute(name).as_string(def);
}

std::string XmlFile::GetString(const char * name, std::string & def)
{
	return std::string(m_root.attribute(name).as_string(def.c_str()));
}

long XmlFile::GetLong(const char * name, long def)
{
	return (long)m_root.attribute(name).as_llong(def);
}

long long XmlFile::GetLongLong(const char * name, long long def)
{
	return m_root.attribute(name).as_llong(def);
}

unsigned long long XmlFile::GetULongLong(const char * name, unsigned long long def)
{
	return m_root.attribute(name).as_ullong(def);
}

std::string XmlFile::Write()
{
	std::stringstream stream;
	m_document.save(stream);

	return stream.str();
}
