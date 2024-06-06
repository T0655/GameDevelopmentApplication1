#pragma once

#include "../GameObjects.h"

class EnemyBullet : public GameObject
{
public:
	int em_se;
	int em_image;
	int em_effect[2];
	int effect_count;
	Vector2D direction;

public:
	EnemyBullet();
	~EnemyBullet();
	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

	//“–‚½‚è”»’è’Ê’mˆ—
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();
	void EffectControl();
};

