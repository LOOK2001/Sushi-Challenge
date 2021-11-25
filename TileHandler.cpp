
#include "include/TileHandler.h"
#include "include/Global.h"

void TileSheet::LoadTileSet(const char* tile_name, const int _rows, const int _cols)
{
	if (tileSet)
		delete tileSet;

	tileSet = new Image(tile_name);
	
	rows = _rows;
	columns = _cols;

	int total_tiles = rows * columns;
	int x = 0, y = 0;

	int tileSet_width = tileSet->GetImgWidth();
	int tileSet_height = tileSet->GetImagHeight();

	tile_width = tileSet_height / rows;
	tile_height = tileSet_width / columns;

	tiles.resize(0);

	for (int i = 0; i < total_tiles; i++)
	{
		Image* tile = new Image(tileSet->GetSurface(), x, y, tile_width, tile_height);
		tiles.push_back(tile);

		// Move to next tile spot
		x += tile_width;

		if (x >= tileSet_width)
		{
			// Move back
			x = 0;

			// Move to the next row
			y += tile_height;
		}
	}
}

