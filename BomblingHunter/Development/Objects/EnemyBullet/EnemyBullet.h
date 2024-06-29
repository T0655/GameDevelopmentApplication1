#pragma once

#include "../GameObjects.h"

class EnemyBullet : public GameObject
{
public:
	int em_se;               //サウンド
	int em_effect[4];        //エフェクト
	int effect_count;        //エフェクトカウント
	Vector2D direction;      //進行方向

public:
	EnemyBullet();
	~EnemyBullet();

	void Initialize();       //初期化処理
	void Update();           //更新処理
	void Draw() const;       //描画処理
	void Finalize();         //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private: 
	void Movement();        //移動処理
	void EffectControl();   //エフェクト処理
};

