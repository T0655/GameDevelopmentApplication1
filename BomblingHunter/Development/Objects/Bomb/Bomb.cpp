#include"Bomb.h"
#include"../Player/Player.h"
#include"DxLib.h"

Bomb::Bomb(): bomb_image(0),direction(0.0f),ex_image(0),bomb_hit_se()
{
}

Bomb::~Bomb() 
{

}

//����������
void Bomb::Initialize()
{
    bomb_image = LoadGraph("Resource/images/���e.png");

	bomb_hit_se = LoadSoundMem("Resource/sounds/explosion.wav");
	//�����i�s�����̐ݒ�
	direction = Vector2D(0.0f, 2.0f);
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
	if (!(dynamic_cast<Player*>(hit_object)))
	{
		Finalize();
	}
}

//�ړ�����
void Bomb::Movement()
{

	if (((location.y + direction.y) < box_size.y))
	{
		direction.y *= -1.0f;
	}

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}
