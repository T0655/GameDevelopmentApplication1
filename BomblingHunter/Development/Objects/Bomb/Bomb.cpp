#include"Bomb.h"
#include"DxLib.h"

Bomb::Bomb(): Bomb_image(0),direction(0.0f)
{

}

Bomb::~Bomb() 
{

}

//����������
void Bomb::Initialize()
{
    Bomb_image = LoadGraph("Resource/images/���e.png");
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
    DrawRotaGraphF(location.x, location.y, 1.0, radian, Bomb_image, TRUE);
}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//�����������̏���
	direction = 0.0f;

	DeleteGraph(Bomb_image);
}

void Bomb::Speed()
{

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
