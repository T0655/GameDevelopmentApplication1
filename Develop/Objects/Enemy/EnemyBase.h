#pragma once

#include "../GameObject.h"

class EnemyBase : public GameObject
{
protected:
/*//エネミーの状態
enum eEnemyState
{
	IDLE,		// 待機状態
	MOVE,		// 移動状態
	DIE,		// 死亡状態
};



public:
	std::vector<int> move_animation;		// 移動のアニメーション画像
	std::vector<int> dying_animation;		// イジケ状態のアニメーション画像
	std::vector<int> eye_animation;         // 目だけの状態のアニメーション画像
 	Vector2D old_location;					// 前回のlocation
	Vector2D velocity;						// 移動量
	eEnemyState enemy_state;				// プレイヤー状態
	float animation_time;					// アニメーション時間
	int animation_count;					// アニメーション添字
	bool is_destroy;						// 死んだ状態になったか？

	// 移動アニメーションの順番
	const int animation_num[4] = { 0, 1, 2, 1, };


	static int enemy_time;
	*/
public:
	EnemyBase();
	virtual ~EnemyBase();

/**	virtual void Initialize();
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D& screen_offset) const override;
	virtual void Finalize() override;

	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	eEnemyState GetPlayerState() const;

	bool GetPowerUp() const;
	void SetPowerDown();
	bool GetDestroy() const;


private:
	void Movement(float delta_second);
	void AnimationControl(float delta_second);*/
};