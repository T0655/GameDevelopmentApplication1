#pragma once

#include "../GameObjects.h"

class Bomb : public GameObject
{
public:
	int bomb_hit_se;
	int bomb_image;
	int ex_image;
	int effect_count;
	int bomb_effect[3];
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
	void EffectControl();
};

