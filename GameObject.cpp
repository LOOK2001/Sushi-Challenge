#include<algorithm>

#include "include/GameObject.h"
#include "include/Camera.h"
#include "include/Global.h"
#include "include/Utils.h"


// GameObject Implementation
bool GameObject::AddChild(GameObject* obj)
{
	if (std::find(children.begin(), children.end(), obj) != children.end())
		return false;

	obj->parent = this;
	children.push_back(obj);
	return true;
}


bool GameObject::RemoveChild(GameObject* obj)
{
	if (std::find(children.begin(), children.end(), obj) == children.end())
		return false;

	children.erase(std::remove(children.begin(), children.end(), obj), children.end());
	return true;
}

// RectObject Implementation
void RectObject::init()
{
	GameObject::init();
	collidable = true;
}

void RectObject::update()
{
	if (!active)
		return;

	GameObject::update();
}

void RectObject::handle_events(SDL_Event& ev)
{
	if (!active)
		return;

	GameObject::handle_events(ev);
}

void RectObject::render(SDL_Renderer* ren)
{
	if (!active)
		return;

	GameObject::render(ren);

#ifdef DEBUG_COLLIDERS
	RenderBoxCollider(ren);
#endif // DEBUG_COLLIDERS
}

void RectObject::RenderBoxCollider(SDL_Renderer* ren)
{
	Camera* camera = Global::GetMainCamera();
	SDL_FPoint pos = camera->GetPos();

	SDL_FRect bb = this->GetBoxCollider();

	float x = bb.x - pos.x;
	float y = bb.y - pos.y;

	SDL_SetRenderDrawColor(ren, 255, 0, 0, 128);
	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	SDL_FRect box;
	box = { x, y, bb.w, bb.h };
	SDL_RenderFillRectF(ren, &box);
}


void RectObject::quit()
{
	for (auto child : children)
		child->quit();
}

SDL_FPoint RectObject::GetPosition() const
{
	SDL_FPoint p;
	p.x = rect.x;
	p.y = rect.y;
	return p;
}

void RectObject::SetPosition(const float x, const float y)
{
	rect.x = x;
	rect.y = y;
}

SDL_FPoint RectObject::GetGlobalPosition() const
{
	SDL_FPoint global_position = { 0.0, 0.0 };
	SDL_FPoint p_pos = { 0.0, 0.0 };
	SDL_FPoint s_pos = GetPosition();

	if (parent)
		p_pos = parent->GetGlobalPosition();

	global_position = { p_pos.x + s_pos.x, p_pos.y + s_pos.y };
	return global_position;
}

void RectObject::translate(const float x, const float y)
{
	rect.x += x;
	rect.y += y;
}

void RectObject::rotate(float angle, SDL_FPoint p)
{
	float radian = angle * PI / 180.f;
	float x = (rect.x - p.x) * cos(radian) - (rect.y - p.y) * sin(radian) + p.x;
	float y = (rect.y - p.y) * cos(radian) + (rect.x - p.x) * sin(radian) + p.y;
	rect.x = x;
	rect.y = y;
}

SDL_FRect RectObject::GetBoxCollider()
{
	float x = rect.x + boxCollider_local.x;
	float y = rect.y + boxCollider_local.y;
	float w = boxCollider_local.w;
	float h = boxCollider_local.h;
	return { x, y, w, h };
}

SDL_FPoint RectObject::GetCircleColliderCenter() const
{
	return { center.x + rect.x, center.y + rect.y };
}

bool RectObject::IsCollideWith_Box(GameObject* dest)
{
	const SDL_FRect bb_r = this->GetBoxCollider();
	const SDL_FRect bb_d = dest->GetBoxCollider();

	float left_r, right_r, top_r, bottom_r;
	float left_d, right_d, top_d, bottom_d;

	left_r = bb_r.x;
	right_r = left_r + bb_r.w;
	bottom_r = bb_r.y;
	top_r = bottom_r + bb_r.h;

	left_d = bb_d.x;
	right_d = left_d + bb_d.w;
	bottom_d = bb_d.y;
	top_d = bottom_d + bb_d.h;

	if (right_r <= left_d ||
		left_r >= right_d ||
		bottom_r >= top_d ||
		top_r <= bottom_d)
		return false;

	return true;
}

bool RectObject::IsCollideWith_Sphere(GameObject* dest)
{
	SDL_FPoint center_r = this->GetCircleColliderCenter();
	float radius_r = this->GetCirlceColliderRadius();

	SDL_FPoint center_d = dest->GetCircleColliderCenter();
	float radius_d = dest->GetCirlceColliderRadius();

	float distance = Distance(center_r, center_d);

	if (distance > (radius_r + radius_d))
		return false;

	return true;
}

// RectFillObject Implementation:
void RectFillObject::render(SDL_Renderer* ren)
{
	if (!active)
		return;

	SDL_SetRenderDrawColor(ren, color.r, color.g, color.b, color.a);
	SDL_RenderFillRectF(ren, &rect);
}

SDL_FPoint RectFillObject::GetPosition() const
{
	SDL_FPoint p;
	p.x = rect.x;
	p.y = rect.y;
	return p;
}

void RectFillObject::SetPosition(const float x, const float y)
{
	rect.x = x;
	rect.y = y;
}

void RectFillObject::translate(const float x, const float y)
{
	rect.x += x;
	rect.y += y;
}

void RectFillObject::rotate(float angle, SDL_FPoint _c)
{
	float radian = angle * PI / 180.f;
	float x = (rect.x - _c.x) * cos(radian) - (rect.y - _c.y) * sin(radian) + _c.x;
	float y = (rect.y - _c.y) * cos(radian) + (rect.x - _c.x) * sin(radian) + _c.y;
	rect.x = x;
	rect.y = y;
}

TextureObject::TextureObject(const char* name, float x, float y)
{
	if (name)
		img = new Image(name);

	angle = 0.0f;
	center = SDL_FPoint();

	float width = (float)img->GetImgWidth();
	float height = (float)img->GetImagHeight();
	rect = { x, y, width, height };
}

TextureObject::~TextureObject()
{
	if (img)
		delete img;
}

void TextureObject::init()
{
	RectObject::init();
}

void TextureObject::render(SDL_Renderer* ren)
{
	if (!active)
		return;

	SDL_FPoint pos = GetGlobalPosition();
	img->Draw(pos.x, pos.y, angle, &center, flip);

	RectObject::render(ren);
}
