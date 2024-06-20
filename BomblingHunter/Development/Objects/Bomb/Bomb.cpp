#include"Bomb.h"
#include"../Player/Player.h"
#include "../Enemy/Enemy.h"
#include "../Enemy/FlyEnemy/FlyEnemy.h"
#include "../Harpy/Harpy.h"
#include"DxLib.h"

Bomb::Bomb(): bomb_image(0),direction(0.0f),ex_image(0),bomb_hit_se()
{
	bomb_effect[0] = NULL;
	bomb_effect[1] = NULL;
	bomb_effect[2] = NULL;
	bomb_effect[3] = NULL;
}

Bomb::~Bomb() 
{

}

//����������
void Bomb::Initialize()
{
	//���e�摜�E�G�t�F�N�g
	bomb_effect[0] = LoadGraph("Resource/images/���e.png");
	bomb_effect[1] = LoadGraph("Resource/images/����1.png");
	bomb_effect[2] = LoadGraph("Resource/images/����2.png");
	bomb_effect[3] = LoadGraph("Resource/images/����3.png");
	//���j��
	bomb_hit_se = LoadSoundMem("Resource/sounds/explosion.wav");
	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, 2.0f);

	bomb_image = bomb_effect[0];
}

//�X�V����
void Bomb::Update()
{
	Movement();
}

//�`�揈��
void Bomb::Draw() const
{
    DrawRotaGraphF(location.x, location.y, 1.0, radian, bomb_image, TRUE);
}

void Bomb::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(bomb_image);
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	if (!(dynamic_cast<Player*>(hit_object) != nullptr))
	{
		delete_flag = TRUE;
	}
	//�n�R�e�L�ɓ���������
	if (dynamic_cast<Enemy*>(hit_object) != nullptr)
	{
		Enemy::count--;
	}
	//�n�[�s�[�ɓ���������
	if (dynamic_cast<Harpy*>(hit_object) != nullptr)
	{
		Harpy::count--;
	}
	//�n�l�e�L�ɓ���������
	if (dynamic_cast<FlyEnemy*>(hit_object) != nullptr)
	{
		FlyEnemy::count--;
	}
}

//�ړ�����
void Bomb::Movement()
{

	if (((location.y + direction.y) < box_size.y))
	{
		direction.y *= -1.0f;
	}

	if (location.y == 480.0f)
	{
		Finalize();
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

void Bomb::EffectControl()
{
	//�t���[���J�E���g�����Z����
	effect_count++;

	//60�t���[���ڂɓ��B������
	if (effect_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		effect_count = 0;

		//�摜�̐؂�ւ�
		if (bomb_image == bomb_effect[0])
		{
			bomb_image = bomb_effect[2];
		}
		else
		{
			bomb_image = bomb_effect[0];
		}
	}
}