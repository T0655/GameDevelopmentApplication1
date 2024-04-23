#pragma once

/*
絶対値に変換
説明 引数の数字を絶対値に変換するテンプレート
引数 T value 変換する値
戻り値 T 変換後の値
*/
template<typename T>
T Abs(T value)
{
	T result;

	if (value > 0)
	{
		//valueが正の値
		result = value;
	}
	else
	{
		//valueが負の値
		result = -value;
	}

	return result;
}

/*
最大値を返すテンプレートの関数
説明　引数で指定された二つの値の最大値を返す
引数　T a 計算用データ　T b 計算用データ
戻り値　T　最大値
*/
template <typename T>
T Max(T a, T b)
{
	T result;

	//値が大きい方をresultに設定
	if (a < b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}

/*
最小値を返すテンプレートの関数
説明　引数で指定された二つの値の最小値を返す
引数　T a 計算用データ　T b 計算用データ
戻り値　T　最大値
*/
template <typename T>
T Min(T a, T b)
{
	T result;

	//値が小さい方をresultに設定
	if (a > b)
	{
		result = b;
	}
	else
	{
		result = a;
	}

	return result;
}
