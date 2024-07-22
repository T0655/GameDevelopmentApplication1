#pragma once

#include "../../EnemyBase.h"
#include "../../../Player/Player.h"

class Aosuke : public EnemyBase
{
private:
	Player* player;
	eEnemyState enemy_state;

public:
	Aosuke();
	virtual ~Aosuke();

	eEnemyState GetEnemyState() const;

private:
	virtual void Movement(float delta_second) override;
};

