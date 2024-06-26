#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Utility/InputControl.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Objects/Harpy/Harpy.h"
#include "../Objects/Enemy/GoldEnemy/GoldEnemy.h"
#include "../Objects/Enemy/FlyEnemy/FlyEnemy.h"
#include "../Objects/EnemyBullet/EnemyBullet.h"
#include "../Time/Time.h"
#include "DxLib.h"
#include <time.h>
#include <math.h>

#define TIMELIMIT      (4000 * 3)//制限時間
#define NUMBER         (10)


//コンストラクタ
Scene::Scene() :objects(),game_score(), scene_images(), scene_bgm(), tm_images(), score(), score_image(), high_score_image(), result_image_bad(), result_image_ok(), result_image_good(), result_image_perfect()
{
	num_image[NUMBER];
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
	

	//画像
	scene_images = LoadGraph("Resource/images/背景.png");
	tm_images= LoadGraph("Resource/images/タイマー.png");
	result_image_bad= LoadGraph("Resource/images/BAD.png");
	result_image_ok= LoadGraph("Resource/images/OK.png");
	result_image_good= LoadGraph("Resource/images/GOOD.png");
	result_image_perfect= LoadGraph("Resource/images/Perfect.png");
	score_image = LoadGraph("Resource/images/スコア.png");
	high_score_image = LoadGraph("Resource/images/ハイスコア.png");
	LoadDivGraph("images/number.png", NUMBER,NUMBER, 1, 60, 120, num_image);
	//音源
	scene_bgm = LoadSoundMem("Resource/sounds/BGM_arrows.wav");
	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 60.0f));

	Time::timer = TIMELIMIT;

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
		CreateObject<Enemy>(Vector2D(100.0f, 485.0f));
	}
	//Eキーを押したら、ハネテキを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_E))
	{
		CreateObject<FlyEnemy>(Vector2D(100.0f, 200.0f));
	}
	//Cキーを押したら、金のテキを生成する
	if (InputControl::GetKeyDown(KEY_INPUT_C))
	{
		CreateObject<GoldEnemy>(Vector2D(100.0f, 500.0f));
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
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->DeleteObjectFinalize() == TRUE)
		{
			this->objects.erase(objects.begin() + i);
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
	Enemy::count;
	FlyEnemy::count;
	Harpy::count;
	int num1 = rand() % 100 + 1;
	int num2 = rand() % 3 + 1;
	
	flame_count++;
	//ハコテキ
	if (flame_count > 120)
	{
		if (Enemy::count < 2)
		{
			if (num1 < 20) {
				CreateObject<Enemy>(Vector2D(-70.0f, 485.0f));
				CreateObject<Enemy>(Vector2D(1000.0f, 485.0f));
				flame_count = 0;
			}
		}
	}
	//ハーピー
	if (flame_count > 120)
	{
		if (Harpy::count < 2)
		{
			if (num1 < 40)
			{
				CreateObject<Harpy>(Vector2D(-70.0f, 200.0f));
				CreateObject<Harpy>(Vector2D(880.0f, 400.0f));
				flame_count = 0;
			}
		}
	}
	//ハネテキ
	if (flame_count > 300)
	{
		if (FlyEnemy::count < 5)
		{
			if (num1<50)
			{
				CreateObject<FlyEnemy>(Vector2D(-70.0f, 300.0f));
				FlyEnemy::count++;
				flame_count = 0;
			}
			if (FlyEnemy::count > 1)
			{
				CreateObject<FlyEnemy>(Vector2D(880.0f, 200.0f));
				flame_count = 0;
			}
			if (FlyEnemy::count > 3)
			{
				CreateObject<FlyEnemy>(Vector2D(-70.0f, 400.0f));
				flame_count = 0;
			}
			if (FlyEnemy::count > 4)
			{
				CreateObject<FlyEnemy>(Vector2D(1100.0f, 400.0f));
				FlyEnemy::count++;
				flame_count = 0;
			}

		}
	}
	Time::timer--;
}

//描画処理
void Scene::Draw()const
{
	//背景の描画
	DrawGraph(0,-120, scene_images, FALSE);
	//タイマーの描画
	DrawGraph(15, 542, tm_images, TRUE);
	//スコアの描画
	DrawGraph(200, 560, score_image, TRUE);
	//ハイスコアの描画
	DrawGraph(500, 560, high_score_image, TRUE);
	//音量調整
	ChangeVolumeSoundMem(255 * 30 / 100, scene_bgm);
	//BGM
	PlaySoundMem(scene_bgm, DX_PLAYTYPE_LOOP,FALSE);

	//オブジェクトリスト内のオブジェクトを描画処理
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}

	//制限時間の描画
	//DrawGraph(300,560,560 - Time::timer / 60 * 2, num_image[NUMBER]);
	DrawBox(491, 469, 509, 469 - Time::timer / 60 * 2, 0x0033ff, TRUE);
	DrawFormatString;
}

void Scene::Score()
{
	
}

void Scene::Time()
{
	

}

void Scene::Result()
{
	Score();
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