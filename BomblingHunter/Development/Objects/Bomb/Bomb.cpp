#include"Bomb.h"
#include"../Player/Player.h"
#include"DxLib.h"

Bomb::Bomb(): bomb_image(0),direction(0.0f),ex_image(0),bomb_hit_se()
{
}

Bomb::~Bomb() 
{

}

//初期化処理
void Bomb::Initialize()
{
    bomb_image = LoadGraph("Resource/images/爆弾.png");

	bomb_hit_se = LoadSoundMem("Resource/sounds/explosion.wav");
	//初期進行方向の設定
	direction = Vector2D(0.0f, 2.0f);
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
	//当たった時の処理
	if (!(dynamic_cast<Player*>(hit_object)))
	{
		Finalize();
	}
}

//移動処理
void Bomb::Movement()
{

	if (((location.y + direction.y) < box_size.y))
	{
		direction.y *= -1.0f;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}
