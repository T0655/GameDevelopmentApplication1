#include "Player.h"
#include "../../Utility/InputControl.h"
#include "../Bomb/Bomb.h"
#include "../EnemyBullet/EnemyBullet.h"
#include "DxLib.h"

//コンストラクタ
Player::Player() : animation_count(0), filp_flag(FALSE),hit_se()
{
	animation[0] = NULL;
	animation[1] = NULL;	
}

//デストラクタ
Player::~Player()
{
}

//初期化処理
void Player::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/飛ぶ1.png");
	animation[1] = LoadGraph("Resource/Images/飛ぶ2.png");

	//BGM・SE読み込み
	hit_se = LoadSoundMem("Resource/sounds/bishi.wav");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("トリパイロットの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0;

	//初期画像の設定
	image = animation[0];
}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimeControl();
}

//描画処理
void Player::Draw()const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(location.x ,location.y, 1.0, radian, image, TRUE, filp_flag);

	//デバッグ用
    #if _DEBUG
	//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y, box_collision_lower_right.x, box_collision_lower_right.y, GetColor(255, 0, 0), FALSE);
#endif
}

//終了時処理
void Player::Finalize()
{
	//使用した画像を開放する
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Player::OnHitCollision(GameObject* hit_object)
{
	//当たった時の処理
	if (dynamic_cast<EnemyBullet*>(hit_object))
	{
		/*PlaySoundMem(hit_se, 0);
		WaitTimer(2000);
		StopSoundMem;*/
	}
	
}

//移動処理
void Player::Movement()
{
	//移動の速さ
	Vector2D velocity = 0.0f;

	//左右移動
	if (InputControl::GetKey(KEY_INPUT_LEFT))
	{
		velocity.x += -3.0f;
		filp_flag = TRUE;
	}
	else if (InputControl::GetKey(KEY_INPUT_RIGHT))
	{
		velocity.x += 3.0f;
		filp_flag = FALSE;
	}
	else
	{
		velocity.x += 0.0f;
	}

	//左端で止める(赤い四角基準)
	if (location.x < (box_size.x / 2.0f))
	{
		velocity.x = 0.0f;
		location.x = box_size.x / 2.0f;
	}
	//右端で止める(赤い四角基準)
	else if ((640.0f - (box_size.x / 2.0f)) < location.x)
	{
		velocity.x = 0.0f;
		location.x = 640.0f - (box_size.x / 2.0f);
	}

	//現在の位置座標に速さを加算する
	location += velocity;
}

//アニメーション制御
void Player::AnimeControl()
{
	//フレームカウントを加算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
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