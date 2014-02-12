#ifndef SVGPath_h__
#define SVGPath_h__

#include "Vector.h"

#include <string>

class SVGPath
{
public:
	enum Flag
	{
		ROUND = 1
	};

	SVGPath(int flags = 0);
	~SVGPath();

	void setFlags(int flags) { this->flags = flags; }

	bool openFile(const std::string &filename);
	void close();

	VectorList getPath() const { return path; }

private:
	VectorList path;
	int flags;
};

#endif // SVGPath_h__
