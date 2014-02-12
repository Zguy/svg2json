#ifndef JSONPath_h__
#define JSONPath_h__

#include "Vector.h"

#include <string>

namespace JSONPath
{
	bool writeFile(const std::string &filename, const VectorList &path);
}

#endif // JSONPath_h__
