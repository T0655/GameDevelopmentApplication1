#pragma once

#include "../GameObjects.h"

class Bomb : public GameObject
{
public:
	int bomb_hit_se;            //ヒットSE
	int bomb_image;             //爆弾画像
	int ex_image;               //エフェクト
	int effect_count;           //エフェクトカウント
	int bomb_effect[3];         //エフェクト画像
	Vector2D direction;         //進行方向

public:
	Bomb();
	~Bomb();

	void Initialize();         //初期化処理
	void Update();             //更新処理
	void Draw() const;         //描画処理
	void Finalize();           //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();           //移動処理
	void EffectControl();      //エフェクト処理
};

