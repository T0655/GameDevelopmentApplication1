#pragma once

#include "../GameObject.h"

class Player
{
private:
	//�A�j���[�V�����摜
	int animation[2];
	//�A�j���[�V��������
	int animation_count;
	//���]�t���O
	int flip_flag;

public:
	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//����������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update() override;
	//�`�揈��
	virtual void Draw()const override;
	//�I��������
	virtual void Finalize() override;

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();
};

