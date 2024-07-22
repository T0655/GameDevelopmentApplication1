#pragma once

#include "../../EnemyBase.h"
#include "../../../Player/Player.h"

class Guzuta : public EnemyBase
{
private:
	Player* player;
	eEnemyState enemy_state;

public:
	Guzuta();
	virtual ~Guzuta();

	eEnemyState GetEnemyState() const;

private:
	virtual void Movement(float delta_second) override;
};

