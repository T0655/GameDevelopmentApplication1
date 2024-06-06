#include "EnemyBullet.h"
#include "../Player/Player.h"
#include "DxLib.h"

EnemyBullet::EnemyBullet() : em_image(0),direction(0.0f),em_se(),effect_count(0)
{
	em_effect[0] = NULL;
	em_effect[1] = NULL;
	em_effect[2] = NULL;
}

EnemyBullet::~EnemyBullet()
{

}

//初期化処理
void EnemyBullet::Initialize()
{
	em_image = LoadGraph("Resource/images/敵弾1.png");
	em_effect[0] = LoadGraph("Resource/images/敵弾エフェクト1.png");
	em_effect[1] = LoadGraph("Resource/images/敵弾エフェクト2.png");
	em_effect[2] = LoadGraph("Resource/images/敵弾エフェクト3.png");

	em_se = LoadSoundMem("Resource/sounds/bishi.wav");
	//初期進行方向の設定
	direction = Vector2D(0.0f, -2.0f);
}

//更新処理
void EnemyBullet::Update()
{
	Movement();
}

//描画処理
void EnemyBullet::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1.0, radian, em_image, TRUE);
}

void EnemyBullet::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(em_image);
}

//当たり判定通知処理
void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	if (dynamic_cast<Player*>(hit_object))
	{
		Finalize();
		box_size = 0.0f;
		PlaySoundMem(em_se, 0);
		EffectControl();
	}
}

//移動処理
void EnemyBullet::Movement()
{

	if (((location.y + direction.y) < box_size.y))
	{
		direction.y *= 1.0f;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void EnemyBullet::EffectControl()
{
	//フレームカウントを加算する
	effect_count++;

	//60フレーム目に到達したら
	if (effect_count >= 60)
	{
		//カウントのリセット
		effect_count = 0;

		//画像の切り替え
		if (em_image == em_effect[0])
		{
			image = em_effect[1];
		}
		else
		{
			image = em_effect[0];
		}
	}
}
