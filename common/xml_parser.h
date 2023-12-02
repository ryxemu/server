#ifndef XMLParser_H
#define XMLParser_H

#include "global_define.h"
#include "tinyxml/tinyxml.h"
#include "../common/types.h"

#include <string>
#include <map>

/*
 * See note in XMLParser::ParseFile() before inheriting this class.
 */
class XMLParser {
   public:
	typedef void (XMLParser::*ElementHandler)(TiXmlElement *ele);

	XMLParser();
	virtual ~XMLParser() {}

	bool ParseFile(const char *file, const char *root_ele);
	bool ParseStatus() const { return ParseOkay; }

   protected:
	const char *ParseTextBlock(TiXmlNode *within, const char *name, bool optional = false);
	const char *GetText(TiXmlNode *within, bool optional = false);

	std::map<std::string, ElementHandler> Handlers;

	bool ParseOkay;
};

#endif
