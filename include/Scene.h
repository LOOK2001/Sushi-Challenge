// Class that contains every GameObject in the scene
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <algorithm>
#include <random>

#include "Player.h"
#include "Sprite.h"
#include "Map.h"
#include "Camera.h"
#include "Pickup.h"
#include "ParticleEmitter.h"
#include "Enemy.h"
#include "Application.h"


class Global;
class Application;
// Scene Declaration:
// Base class for Scene. Scene class manage every gameObjects in the scene
class Scene
{
public:
	Scene(Application* _app)
	{
		app = _app;
	}

	virtual ~Scene()
	{
		for (size_t i = 0; i < objects_list.size(); i++) {
			if (objects_list[i])
				delete objects_list[i];
		}
	}
	virtual void init() {
		for (size_t i = 0; i < objects_list.size(); i++) {
			objects_list[i]->init();
		}
	}

	virtual void handle_events(SDL_Event& ev){
		for (size_t i = 0; i < objects_list.size(); i++){
			objects_list[i]->handle_events(ev);
		}
	}

	virtual void update(){
		for (size_t i = 0; i < objects_list.size(); i++){
			objects_list[i]->update();
		}
	}

	virtual void lateUpdate() {
		for (size_t i = 0; i < objects_list.size(); i++) {
			objects_list[i]->lateUpdate();
		}
	}

	virtual void render(SDL_Renderer* ren){
		for (size_t i = 0; i < objects_list.size(); i++) {
			objects_list[i]->render(ren);
		}
	}

	virtual void quit(){
		for (size_t i = 0; i < objects_list.size(); i++) {
			objects_list[i]->quit();
		}
	}

	virtual void SwitchLevel(const int& _level) {}

	virtual void AddGameObject(GameObject* _obj) { objects_list.push_back(_obj); }
	virtual void RemoveGameObject(GameObject * _obj) { objects_list.erase(std::remove(objects_list.begin(), objects_list.end(), _obj), objects_list.end()); }

	virtual void GameEnd() {}

protected:
	std::vector<GameObject*> objects_list;
	Application* app;
};


class Application;
// SceneHw3 Declaration:
class ExampleScene : public Scene
{
public:
	ExampleScene(Application* app) : Scene(app)
	{}

