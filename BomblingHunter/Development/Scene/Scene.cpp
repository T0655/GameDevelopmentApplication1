#include "Scene.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

#define D_PIVOT_CENTER

Scene::Scene() : objects()
{
}

Scene::~Scene()
{
	//解放忘れ防止
	Finalize();
}

void Scene::Initialize()
{
	//プレイヤーを画面中央あたりに生成する
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
}

void Scene::Initialize()
{
	//プレイヤーを画面中央あたりに生成する
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
}

void Scene::Update()
{
	//オブジェクトリスト内のオブジェクトを更新する
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//オブジェクト同士の当たり判定チェック
}
