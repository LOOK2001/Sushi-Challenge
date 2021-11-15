
#ifndef TILEHANDLER_H
#define TILEHANDLER_H

#include <iostream>
#include <vector>
#include <string>
#include <utility>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "Image.h"
#include "Global.h"


class TileSheet
{
public:
	TileSheet(const char* tile_name = nullptr, const int _rows = 1, const int _cols = 1) :
		columns(_cols), rows(_rows)
	{
		if (tile_name)
			LoadTileSet(tile_name, rows, columns);
	}
	~TileSheet()
	{
		if (tileSet)
			delete tileSet;

		for (auto img : tiles)
			delete img;
	}

	Image* GetTile(int index) const
	{
		return tiles[index];
	}

	void LoadTileSet(const char* tile_name, const int _rows, const int _cols);

	void SetRow(int _rows) { rows = _rows; }
	void SetCol(int _cols) { columns = _cols; }
	int GetTileWidth() const { return tile_width; }
	int GetTileHeight() const { return tile_height; }

private:
	int columns;
	int rows;
	int tile_width;
	int tile_height;
	std::vector<Image*> tiles;
	SDL_FRect rect;
	Image* tileSet;
};

#endif // TILEHANDLER_H
