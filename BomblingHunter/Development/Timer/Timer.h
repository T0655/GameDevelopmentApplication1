#pragma once

#include "../Objects/GameObjects.h"

class Timer : public GameObject
{
public:
	int tm_image;

public:
	Timer();
	~Timer();
	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

private:
};

