
#include <fstream>
#include <sstream>
#include <utility>

#include "include/Map.h"
#include "include/Utils.h"


void Map::LoadMap(const char* _file_name)
{
	if (!_file_name)
		return;

	if (!tileSheet)
		std::cout << "Please load tile sheet first" << std::endl;

	map_file_name = _file_name;
	std::vector<std::vector<int>> _map;
	std::ifstream infile(_file_name);

	std::string line;
	int i, j;
	i = j = 0;
	int width = tileSheet->GetTileWidth() * scale_factor;
	int height = tileSheet->GetTileHeight() * scale_factor;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);

		std::string tile_index;
		std::vector<int> tile_line;
		bool isWall = false;
		i = 0;
		while (iss >> tile_index)
		{
			int index = std::stoi(tile_index);

			// If the index is wall, create a box collider
			if (index >=3 && index <= 10)
			{
				isWall = true;
				RectObject* wall = new RectObject(i * width, j * height, width, height);
				wall->init();
				wall->SetObjectType(ObjectType::WALL);
				AddInstance(wall);
			}
			else
			{
				isWall = false;
			}
			tile_line.push_back(index);
			i++;
		}
		_map.push_back(tile_line);
		j++;
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
