#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <string>

class Grid;

namespace IOUtils
{
	void loadGraphicsBuffers(const std::string& path);
	void loadAnimations(const std::string& path);

	void saveGrid(const std::string& path, Grid* grid);
	Grid* loadGrid(const std::string& path);

	void errorReport(const std::string& name);
}

#endif