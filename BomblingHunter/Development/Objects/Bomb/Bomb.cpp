#include"Bomb.h"
#include"../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/FlyEnemy/FlyEnemy.h"
#include "../Harpy/Harpy.h"
#include "../Enemy/GoldEnemy/GoldEnemy.h"
#include "../../Scene/Scene.h"
#include"DxLib.h"

Bomb::Bomb(): bomb_image(0),direction(0.0f),ex_image(0),bomb_hit_se()
{
	bomb_effect[0] = NULL;
	bomb_effect[1] = NULL;
	bomb_effect[2] = NULL;
	bomb_effect[3] = NULL;
}

Bomb::~Bomb() 
{

}

//初期化処理
void Bomb::Initialize()
{
	//爆弾画像・エフェクト
	bomb_effect[0] = LoadGraph("Resource/images/爆弾.png");
	bomb_effect[1] = LoadGraph("Resource/images/爆風1.png");
	bomb_effect[2] = LoadGraph("Resource/images/爆風2.png");
	bomb_effect[3] = LoadGraph("Resource/images/爆風3.png");
	//爆破音
	bomb_hit_se = LoadSoundMem("Resource/sounds/explosion.wav");
	//初期進行方向の設定
	direction = Vector2D(0.0f, 2.0f);
	//初期化画像
	bomb_image = bomb_effect[0];
}

//更新処理
void Bomb::Update()
{
	Movement();
}

//描画処理
void Bomb::Draw() const
{
    DrawRotaGraphF(location.x, location.y, 1.0, radian, bomb_image, TRUE);
}

void Bomb::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(bomb_image);
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	Scene::score;
	//当たった時の処理
	if (!(dynamic_cast<Player*>(hit_object) != nullptr))
	{
		delete_flag = TRUE;
	}
	//ハコテキに当たった時
	if (dynamic_cast<Enemy*>(hit_object) != nullptr)
	{
		Enemy::count--;
		Scene::score += 300;
		
	}
	//ハーピーに当たった時
	if (dynamic_cast<Harpy*>(hit_object) != nullptr)
	{
		Harpy::count--;
		Scene::score -= 100;
		
	}
	//ハネテキに当たった時
	if (dynamic_cast<FlyEnemy*>(hit_object) != nullptr)
	{
		FlyEnemy::count--;
		Scene::score += 100;
	}
	//金テキに当たった時
	if (dynamic_cast<GoldEnemy*>(hit_object) != nullptr)
	{
		Scene::score += 1500;
		GoldEnemy::count--;
	}
}

//移動処理
void Bomb::Movement()
{

	if (((location.y + direction.y) < box_size.y))
	{
		direction.y *= -1.0f;
	}

	if (location.y == 500.0f)
	{
		Finalize();
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}
//エフェクト処理
void Bomb::EffectControl()
{
	//フレームカウントを加算する
	effect_count++;

	//60フレーム目に到達したら
	if (effect_count >= 60)
	{
		//カウントのリセット
		effect_count = 0;

		//画像の切り替え
		if (bomb_image == bomb_effect[0])
		{
			bomb_image = bomb_effect[2];
		}
		else
		{
			bomb_image = bomb_effect[0];
		}
	}
}