#include "SVGPath.h"
#include "SVGParser.h"

#include <pugixml.hpp>

#include <boost/lexical_cast.hpp>

#include <fstream>
#include <iostream>

namespace
{
	Vector parseTranslate(const pugi::xml_node &g_node)
	{
		Vector translate;
		std::string transformAttribute = g_node.attribute("transform").as_string("translate(0,0)");
		std::string::size_type beg = transformAttribute.find("translate(") + 10;
		std::string::size_type end = transformAttribute.find(")", beg);
		transformAttribute = transformAttribute.substr(beg, end - beg);

		std::string::size_type comma = transformAttribute.find(",");
		translate.x = boost::lexical_cast<float>(transformAttribute.substr(0, comma));
		translate.y = boost::lexical_cast<float>(transformAttribute.substr(comma + 1));
		return translate;
	}

	VectorList parsePath(const pugi::xml_node &path_node, const Vector &translate, int flags)
	{
		VectorList result;
		std::string pathString = path_node.attribute("d").as_string();
		std::istringstream pathStream(pathString);

		SVGParser::SVGPath svgPath = SVGParser::parsePath(pathStream);

		for (SVGParser::SVGCommand *cmd : svgPath)
		{
			switch (cmd->getType())
			{
			case SVGParser::SVG_MOVE_TO_ABS:
			case SVGParser::SVG_LINE_TO_ABS:
				{
					float x = (cmd->x + translate.x);
					float y = (cmd->y + translate.y);

					if (flags & SVGPath::ROUND)
					{
						x = std::floor(x + 0.5f);
						y = std::floor(y + 0.5f);
					}

					result.emplace_back(x,y);
					break;
				}
			case SVGParser::SVG_CLOSE_PATH:
				break; // Do nothing
			default:
				std::cerr << "Unhandled svg command" << std::endl;
				break;
			}
		}

		return result;
	}
}

SVGPath::SVGPath(int flags) : flags(flags)
{
}
SVGPath::~SVGPath()
{
	close();
}

bool SVGPath::openFile(const std::string &filename)
{
	std::fstream file(filename, std::ios::in);
	if (!file.is_open())
	{
		std::cerr << "Could not open file" << std::endl;
		return false;
	}

	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load(file);
	if (result.status != pugi::status_ok)
	{
		std::cerr << "Parse error: " << result.description() << std::endl;
		return false;
	}

	pugi::xml_node g_node = doc.select_single_node("/svg/g").node();
	pugi::xml_node path_node = g_node.child("path");

	Vector translate = parseTranslate(g_node);
	path = parsePath(path_node, translate, flags);

	return true;
}
void SVGPath::close()
{
	path.clear();
}
