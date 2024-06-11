#pragma once

#include "../Objects/GameObjects.h"

class Score : public GameObject
{
public:
	int score;
	int draw_score;

public:
	Score();
	~Score();
	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

	//“–‚½‚è”»’è’Ê’mˆ—
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
};

