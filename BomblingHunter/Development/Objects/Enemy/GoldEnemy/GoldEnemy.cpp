#include "GoldEnemy.h"
#include "../../Bomb/Bomb.h"
#include "DxLib.h"

int GoldEnemy::count = 0;

GoldEnemy::GoldEnemy() : animation_count(0), direction(0.0f),hit_se()
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;

}

GoldEnemy::~GoldEnemy()
{
	
}

//初期化処理
void GoldEnemy::Initialize()
{
	//画像の読込み
	animation[0] = LoadGraph("Resource/Images/金のテキ1.png");
	animation[1] = LoadGraph("Resource/Images/金のテキ2.png");
	animation[2] = LoadGraph("Resource/Images/金のテキ3.png");
	animation[3] = LoadGraph("Resource/Images/金のテキ4.png");
	animation[4] = LoadGraph("Resource/Images/金のテキ5.png");

	//BGM・SE読み込み
	hit_se = LoadSoundMem("Resource/sounds/arrows_perfect03_short.wav");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("金のテキの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	image = animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);
}

//更新処理
void GoldEnemy::Update()
{
	//移動処理
	Movement();

	//アニメーション制御
	AnimationControl();
}

//描画処理
void GoldEnemy::Draw() const
{
	//画像反転フラグ
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//情報を基にハコテキ画像を描画する
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void GoldEnemy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
	DeleteGraph(animation[4]);
}

//当たり判定通知処理
void GoldEnemy::OnHitCollision(GameObject* hit_object)
{
	if (dynamic_cast<Bomb*>(hit_object))
	{
		direction = 0.0f;
		Finalize();
		box_size = 0.0f;
		PlaySoundMem(hit_se, DX_PLAYTYPE_BACK);
	}
}

//移動処理
void GoldEnemy::Movement()
{
	if (((location.x + direction.x) < (-80.0f - box_size.x)) || (1040.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}
	if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//アニメーション制御
void GoldEnemy::AnimationControl()
{
	//アニメーションカウントを加算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントのリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
