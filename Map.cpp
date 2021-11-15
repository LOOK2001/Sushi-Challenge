
#include <fstream>
#include <sstream>

#include "include/Map.h"


void Map::LoadMap(const char* _file_name)
{
	if (!_file_name)
		return;

	map_file_name = _file_name;
	std::vector<std::vector<int>> _map;
	std::ifstream infile(_file_name);

	std::string line;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		std::string tile_index;
		std::vector<int> tile_line;
		while (iss >> tile_index)
		{
			int index = std::stoi(tile_index);
			tile_line.push_back(index);
		}
		_map.push_back(tile_line);
	}

	if (!_map.empty())
		map = _map;
}

void Map::LoadTiles(const char* _file_name, const int _rows, const int _cols)
{
	if (!_file_name)
		return;

	tiles_file_name = _file_name;

	if (tileSheet)
		delete tileSheet;

	tileSheet = new TileSheet(tiles_file_name.c_str(), _rows, _cols);
}

void Map::init()
{
	collidable = false;
}

void Map::render(SDL_Renderer* ren)
{
	for (unsigned int i = 0; i < map.size(); i++)
	{
		for (unsigned int j = 0; j < map[i].size(); j++)
		{
			int idx = map[i][j];
			Image* tile = tileSheet->GetTile(idx);
			int width, height;
			tile->SetViewSize(width, height);
			tile->Draw(width * j * scale_factor, height * i * scale_factor, scale_factor);
		}
	}
}
