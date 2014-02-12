#include "JSONPath.h"

#include <fstream>
#include <iostream>

namespace JSONPath
{
	bool writeFile(const std::string &filename, const VectorList &path)
	{
    std::fstream file(filename, std::ios::out | std::ios::trunc);
    if (!file.is_open())
		{
			std::cerr << "Failed to open output file" << std::endl;
			return false;
		}

		file << "[\n";

		for (const Vector &vector : path)
		{
			file << "\t{ \"x\": " << vector.x << ", \"y\": " << vector.y << " }";
			if (&vector != &path.back())
				file << ",";
			file << '\n';
		}

		file << "]" << std::flush;

		return true;
	}
}
