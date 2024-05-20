#pragma once

#include "../GameObjects.h"
#include "../Enemy/Enemy.h"

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

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Speed();
	void Movement();

	
};

