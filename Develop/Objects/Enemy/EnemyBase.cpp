#include "EnemyBase.h"
#include "DxLib.h"
#include "../../Utility/ResourceManager.h"
#include "../Player/Player.h"
#include "../../Utility/InputManager.h"

//コンストラクタ
EnemyBase::EnemyBase() 
: move_animation(),
  eye_animation(),
  velocity(0.0f),
  enemy_state(eEnemyState::WAIT),
  now_direction(eMoveState::RIGHT),
  next_direction_state(eMoveState::RIGHT),
  animation_time(0.0f),
  animation_count(0),
  enemy_time(0.0f),
  flame_time(0.0f)
{
}
//デストラクタ
EnemyBase::~EnemyBase()
{
}

//初期化処理
void EnemyBase::Initialize() 
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
}

//更新処理
void EnemyBase::Update(float delta_second) 
{
	Movement(delta_second);
}

//描画処理
void EnemyBase::Draw(const Vector2D& screen_offset)const 
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

//終了時処理
void EnemyBase::Finalize() 
{
	// 動的配列の解放
	move_animation.clear();
	eye_animation.clear();
}

//当たり判定処理
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
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
	// 当たるときプレイヤーが無敵状態である場合
	if (hit_object->GetCollision().object_type == eObjectType::special)
	{
		enemy_state = eEnemyState::WEEKEND;
	}

	// 当たるときプレイヤーが無敵状態である場合
	if (hit_object->GetCollision().object_type == eObjectType::player)
	{
		enemy_state = eEnemyState::RUN;
	}
}

//移動処理
void EnemyBase::Movement(float delta_second)
{
	switch (enemy_state)
	{
	case eEnemyState::WAIT:
		// 画像の設定
		image = move_animation[9];
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
}

//エネミー待機処理
void EnemyBase::WaitMoment(float delta_second)
{
	if (enemy_time < 0.0f)
	{
		enemy_state = WORK;
	}
}

//ナワバリ巡回処理
void EnemyBase::TerritoryMove(float delta_second)
{
	
}

//イジケ状態処理
void EnemyBase::WeekendMove(float delta_second)
{

}

//追いかけ処理
void EnemyBase::ChaseMoment(float delta_second)
{

}

//帰巣処理
void EnemyBase::RunMoment(float delta_second)
{
	// 死亡中のアニメーション
	animation_time += delta_second;
	if (animation_time >= 0.07f)
	{
		animation_time = 0.0f;
		animation_count++;
		// 復活させる
		if (animation_count >= eye_animation.size())
		{
			enemy_state = eEnemyState::CHASE;
			animation_count = 0;
		}
	}
	image = eye_animation[animation_count];
}

//アニメーション処理
void EnemyBase::AnimationControl(float delta_second)
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