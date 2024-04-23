#pragma once

#define D_KEYCODE_MAX (256) //キーボードの総数

class InputControl
{
private:
	//現在の入力情報
	static char now_key[D_KEYCODE_MAX];

	//前フレームの入力情報
	static char old_key[D_KEYCODE_MAX];

public:
	//更新処理
	static void Update();

	//キーを押し続けているとき
	static bool GetKey(int key_code);

	//キーを押した瞬間
	static bool GetKeyDown(int key_code);

	//キーを離した瞬間
	static bool GetKeyUp(int key_code);

private:
	//キー配列範囲チェック
	static bool CheckKeyCodeRange(int key_code);
};


