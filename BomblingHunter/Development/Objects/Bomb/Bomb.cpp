#include"Bomb.h"
#include"DxLib.h"

Bomb::Bomb(): Bomb_image(0),direction(0.0f),ex_image(0)
{

}

Bomb::~Bomb() 
{

}

//初期化処理
void Bomb::Initialize()
{
    Bomb_image = LoadGraph("Resource/images/爆弾.png");
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
    DrawRotaGraphF(location.x, location.y, 1.0, radian, Bomb_image, TRUE);
}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
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
