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

	// ------------------------------------------------

	// Getters

	XmlFile GetChild(const char* childName);

	// ------------------------------------------------

private:
	pugi::xml_document m_document;
	pugi::xml_node m_root;

	const char* m_rootName = "";
};

#endif // !__XML_FILE_H__