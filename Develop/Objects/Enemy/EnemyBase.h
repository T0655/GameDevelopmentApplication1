#pragma once

#include "../GameObject.h"

enum eEnemyState
{
	WAIT,		// 待機状態
	WORK,		// 移動状態
	TERRITORY,  // ナワバリ状態
	WEEKEND,    // イジケ状態
	CHASE,      // 追いかけ状態
	RUN,        // 帰巣状態
	BASE,       // グズタとアオスケ専用
};

class EnemyBase : public GameObject
{
protected:
	// 進行方向状態
	enum eMoveState : unsigned char
	{
		UP,
		RIGHT,
		DOWN,
		LEFT,
	};

protected:
	std::vector<int> move_animation;		// ゴーストアニメーション画像
	std::vector<int> eye_animation;		    // 目だけの状態のアニメーション画像
	Vector2D old_location;					// 前回のlocation
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;				// プレイヤー状態
	eMoveState now_direction;				// 現在進行方向状態
	eMoveState next_direction_state;	    // 次回進行方向状態
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	float enemy_time;                       // 各ゴーストの待ち時間
	float flame_time;                       // フレーム時間

	int animation_num[19];

public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	eEnemyState GetEnemyState() const;

protected:
	virtual void Movement(float delta_second);
	virtual void WaitMoment(float delta_second);
	virtual void TerritoryMove(float delta_second);
	virtual void WeekendMove(float delta_second);
	virtual void ChaseMoment(float delta_second);
	virtual void RunMoment(float delta_second);
	virtual void AnimationControl(float delta_second);
};