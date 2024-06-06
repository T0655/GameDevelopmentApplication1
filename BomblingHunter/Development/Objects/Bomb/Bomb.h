#pragma once

#include "../GameObjects.h"

class Bomb : public GameObject
{
public:
	int bomb_hit_se;
	int bomb_image;
	int ex_image;
	Vector2D direction;

public:
	Bomb();
	~Bomb();
	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();
};

