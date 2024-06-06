#include "EnemyBullet.h"
#include "../Player/Player.h"
#include "DxLib.h"

EnemyBullet::EnemyBullet() : em_image(0),direction(0.0f),em_se(),effect_count(0)
{
	em_effect[0] = NULL;
	em_effect[1] = NULL;
	em_effect[2] = NULL;
}

EnemyBullet::~EnemyBullet()
{

}

//����������
void EnemyBullet::Initialize()
{
	em_image = LoadGraph("Resource/images/�G�e1.png");
	em_effect[0] = LoadGraph("Resource/images/�G�e�G�t�F�N�g1.png");
	em_effect[1] = LoadGraph("Resource/images/�G�e�G�t�F�N�g2.png");
	em_effect[2] = LoadGraph("Resource/images/�G�e�G�t�F�N�g3.png");

	em_se = LoadSoundMem("Resource/sounds/bishi.wav");
	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, -2.0f);
}

//�X�V����
void EnemyBullet::Update()
{
	Movement();
}

//�`�揈��
void EnemyBullet::Draw() const
{
	DrawRotaGraphF(location.x, location.y, 1.0, radian, em_image, TRUE);
}

void EnemyBullet::Finalize()
{
	//�g�p�����摜���J������
	DeleteGraph(em_image);
}

//�����蔻��ʒm����
void EnemyBullet::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	if (dynamic_cast<Player*>(hit_object))
	{
		Finalize();
		box_size = 0.0f;
		PlaySoundMem(em_se, 0);
		EffectControl();
	}
}

//�ړ�����
void EnemyBullet::Movement()
{

	if (((location.y + direction.y) < box_size.y))
	{
		direction.y *= 1.0f;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
void EnemyBullet::EffectControl()
{
	//�t���[���J�E���g�����Z����
	effect_count++;

	//60�t���[���ڂɓ��B������
	if (effect_count >= 60)
	{
		//�J�E���g�̃��Z�b�g
		effect_count = 0;

		//�摜�̐؂�ւ�
		if (em_image == em_effect[0])
		{
			image = em_effect[1];
		}
		else
		{
			image = em_effect[0];
		}
	}
}
