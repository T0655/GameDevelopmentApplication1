#pragma once

#include "../../Objects/GameObjects.h"

class Time : public GameObject
{
public:
	static int timer;

public:
	Time();
	~Time();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();
};

