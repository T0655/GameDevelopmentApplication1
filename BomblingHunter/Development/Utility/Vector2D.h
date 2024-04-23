#pragma once

//2次元ベクトルクラス
class Vector2D
{
public:
	//X座標
	float x;
	//Y座標
	float y;

public:
	//コンストラクタ
	Vector2D();
	Vector2D(float scalar);
	Vector2D(float mx, float my);
	//デストラクタ
	~Vector2D();

public:
	//演算子オーバーロード
	//代入演算
	Vector2D& operator = (const Vector2D& location);

	//加算
	const Vector2D operator + (const Vector2D& location) const;
	Vector2D& operator +=(const Vector2D& location);

	//減算
	const Vector2D operator - (const Vector2D& location) const;
	Vector2D& operator -=(const Vector2D& location);

	//乗算
	const Vector2D operator * (const float& scalar) const;
	const Vector2D operator * (const Vector2D& location) const;
	Vector2D& operator *=(const float& scalar);
	Vector2D& operator *=(const Vector2D& location);

	//除算
	const Vector2D operator / (const float& scalar) const;
	const Vector2D operator / (const Vector2D& location) const;
	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /= (const Vector2D& location);

public:
	//整数値にキャストする
	void ToInt(int* x, int* y)const;
};