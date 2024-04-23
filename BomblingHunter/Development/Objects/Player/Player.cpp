#include "Player.h"
#include"../../Utility/InputControl.h"
#include"../../Utility/UserTemplate.h"
#include "DxLib.h"

Player::Player() : velocity(0.0f)
{
}

Player::~Player()
{
}

void Player::Initialize()
{
	color = GetColor(255, 255, 255);
}
