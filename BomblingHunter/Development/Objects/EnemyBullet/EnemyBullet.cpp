#include "EnemyBullet.h"
#include "../Player/Player.h"
#include "../../Time/Time.h"
#include "DxLib.h"

EnemyBullet::EnemyBullet() : direction(0.0f),em_se(),effect_count(0)
{
	em_effect[0] = NULL;
	em_effect[1] = NULL;
	em_effect[2] = NULL;
	em_effect[3] = NULL;
}

EnemyBullet::~EnemyBullet()
{

}

//初期化処理
void EnemyBullet::Initialize()
{
	//画像読み込み
	em_effect[0] = LoadGraph("Resource/images/敵弾1.png");
	em_effect[1] = LoadGraph("Resource/images/敵弾エフェクト1.png");
	em_effect[2] = LoadGraph("Resource/images/敵弾エフェクト2.png");
	em_effect[3] = LoadGraph("Resource/images/敵弾エフェクト3.png");
	//音源読み込み
	em_se = LoadSoundMem("Resource/sounds/bishi.wav");
	//初期進行方向の設定
	direction = Vector2D(0.0f, -2.0f);

	//初期画像の設定
	image = em_effect[0];
}

//更新処理
void EnemyBullet::Update()
{
	Movement();
}

//描画処理
void EnemyBullet::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE);
}

void EnemyBullet::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(em_effect[0]);
	DeleteGraph(em_effect[1]);
	DeleteGraph(em_effect[2]);
	DeleteGraph(em_effect[3]);
}

//当たり判定通知処理
void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	if (dynamic_cast<Player*>(hit_object))
	{
		Time::timer-=120;
		Finalize();
		PlaySoundMem(em_se, DX_PLAYTYPE_BACK,0);
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

//エフェクト処理
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
		if (image == em_effect[0])
		{
			image = em_effect[1];
		}
		else
		{
			image = em_effect[0];
		}
		
	}
}
