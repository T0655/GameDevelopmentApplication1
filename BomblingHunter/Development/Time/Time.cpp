#include "Time.h"

//タイム初期化
int Time::timer = 0;

Time::Time()
{
	timer++;
}
Time::~Time()
{
	timer--;
}
//初期化処理
void Time::Initialize()
{

}
//更新処理
void Time::Update()
{

}
//描画処理
void Time::Draw()
{

}
//終了時処理
void Time::Finalize()
{

}
