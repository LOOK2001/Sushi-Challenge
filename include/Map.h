// Class that maintaining map data
#ifndef MAP_H
#define MAP_H

#include "GameObject.h"
#include "TileHandler.h"


class Map : public GameObject
{
public:
	Map(const char* mapFile = nullptr , const char* tilesFile = nullptr)
	{
		tileSheet = nullptr;

		LoadMap(mapFile);
		LoadTiles(tilesFile);
		scale_factor = 1;
	}
	~Map()
	{
		if (tileSheet)
			delete tileSheet;
	}

	virtual void init();
	virtual void render(SDL_Renderer* ren);

	void LoadMap(const char* file_name);
	void LoadTiles(const char* file_name, const int _rows = 1, const int _cols = 1);

	TileSheet* GetTileSheet() const { return tileSheet; }
	void SetScaleFactor(float _scale) { scale_factor = _scale; }
	float GetScaleFactor() const { return scale_factor; }

private:
	std::string map_file_name;
	std::string tiles_file_name;
	std::vector<std::vector<int>> map;
	TileSheet* tileSheet;
	float scale_factor;
};

#endif //MAP_H