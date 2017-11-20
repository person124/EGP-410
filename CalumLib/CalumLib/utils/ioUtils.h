#ifndef IO_UTILS_H
#define IO_UTILS_H

#include <string>

class Grid;

namespace IOUtils
{
	void loadGraphicsBuffers(const std::string& path);
	void loadAnimations(const std::string& path);
	void loadAudio(const std::string& path);

	void saveGrid(const std::string& path, Grid* grid);
	void loadGrid(const std::string& path, Grid*& grid);

	void getLevels(const std::string& dirPath, std::string*& levels, unsigned int& count);

	void errorFileReport(const std::string& name);
	void errorInitReport(const std::string& str);
}

#endif