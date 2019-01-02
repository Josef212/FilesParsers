#ifndef __XML_FILE_H__
#define __XML_FILE_H__

#include "pugixml-1.9/src/pugixml.hpp"

class XmlFile
{
public:
	XmlFile(const char* rootName = "root_node");
	XmlFile(const char* buffer, unsigned int size, const char* rootName = "root_node");
	XmlFile(pugi::xml_node node);
	virtual ~XmlFile();

	// Setters

	void AddChild(const char* name, XmlFile& node);

	template<typename T>
	void AddAttribute(const char* name, T value)
	{
		m_root.append_attribute(name) = value;
	}

	template<typename T>
	void AddAttribute(const char* name, T& value)
	{
		m_root.append_attribute(name) = value;
	}

	// ------------------------------------------------

	// Getters

	//XmlFile GetChild(const char* childName);
	pugi::xml_node GetPugiChild(const char* childName);

	bool GetBool(const char* name, bool def);
	int GetInt(const char* name, int def);
	unsigned int GetUInt(const char* name, unsigned int def);
	float GetFloat(const char* name, float def);
	double GetDouble(const char* name, double def);

	const char* GetStringCStr(const char* name, const char* def);
	std::string GetString(const char* name, std::string& def);

	long GetLong(const char* name, long def);
	long long GetLongLong(const char* name, long long def);
	unsigned long long GetULongLong(const char* name, unsigned long long def);

	// ------------------------------------------------

	// Let get the pugi nodes since it gives facilities to iterate, etc.
	pugi::xml_node GetPugiNode()const { return m_root; }

	// Write
	std::string Write();

private:
	pugi::xml_document m_document;
	pugi::xml_node m_root;

	const char* m_rootName = "";
};

#endif // !__XML_FILE_H__