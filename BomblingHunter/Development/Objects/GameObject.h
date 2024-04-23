#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER   //座標の原点を画像の中心にする

//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	//位置情報
	Vector2D location;
	//大きさ
	Vector2D box_size;
	//向き
	double radian;
	//画像
	int image;
	//音源
	int sound;

public:
	//コンストラクタ
	GameObject();
	//デストラクタ
	virtual ~GameObject();

	//初期化処理
	virtual void Initialize();
	//更新処理
	virtual void Update();
	//描画処理
	virtual void Draw() const;
	//終了時処理
	virtual void Finalize();

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//位置情報取得処理
	Vector2D GetLocation() const;
	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;
};

