#pragma once

#include "../../Objects/GameObjects.h"

class Score : public GameObject
{
public:
	static int score;

public:
	Score();
	~Score();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};



