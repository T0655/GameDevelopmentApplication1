#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER   //���W�̌��_���摜�̒��S�ɂ���

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	//�ʒu���
	Vector2D location;
	//�傫��
	Vector2D box_size;
	//����
	double radian;
	//�摜
	int image;
	//����
	int sound;

public:
	//�R���X�g���N�^
	GameObject();
	//�f�X�g���N�^
	virtual ~GameObject();

	//����������
	virtual void Initialize();
	//�X�V����
	virtual void Update();
	//�`�揈��
	virtual void Draw() const;
	//�I��������
	virtual void Finalize();

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;
};

