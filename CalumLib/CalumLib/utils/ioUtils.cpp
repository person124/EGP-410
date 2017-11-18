#include "ioUtils.h"

#include "game.h"

#include "audio/audioSystem.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/graphicsBuffer.h"
#include "graphics/animation.h"
#include "graphics/animationManager.h"
#include "graphics/sprite.h"

#include "pathing/grid.h"

#include <iostream>
#include <fstream>

bool readFile(std::ifstream& file, const std::string& path)
{
	file = std::ifstream(path.c_str());
	return !file.fail();
}

bool writeFile(std::ofstream& file, const std::string& path)
{
	file = std::ofstream(path.c_str());
	return !file.fail();
}

void IOUtils::loadGraphicsBuffers(const std::string& path)
{
	std::ifstream file;
	if (!readFile(file, path))
	{
		errorFileReport(path);
		return;
	}

	std::string name, filePath, junk;
	GraphicsBuffer* buffer;
	std::getline(file, junk);
	while (!file.eof())
	{
		file >> name >> filePath;
		buffer = new GraphicsBuffer(filePath);
		Game::pInstance->getBufferManager()->add(name, buffer);
	}

	file.close();
}

void IOUtils::loadAnimations(const std::string& path)
{
	std::ifstream file;
	if (!readFile(file, path))
	{
		errorFileReport(path);
		return;
	}

	std::string name, bufferName, junk;
	double speed;
	int loop, width, height, xCount, yCount, xOffset, yOffset;
	Animation* ani;
	GraphicsBuffer* buffer;

	std::getline(file, junk);
	while (!file.eof())
	{
		file >> name >> bufferName >> speed >> loop >> width >> height >> xCount >> yCount >> xOffset >> yOffset;
		
		buffer = Game::pInstance->getBufferManager()->get(bufferName);
		
		std::vector<Sprite*> sprites = std::vector<Sprite*>();
		for (int y = 0; y < yCount; y++)
			for (int x = 0; x < xCount; x++)
				sprites.push_back(new Sprite(buffer, xOffset + (width * x), yOffset + (height * y), width, height));

		ani = new Animation(sprites, speed, loop);

		Game::pInstance->getAnimationManager()->add(name, ani);
	}

	file.close();
}

void IOUtils::loadAudio(const std::string& path)
{
	std::ifstream file;
	if (!readFile(file, path))
	{
		errorFileReport(path);
		return;
	}

	std::string name, filePath, junk;
	bool isStream;
	
	std::getline(file, junk);
	while (!file.eof())
	{
		file >> name >> isStream >> filePath;

		if (isStream)
			Game::pInstance->getAudio()->registerStream(name, filePath);
		else
			Game::pInstance->getAudio()->registerClip(name, filePath);
	}
	file.close();
}

void IOUtils::saveGrid(const std::string& path, Grid* grid)
{
	std::ofstream file;
	if (!writeFile(file, path))
	{
		errorFileReport(path);
		return;
	}

	file << grid->getWidth() << ' ' << grid->getHeight() << ' ';

	for (int i = 0; i < grid->getSize(); i++)
		file << grid->getID(i) << ' ';

	file.close();
}

void IOUtils::loadGrid(const std::string& path, Grid* grid)
{
	std::ifstream file;
	if (!readFile(file, path))
	{
		errorFileReport(path);
		return;
	}

	int width, height;
	file >> width >> height;

	if (grid != NULL)
		delete grid;
	grid = new Grid(width, height);

	int value;
	for (int i = 0; i < grid->getSize(); i++)
	{
		file >> value;
		grid->setID(i, value);
	}

	file.close();
}

void IOUtils::errorFileReport(const std::string& name)
{
	std::cout << "ERROR: Opening file: " << name << "!\n";
}

void IOUtils::errorInitReport(const std::string& str)
{
	std::cout << "ERROR: Failed to init " << str << "!\n";
}