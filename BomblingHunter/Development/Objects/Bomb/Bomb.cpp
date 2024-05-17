#include"Bomb.h"
#include"DxLib.h"

Bomb::Bomb(): Bomb_image(0),direction(0.0f)
{

}

Bomb::~Bomb() 
{

}

void Bomb::Initialize()
{
    Bomb_image = LoadGraph("Resource/images/”š’e.png");
}

void Bomb::Update()
{
	Movement();
}

void Bomb::Draw() const
{
    DrawRotaGraphF(location.x, location.y, 1.0, radian, Bomb_image, TRUE);
}

void Bomb::Speed()
{
}

//ˆÚ“®ˆ—
void Bomb::Movement()
{
	if (((location.x + direction.x) < box_size.x) || (640.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}
	if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}

}
