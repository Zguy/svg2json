#include "SVGPath.h"
#include "JSONPath.h"

#include <boost/program_options.hpp>

#include <iostream>
#include <string>

namespace po = boost::program_options;

void show_help(const po::options_description &visible)
{
	std::cout
		<< "Usage: svg2json [options] input.svg\n"
		<< visible
		<< std::endl;
}

int main(int argc, char *argv[])
{
	std::string input;
	std::string output;

	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "show help message")
		("output,o", po::value<std::string>(&output)->default_value(std::string()), "set output file")
		("round", "round coordinates")
	;

	po::options_description hidden("Hidden options");
	hidden.add_options()
		("input,i", po::value<std::string>(&input), "set input file")
	;

	po::options_description options;
	options.add(desc).add(hidden);

	po::positional_options_description pos;
	pos.add("input", -1);

	po::variables_map vm;
	po::store(po::command_line_parser(argc, argv).options(options).positional(pos).run(), vm);
	po::notify(vm);

	if (vm.count("help"))
	{
		show_help(desc);
		return 1;
	}

	if (input.empty())
	{
		show_help(desc);
		return 1;
	}

	if (output.empty())
	{
		output = input.substr(0, input.find_last_of('.')) + ".json";
	}

	int flags = 0;
	if (vm.count("round"))
		flags |= SVGPath::ROUND;

	SVGPath svg(flags);
	if (!svg.openFile(input))
	{
		return 1;
	}

	VectorList path = svg.getPath();
	if (!JSONPath::writeFile(output, path))
	{
		return 1;
	}

	return 0;
}
