#pragma once

#include "../GameObjects.h"

class Bomb : public GameObject
{
public:
	int Bomb_image;
	int ex_image;
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