	virtual void init()
	{
		objects_list.reserve(1000);

		use_sphere_collider = false;

		float right = (float)Global::GetWindowWidth();
		float bottom = (float)Global::GetWindowHeight();

		// Create gameObjects for homework3
		camera = new Camera(0.0f, 0.0f, right, bottom);
		camera->init();
		camera->SetTargetOffset({ 100.0f, 100.0f });
		Global::GetInstance()->SetMainCamera(camera);
		objects_list.push_back(camera);

		// The background map
		map = new Map();
		// Scale map up
		map->SetScaleFactor(1);
		// Load tile set of map
		map->LoadTiles("./images/tileSet5.png", 4, 8);
		// Map data stores index of tiles
		map->LoadMap("./include/map.txt");
		map->init();
		objects_list.push_back(map);
		Global::SetActiveMap(map);

		// Viewport offset for camera
		int offset = (map->GetTileWidth() > map->GetTileHeight()) ? map->GetTileWidth() : map->GetTileHeight();
		camera->SetViewOffset((float)offset * 2);

		// Create sprite animation for states of character
		SpriteObject* walk_state = new SpriteObject(6, 100, "./images/sushi_chef_walk_spritesheet.png");
		SpriteObject* idle_state = new SpriteObject(4, 100, "./images/sushi_chef_idle_spritesheet.png");
		//idle_state->ScaleInPlace(2);

		// Player
		player = new Player(120.0f, 150.0f);
		player->SetDefaultState("idle");
		player->AddState(walk_state, "walk");
		player->AddState(idle_state, "idle");
		float view_width = (float)walk_state->GetViewWidth();
		float view_height = (float)walk_state->GetViewHeight();
		player->init();
		player->SetBoxCollider(30, 50, 30, 30);
		player->SetCircleColliderCenter(view_width / 2, view_height / 2);
		player->SetCirlceColliderRadius(view_width / 2);
		Global::SetMainPlayer(player);
		camera->SetTarget(player);
		objects_list.push_back(player);

		// Pickup gun
		Pickup* gun = new Pickup(250.0f, 200.0f, "./images/gun2.png");
		gun->init();
		gun->SetObjectType(ObjectType::GUN);
		objects_list.push_back(gun);

		// Enemy
		float w = (float)map->GetTileWidth();
		float h = (float)map->GetTileHeight();

		// Enemies for level 1
		for (auto i = 0; i < 10; i++)
		{
			SpriteObject* default_state = new SpriteObject(1, 100, "./images/carrot.png");
			SpriteObject* hurt_state = new SpriteObject(1, 100, "./images/carrot_hurt.png");
			Enemy* enemy = new Enemy(400, 400);
			enemy->AddState(default_state, "idle");
			enemy->AddState(hurt_state, "hurt");
			enemy->SetDefaultState("idle");
			enemy->init();
			enemy_list.push_back(enemy);
			objects_list.push_back(enemy);
		}

		// Enemies for level 2
		for (auto i = 0; i < 15; i++)
		{
			SpriteObject* default_state = new SpriteObject(1, 100, "./images/rice.png");
			SpriteObject* hurt_state = new SpriteObject(1, 100, "./images/rice_hurt.png");
			Enemy* enemy = new Enemy(w * 24, h * 6);
			enemy->AddState(default_state, "idle");
			enemy->AddState(hurt_state, "hurt");
			enemy->SetDefaultState("idle");
			enemy->init();
			enemy_list.push_back(enemy);
			objects_list.push_back(enemy);
		}

		// Enemies for level 3
		for (auto i = 0; i < 3; i++)
		{
			SpriteObject* default_state = new SpriteObject(1, 100, "./images/carrot.png");
			SpriteObject* hurt_state = new SpriteObject(1, 100, "./images/carrot_hurt.png");
			Enemy* enemy = new Enemy(1600, 1600);
			enemy->AddState(default_state, "idle");
			enemy->AddState(hurt_state, "hurt");
			enemy->SetDefaultState("idle");
			enemy->init();
			enemy_list.push_back(enemy);
			objects_list.push_back(enemy);
		}

		// Enemies for level 3
		for (auto i = 0; i < 3; i++)
		{
			SpriteObject* default_state = new SpriteObject(1, 100, "./images/rice.png");
			SpriteObject* hurt_state = new SpriteObject(1, 100, "./images/rice_hurt.png");
			Enemy* enemy = new Enemy(1600, 1600);
			enemy->AddState(default_state, "idle");
			enemy->AddState(hurt_state, "hurt");
			enemy->SetDefaultState("idle");
			enemy->init();
			enemy_list.push_back(enemy);
			objects_list.push_back(enemy);
		}

		// Sushi boss
		SpriteObject* default_state = new SpriteObject(1, 100, "./images/sushi.png");
		SpriteObject* hurt_state = new SpriteObject(1, 100, "./images/sushi_hurt.png");
		boss = new SushiBoss(1600, 1600);
		boss->AddState(default_state, "idle");
		boss->AddState(hurt_state, "hurt");
		boss->SetDefaultState("idle");
		boss->init();
		objects_list.push_back(boss);

		// Collision trigger for level 1
		SDL_FRect area{ 0.0f, 320.0f, 765.0f, 320.0f };
		RectObject* level_1_area = new RectObject(area.x, area.y, area.w, area.h);
		level_1_area->init();
		level_1_area->SetObjectType(ObjectType::LEVEL1);
		objects_list.push_back(level_1_area);
		camera->InsertLevelArea(1, area);
		area = { 1216.0f, 0.0f, 576.0f, 640.0f };
		// Collision trigger for level 2
		RectObject* level_2_area = new RectObject(area.x, area.y, area.w, area.h);
		level_2_area->init();
		level_2_area->SetObjectType(ObjectType::LEVEL2);
		objects_list.push_back(level_2_area);
		camera->InsertLevelArea(2, area);
		area = { w * 21, h * 20, w * 11, h * 12 };
		// Collision trigger for level 3
		RectObject* level_3_area = new RectObject(area.x, area.y, area.w, area.h);
		level_3_area->init();
		level_3_area->SetObjectType(ObjectType::LEVEL3);
		objects_list.push_back(level_3_area);
		// Collision trigger for level 0
		camera->InsertLevelArea(3, area);
		area = { 0.0f, 0.0f, w * 6, h * 5 };
		camera->InsertLevelArea(0, area);
		area = { w * 11, h * 6, w * 8, h * 5 };
		camera->InsertLevelArea(0, area);
		area = { w * 24, h * 10, w * 4, h * 10 };
		camera->InsertLevelArea(0, area);
	}

	virtual void handle_events(SDL_Event& ev)
	{
		if (ev.type == SDL_KEYDOWN)
		{
			// Switch between to collision method
			switch (ev.key.keysym.sym)
			{
			case SDLK_1:
				use_sphere_collider = true;
				std::cout << "switch to box collider" << std::endl;
				break;
			case SDLK_2:
				use_sphere_collider = false;
				std::cout << "switch to circle distance collider" << std::endl;
				break;
			}
		}

		Scene::handle_events(ev);
	}

	virtual void update()
	{
		// Level 0 as a default
		Global::GetMainCamera()->SetCurrentLevel(0);

		handle_collisions();

		Scene::update();
	}

	virtual void render(SDL_Renderer* ren)
	{
		// The color for drawing. It is set to white here
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);

		// Clear the entire screen to selected color
		SDL_RenderClear(ren);

		Scene::render(ren);
	}

	// Collision handler
	void handle_collisions()
	{
		// Loop through every object in the scene
		for (unsigned int i = 0; i < objects_list.size(); i++)
		{
			GameObject* src = objects_list[i];
			if (!src->IsCollidable())
				continue;

			for (unsigned int j = 0; j < objects_list.size(); j++)
			{
				GameObject* dest = objects_list[j];

				if (!dest->IsCollidable())
					continue;

				if (src == dest)
					continue;

				bool result = false;
				if (use_sphere_collider)
					result = src->IsCollideWith_Sphere(dest);
				else
					result = src->IsCollideWith_Box(dest);

				if (result)
				{
					src->CollisionResponse(dest);
					//dest->CollisionResponse(src);
				}
			}
		}
	}

	void SwitchLevel(const int& _level)
	{
		currentLevel = _level;
		Global::GetMainCamera()->SetCurrentLevel(_level);
	}

	virtual void GameEnd();

private:
	Player* player;
	std::vector<Pickup*> pickUps;
	Map* map;
	Camera* camera;
	ParticleEmitter* pe;
	bool use_sphere_collider;
	std::vector<Enemy*> enemy_list;
	SushiBoss* boss;
	int currentLevel;
};

#endif // SCENE_H
