#pragma once

#include "../../Objects/GameObjects.h"

class Time : public GameObject
{
public:
	//タイマー
	static int timer;

public:
	Time();
	~Time();

	void Initialize();      //初期化処理
	void Update();          //更新処理
	void Draw();            //描画処理
	void Finalize();        //終了時処理
};

