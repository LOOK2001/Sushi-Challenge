// Base class for all entities in Game Engine
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <vector>

#include <SDL2/SDL.h>

#include "Image.h"


#define PI 3.14159265
//#define DEBUG_COLLIDERS

enum ObjectType
{
	NONE,
	PLAYER,
	PICKUP,
	BULLET,
	ENEMY_BULLET,
	BLAST,
	WALL,
	LEVEL1,
	LEVEL2,
	LEVEL3
};


// GameObject Declaration:
// Base class for everything displayed on the screen
class GameObject
{
public:
	GameObject() :
	parent(nullptr)
	{}
	virtual ~GameObject() {}

	virtual void init(){
		active = true;
		collidable = false;
		type = ObjectType::NONE;

		for (size_t i = 0; i < children.size(); i++)
			children[i]->init();
	}
	virtual void update(){
		for (size_t i = 0; i < children.size(); i++)
			children[i]->update();
	}
	virtual void lateUpdate() {
		for (size_t i = 0; i < children.size(); i++)
			children[i]->lateUpdate();
	}
	virtual void handle_events(SDL_Event& ev){
		for (size_t i = 0; i < children.size(); i++)
			children[i]->handle_events(ev);
	}
	virtual void render(SDL_Renderer* ren){
		for (size_t i = 0; i < children.size(); i++)
			children[i]->render(ren);
	}
	virtual void quit(){
		for (size_t i = 0; i < children.size(); i++)
			children[i]->quit();
	}

	virtual ObjectType GetObjectType() const { return type; }
	virtual void SetObjectType(const ObjectType _type) { type = _type; }

	bool GetActive() const { return active; }
	void SetActive(const bool _active) { active = _active; }

	bool AddChild(GameObject* obj);
	bool RemoveChild(GameObject* obj);

	virtual SDL_FPoint GetGlobalPosition() const { return { 0.0, 0.0 }; }

	// collision
	virtual void SetCollidable(const bool _c) { collidable = _c; }
	virtual bool IsCollidable() const { return collidable; }
	virtual bool IsCollideWith_Box(GameObject* dest) { return false; }
	virtual bool IsCollideWith_Sphere(GameObject* dest) { return false; }
	virtual void CollisionResponse(GameObject* other) {};

	virtual SDL_FRect GetBoxCollider() { return boxCollider_local; }
	virtual void SetBoxCollider(float _x, float _y, float _w, float _h) { boxCollider_local = { _x, _y, _w, _h }; }
	virtual void SetBoxCollider(const SDL_FRect box) { boxCollider_local = box; }

	virtual float GetCirlceColliderRadius() const { return radius; }
	virtual void SetCirlceColliderRadius(float _radius) { radius = _radius; }

	virtual SDL_FPoint GetCircleColliderCenter() const { return center; }
	virtual void SetCircleColliderCenter(float _x, float _y) { center = {_x, _y}; }
	virtual void SetCircleColliderCenter(SDL_FPoint _center) { center = _center; }

protected:
	bool collidable;
	float radius;
	SDL_FPoint center;
	bool active;
	SDL_FRect boxCollider_local;
	std::vector<GameObject*> children;
	GameObject* parent;
	ObjectType type;
};


// RectObject Declaration:
// Base class of rect objects
class RectObject : public GameObject
{
public:
	RectObject() {}
	RectObject(float x, float y, float w, float h)
	{
		SetPosition(x, y);
		SetWidth(w);
		SetHeight(h);

		collidable = true;
	}
	virtual ~RectObject() {}

	virtual void init();
	virtual void update();
	virtual void handle_events(SDL_Event& ev);
	virtual void render(SDL_Renderer* ren);
	virtual void RenderBoxCollider(SDL_Renderer* ren);
	virtual void quit();

	virtual void SetPosition(const float x, const float y);
	virtual SDL_FPoint GetPosition() const;

	void setSize(const float _w, const float _h) { rect.w = _w, rect.h = _h; }
	SDL_FRect GetSize() const { return rect; }

	void SetWidth(const float w) { rect.w = w; }
	float GetWidth() const { return rect.w; }
	void SetHeight(const float h) { rect.h = h; }
	float GetHeight() const { return rect.h; }

	virtual SDL_FPoint GetGlobalPosition() const;

	virtual void translate(const float x, const float y);
	virtual void rotate(float angle, SDL_FPoint p);
	virtual SDL_FRect GetBoxCollider();
	virtual SDL_FPoint GetCircleColliderCenter() const;
	virtual bool IsCollideWith_Box(GameObject* dest);
	virtual bool IsCollideWith_Sphere(GameObject* dest);

protected:
	//SDL_Texture* texture;
	std::vector<GameObject*> children;
	SDL_FRect rect;
};


class TextureObject : public RectObject
{
public:
	TextureObject(const char* name, float x, float y);
	virtual ~TextureObject();

	virtual void init();
	virtual void render(SDL_Renderer* ren);

	virtual void SetAngle(const float _angle) { angle = _angle; }
	virtual float GetAngle() const { return angle; }

	virtual void SetCenter(const SDL_FPoint _center) { center = _center; }
	virtual SDL_FPoint GetCenter() const { return center; }

	virtual void SetFlip(const SDL_RendererFlip _filp) { flip = _filp; }
	virtual SDL_RendererFlip GetFlip() const { return flip; }

	virtual int GetImgWidth() const { return img->GetImgWidth(); }
	virtual int GetImgHeight() const { return img->GetImagHeight(); }

protected:
	Image* img;
	float angle;
	SDL_RendererFlip flip;
	SDL_FPoint center;
};


// RectFillObject Declaration:
// Base class of color objects
class RectFillObject : public RectObject
{
public:
	RectFillObject() {}
	RectFillObject(SDL_Color _color, float x, float y, float w, float h) : color(_color)
	{
		SetPosition(x, y);
		SetWidth(w);
		SetHeight(h);
	}
	virtual ~RectFillObject() {}

	virtual void init();
	virtual void render(SDL_Renderer* ren);

	SDL_Color getColor() const { return color; }
	void setColor(SDL_Color _color) { color = _color; }
	void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a) { setColor(SDL_Color{ r, g, b, a }); }

	SDL_FPoint GetPosition() const;
	void SetPosition(const float x, const float y);

	void SetWidth(const float w) { rect.w = w; }
	void SetHeight(const float h) { rect.h = h; }

	void translate(const float x, const float y);
	void rotate(float angle, SDL_FPoint _center);

private:
	SDL_Color color;
};

#endif // GAMEOBJECT_H
