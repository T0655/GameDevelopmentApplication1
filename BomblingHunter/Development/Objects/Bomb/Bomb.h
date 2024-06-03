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

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();
};

