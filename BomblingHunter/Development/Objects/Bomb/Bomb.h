#pragma once

#include "../GameObjects.h"

class Bomb : public GameObject
{
public:
	int Bomb_image;
	Vector2D direction;

public:
	Bomb();
	~Bomb();
	void Initialize();
	void Update();
	void Draw() const;

private:
	void Speed();
	void Movement();
};

