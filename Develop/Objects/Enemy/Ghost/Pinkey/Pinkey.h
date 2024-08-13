#pragma once

#include "../../EnemyBase.h"
#include "../../../Player/Player.h"

class Pinkey : public EnemyBase
{
private:
	Player* player;
	Pinkey* pinkey;
	eEnemyState enemy_state;

public:
	Pinkey();
	virtual ~Pinkey();

	virtual void Initialize();
	virtual void Update(float delta_second);
	virtual void Draw(const Vector2D& screen_offset) const;
	virtual void Finalize();

	virtual void OnHitCollision(GameObjectBase* hit_object);

	eEnemyState GetEnemyState() const;

private:
	virtual void Movement(float delta_second) override;
	virtual void WaitMoment(float delta_second) override;
	virtual void TerritoryMove(float delta_second) override;
	virtual void WeekendMove(float delta_second);
	virtual void ChaseMoment(float delta_second);
	virtual void RunMoment(float delta_second);
	virtual void AnimationControl(float delta_second);
};

