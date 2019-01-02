#include "XmlFile.h"

#include <assert.h>
#include <iostream>


XmlFile::XmlFile(const char* rootName) : m_rootName(rootName)
{
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

XmlFile::XmlFile(pugi::xml_node node) : m_root(node), m_rootName(m_root.name())
{
	m_root = node;
	m_rootName = m_root.name;
}

XmlFile::~XmlFile()
{
	m_document.reset();
}

 // =======================================================================

XmlFile XmlFile::GetChild(const char * childName)
{
	return XmlFile(m_root.child(childName));
}
