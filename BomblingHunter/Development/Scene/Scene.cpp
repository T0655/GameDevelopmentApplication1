#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Utility/InputControl.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Objects/Harpy/Harpy.h"
#include "../Objects/Enemy/GoldEnemy/GoldEnemy.h"
#include "../Objects/Enemy/FlyEnemy/FlyEnemy.h"
#include "../Objects/EnemyBullet/EnemyBullet.h"
#include "../Timer/Timer.h"
#include "DxLib.h"

//コンストラクタ
Scene::Scene() :objects(),scene_images(),scene_bgm(),tm_images()
{
}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	scene_images = LoadGraph("Resource/images/背景.png");
	tm_images= LoadGraph("Resource/images/タイマー.png");

	scene_bgm = LoadSoundMem("Resource/sounds/BGM_arrows.wav");
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 60.0f));
	//ハコテキを生成する
	CreateObject<Enemy>(Vector2D(100.0f, 500.0f));
}

//更新処理
void Scene::Update()
{
	//オブジェクトリスト内のオブジェクトを更新する
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
	

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i],objects[j]);
		}
	}
	//Qキーを押したら、ハーピーを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_Q))
	{
		CreateObject<Harpy>(Vector2D(100.0f, 200.0f));
	}
	//Zキーを押したら、ハコテキを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 500.0f));
	}
	//Eキーを押したら、ハネテキを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_E))
	{
		CreateObject<FlyEnemy>(Vector2D(100.0f, 200.0f));
	}
	//Cキーを押したら、金のテキを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_C))
	{
		CreateObject<GoldEnemy>(Vector2D(100.0f, 510.0f));
	}
	//スペースキーを押したら、プレイヤーの位置から爆弾を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		for (int i =0; i < objects.size(); i++)
		{
			if (!(dynamic_cast<Player*>(objects[i]) == nullptr))
			{
				CreateObject<Bomb>(objects[i]->GetLocation());
			}
		}
	}
	//Gキーを押したら、エネミーの位置から敵弾を生成する
	if (InputControl::GetKeyDown(KEY_INPUT_G))
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (!(dynamic_cast<Enemy*>(objects[i]) == nullptr))
			{
				CreateObject<EnemyBullet>(objects[i]->GetLocation());
			}
		}
	}
}

//描画処理
void Scene::Draw()const
{
	//背景の描画
	DrawGraph(0,-120, scene_images, FALSE);
	DrawGraph(15, 542, tm_images, TRUE);

	
	

	//オブジェクトリスト内のオブジェクトを描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	StopSoundMem(scene_bgm);

	//動的配列の開放
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//当たり判定チェック処理(矩形の中心で当たり判定を取る)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);

	}
}
#else

//当たり判定チェック処理(左上頂点の座標から当たり判定計算を行う)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を取得する
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) && (a->GetLocation().y < b_lower_right.y) && (a_lower_right.x > b->GetLocation().x) && (a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHit判定を通知する
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif //D_PIVOT_CENTER