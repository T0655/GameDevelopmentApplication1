#include "GoldEnemy.h"
#include "../../Bomb/Bomb.h"
#include "DxLib.h"

int GoldEnemy::count = 0;

GoldEnemy::GoldEnemy() : animation_count(0), direction(0.0f),hit_se()
{
	animation[0] = NULL;
	animation[1] = NULL;
	animation[2] = NULL;
	animation[3] = NULL;
	animation[4] = NULL;

}

GoldEnemy::~GoldEnemy()
{
	
}

//����������
void GoldEnemy::Initialize()
{
	//�摜�̓Ǎ���
	animation[0] = LoadGraph("Resource/Images/���̃e�L1.png");
	animation[1] = LoadGraph("Resource/Images/���̃e�L2.png");
	animation[2] = LoadGraph("Resource/Images/���̃e�L3.png");
	animation[3] = LoadGraph("Resource/Images/���̃e�L4.png");
	animation[4] = LoadGraph("Resource/Images/���̃e�L5.png");

	//BGM�ESE�ǂݍ���
	hit_se = LoadSoundMem("Resource/sounds/arrows_perfect03_short.wav");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("���̃e�L�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, 0.0f);
}

//�X�V����
void GoldEnemy::Update()
{
	//�ړ�����
	Movement();

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void GoldEnemy::Draw() const
{
	//�摜���]�t���O
	int flip_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//������Ƀn�R�e�L�摜��`�悷��
	DrawRotaGraphF(location.x, location.y, 1.0, radian, image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void GoldEnemy::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
	DeleteGraph(animation[2]);
	DeleteGraph(animation[3]);
	DeleteGraph(animation[4]);
}

//�����蔻��ʒm����
void GoldEnemy::OnHitCollision(GameObject* hit_object)
{
	if (dynamic_cast<Bomb*>(hit_object))
	{
		direction = 0.0f;
		Finalize();
		box_size = 0.0f;
		PlaySoundMem(hit_se, DX_PLAYTYPE_BACK);
	}
}

//�ړ�����
void GoldEnemy::Movement()
{
	if (((location.x + direction.x) < (-80.0f - box_size.x)) || (1040.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}
	if (((location.y + direction.y) < box_size.y) || (480.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�A�j���[�V��������
void GoldEnemy::AnimationControl()
{
	//�A�j���[�V�����J�E���g�����Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�̃��Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}
