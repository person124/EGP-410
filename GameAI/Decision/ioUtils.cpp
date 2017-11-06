#include "ioUtils.h"
#include "game.h"

#include "graphics/graphicsSystem.h"
#include "graphics/graphicsBufferManager.h"
#include "graphics/graphicsBuffer.h"
#include "graphics/animation.h"
#include "graphics/animationManager.h"

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
		errorReport(path);
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
		errorReport(path);
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
		
		std::vector<Sprite>* sprites = new std::vector<Sprite>();
		for (int y = 0; y < yCount; y++)
			for (int x = 0; x < xCount; x++)
				sprites->push_back(Sprite(buffer, xOffset + (width * x), yOffset + (height * y), width, height));

		ani = new Animation(sprites, speed, loop);

		Game::pInstance->getAnimationManager()->add(name, ani);
	}

	file.close();
}

void IOUtils::saveGrid(const std::string& path, Grid* grid)
{
	std::ofstream file;
	if (!writeFile(file, path))
	{
		errorReport(path);
		return;
	}

	for (int i = 0; i < grid->getSize(); i++)
		file << grid->isSolid(i) << ' ';

	file.close();
}

void IOUtils::loadGrid(const std::string& path, Grid* grid)
{
	std::ifstream file;
	if (!readFile(file, path))
	{
		errorReport(path);
		return;
	}

	bool value;
	for (int i = 0; i < grid->getSize(); i++)
	{
		file >> value;
		grid->setSolid(i, value);
	}

	file.close();
}

void IOUtils::errorReport(const std::string& name)
{
	std::cout << "Error opening file: " << name << "!\n";
}