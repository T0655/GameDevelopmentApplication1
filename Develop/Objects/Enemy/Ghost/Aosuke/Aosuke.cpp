#include "Aosuke.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"
#include "../../../Player/Player.h"
#include "../../Utility/InputManager.h"

#define D_ENEMY_SPEED (50.0f)

//コンストラクタ
Aosuke::Aosuke()
{
	
}
//デストラクタ
Aosuke::~Aosuke()
{
}

//初期化処理
void Aosuke::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 12, 1, 32, 32);
	eye_animation = rm->GetImages("Resource/Images/eyes.png", 4, 11, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	collision.hit_object_type.push_back(eObjectType::special);
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	enemy_time = 0.0f;
}

//更新処理
void Aosuke::Update(float delta_second)
{
	EnemyBase::Movement(delta_second);
}

//描画処理
void Aosuke::Draw(const Vector2D& screen_offset)const
{
	DrawFormatString(5, 5, 0xffffff, "X座標:%f", location.x);
	DrawFormatString(5, 20, 0xffffff, "Y座標:%f", location.y);
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

//終了時処理
void Aosuke::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	eye_animation.clear();
}

//当たり判定処理
void Aosuke::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Enemyからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;
	}
	// 当たるときプレイヤーがである場合
	if (hit_object->GetCollision().object_type == eObjectType::special)
	{
		enemy_state = eEnemyState::WEEKEND;
	}
}

//移動処理
void Aosuke::Movement(float delta_second)
{
	enemy_state = WORK;

	switch (enemy_state)
	{
	case eEnemyState::WAIT:
		WaitMoment(delta_second);
		break;
	case eEnemyState::WORK:
		// アニメーション制御
		AnimationControl(delta_second);
		break;
	case eEnemyState::TERRITORY:
		TerritoryMove(delta_second);
		break;
	case eEnemyState::WEEKEND:
		WeekendMove(delta_second);
		break;
	case eEnemyState::CHASE:
		ChaseMoment(delta_second);
		break;
	case eEnemyState::RUN:
		RunMoment(delta_second);
		break;
	default:
		break;
	}

	// 進行方向の移動量を追加
	switch (now_direction)
	{
	case eMoveState::UP:
		velocity.y = -1.0f;
		break;
	case eMoveState::DOWN:
		velocity.y = 1.0f;
		break;
	case eMoveState::LEFT:
		velocity.x = -1.0f;
		break;
	case eMoveState::RIGHT:
		velocity.x = 1.0f;
		break;
	default:
		break;
	}

	// 移動量 * 速さ * 時間 で移動先を決定する
	location += velocity * D_ENEMY_SPEED * delta_second;
}

//エネミー待機処理
void Aosuke::WaitMoment(float delta_second)
{
	image = move_animation[5];

	if (enemy_time > 1500.0f) {
		aosuke_state = eEnemyState::TERRITORY;
	}
	// 初期位置の移動処理
	if (location.x==300.0f && location.y==323.5f) {
		now_direction = eMoveState::RIGHT;
		if (now_direction == eMoveState::RIGHT) {
			next_direction_state = eMoveState::RIGHT;
		}
	}
	// 初期位置の右端処理
	if (location.x == 396.5f && location.y == 323.5f) {
		now_direction = eMoveState::LEFT;
		if (now_direction == eMoveState::LEFT) {
			next_direction_state = eMoveState::LEFT;
		}
	}
	// 初期位置の左端処理
	if (location.x == 275.5f && location.y == 323.5f) {
		now_direction = eMoveState::RIGHT;
		if (now_direction == eMoveState::RIGHT) {
			next_direction_state = eMoveState::RIGHT;
		}
	}
}

//ナワバリ巡回処理
void Aosuke::TerritoryMove(float delta_second)
{
	now_direction = eMoveState::UP;
}

//イジケ状態
void Aosuke::WeekendMove(float delta_second)
{

}

//追いかけ処理
void Aosuke::ChaseMoment(float delta_second)
{
	player->GetLocation();

	now_direction = RIGHT;
}

void Aosuke::RunMoment(float delta_second)
{
	if (enemy_state == eEnemyState::RUN)
	{

	}
	image = eye_animation[4];
}

//アニメーション処理
void Aosuke::AnimationControl(float delta_second)
{
	// 移動中のアニメーション
	animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 4)
		{
			animation_count = 0;
		}
		// 画像の設定
		int dir_num = (int)now_direction;
		if (0 <= dir_num && dir_num < 4)
		{
			image = move_animation[(dir_num * 3) + animation_num[animation_count]];
		}

	}
}