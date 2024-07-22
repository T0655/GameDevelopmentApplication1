#pragma once

#include "../../EnemyBase.h"
#include "../../../Player/Player.h"

class Pinkey : public EnemyBase
{
private:
	Player* player;
	eEnemyState enemy_state;

public:
	Pinkey();
	virtual ~Pinkey();

	eEnemyState GetEnemyState() const;

private:
	virtual void Movement(float delta_second) override;
};

