#include "InputControl.h"
#include"DxLib.h"

//現在の入力情報
char InputControl::now_key[D_KEYCODE_MAX] = {};

//前フレームの入力情報
char InputControl::old_key[D_KEYCODE_MAX] = {};

//更新処理
void InputControl::Update()
{
	//前フレームの入力情報に現在の入力情報をコピーする
	memcpy(old_key, now_key, (sizeof(char) * D_KEYCODE_MAX));

	GetHitKeyStateAll(now_key);
}

//十字キー(押し続けている時)
bool InputControl::GetKey(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) && (old_key[key_code] == TRUE));
}

//十字キー(押した瞬間)
bool InputControl::GetKeyDown(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == TRUE) && (old_key[key_code] == FALSE));
}

//十字キー(離した瞬間)
bool InputControl::GetKeyUp(int key_code)
{
	return CheckKeyCodeRange(key_code) && ((now_key[key_code] == FALSE) && (old_key[key_code] == TRUE));
}

//キー配列範囲チェック
bool InputControl::CheckKeyCodeRange(int key_code)
{
	return (0 <= key_code && key_code < D_KEYCODE_MAX);
}