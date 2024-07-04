#pragma once

#include "../GameObject.h"


class EnemyBase : public GameObject
{
private:
	enum eEnemyState
	{
		WAIT,		// 待機状態
		MOVE,		// 移動状態
		DIE,		// 死亡状態
	};
private:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> dying_animation;		// 死亡のアニメーション画像
	std::vector<int> eye_animation;		    // 目だけの状態のアニメーション画像
	Vector2D old_location;					// 前回のlocation
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;				// プレイヤー状態
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	int is_destroy;


	// 移動アニメーションの順番
	const int animation_num[4] = { 0, 1, 2, 1, };

protected:

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

private:
	void Movement(float delta_second);
	void AnimationControl(float delta_second);
};