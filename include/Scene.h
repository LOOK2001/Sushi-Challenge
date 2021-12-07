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


class Global;
// Scene Declaration:
// Base class for Scene. Scene class manage every gameObjects in the scene
class Scene
{
public:
	~Scene()
	{
		for (auto obj : objects_list)
			delete obj;
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

	virtual void AddGameObject(GameObject* _obj) { objects_list.push_back(_obj); }
	virtual void RemoveGameObject(GameObject * _obj) { objects_list.erase(std::remove(objects_list.begin(), objects_list.end(), _obj), objects_list.end()); }

protected:
	std::vector<GameObject*> objects_list;
};


// SceneHw3 Declaration:
class ExampleScene : public Scene
{
public:
	virtual void init()
	{
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
		// Map data stores index of tiles
		map->LoadMap("./include/map.txt");
		// Load tile set of map
		map->LoadTiles("./images/tileSet3.png", 4, 8);
		// Scale map up
		map->SetScaleFactor(1.5);
		map->init();
		objects_list.push_back(map);
		Global::SetActiveMap(map);

		TileSheet* sh = map->GetTileSheet();
		float offset = (float)sh->GetTileWidth();
		camera->SetViewOffset(offset * 2);

		// Random position for coins
		std::random_device r;
		std::default_random_engine e1(r());
		std::uniform_real_distribution<float> uniform_pos(0, 1500);

		//// Create 20 coins
		//for (auto i = 0; i < 5; i++)
		//{
		//	float pos_x = uniform_pos(e1);
		//	float pos_y = uniform_pos(e1);

		//	Pickup* coin = new Pickup(pos_x, pos_y, "./images/coinSprites.png");
		//	coin->init();
		//	coin->SetCount(6);
		//	coin->SetDuration(100.0);
		//	float width = coin->GetWidth();
		//	float height = coin->GetHeight();
		//	coin->SetBoxCollider(0.0, 0.0, width * 2, height * 2);
		//	coin->SetCircleColliderCenter(width / 2, height / 2);
		//	coin->SetCirlceColliderRadius(width / 2);
		//	pickUps.push_back(coin);
		//	objects_list.push_back(coin);
		//}

		// Create sprite animation for states of character
		SpriteObject* walk_state = new SpriteObject(6, 100, "./images/DinoSprites_walk.png");
		SpriteObject* idle_state = new SpriteObject(4, 100, "./images/DinoSprites_idle.png");

		player = new Player(right * 0.5f, bottom * 0.5f);
		player->SetDefaultState("idle");
		player->AddState(walk_state, "walk");
		player->AddState(idle_state, "idle");
		float view_width = (float)walk_state->GetViewWidth();
		float view_height = (float)walk_state->GetViewHeight();
		player->init();
		player->SetBoxCollider(view_width / 4, view_height / 2, view_width / 2, 80);
		player->SetCircleColliderCenter(view_width / 2, view_height / 2);
		player->SetCirlceColliderRadius(view_width / 2);
		Global::SetMainPlayer(player);
		camera->SetTarget(player);
		objects_list.push_back(player);

		// Enemy
		for (auto i = 0; i < 1; i++)
		{
			//float pos_x = uniform_pos(e1);
			//float pos_y = uniform_pos(e1);

			SpriteObject* default_state = new SpriteObject(1, 100, "./images/carrot.png");
			SpriteObject* hurt_state = new SpriteObject(1, 100, "./images/carrot_hurt.png");
			Enemy* enemy = new Enemy(300, 300);
			enemy->AddState(default_state, "idle");
			enemy->AddState(hurt_state, "hurt");
			enemy->SetDefaultState("idle");
			enemy->init();
			enemy_list.push_back(enemy);
			objects_list.push_back(enemy);
		}

		SpriteObject* default_state = new SpriteObject(1, 100, "./images/sushi.png");
		SpriteObject* hurt_state = new SpriteObject(1, 100, "./images/sushi_hurt.png");
		boss = new SushiBoss(100, 100);
		boss->AddState(default_state, "idle");
		boss->AddState(hurt_state, "hurt");
		boss->SetDefaultState("idle");
		boss->init();
		objects_list.push_back(boss);
	}

	virtual void handle_events(SDL_Event& ev)
	{
		if (ev.type == SDL_KEYDOWN)
		{
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
		handle_collisions();

		//// Camera follow the player
		//SDL_FPoint pos = player->GetPosition();
		//float w = camera->GetWidth() / 2;
		//float h = camera->GetHeight() / 2;

		//// Move camera on top of character
		//camera->SetPos(pos.x - w + 100, pos.y - h + 100);

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

	void handle_collisions()
	{
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
					dest->CollisionResponse(src);
				}
			}
		}
	}

private:
	Player* player;
	std::vector<Pickup*> pickUps;
	Map* map;
	Camera* camera;
	ParticleEmitter* pe;
	bool use_sphere_collider;
	std::vector<Enemy*> enemy_list;
	SushiBoss* boss;
};

#endif // SCENE_H
