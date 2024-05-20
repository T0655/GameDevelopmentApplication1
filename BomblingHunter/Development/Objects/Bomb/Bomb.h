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

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Speed();
	void Movement();

	
};

