#pragma once

#include "../../GameObjects.h"

class GoldEnemy : public GameObject
{
private:
	int hit_se;
	int animation[5];             //�A�j���[�V�����摜
	int animation_count;          //�A�j���[�V��������
	Vector2D direction;           //�i�s����

public:
	static int count;


public:
	GoldEnemy();
	~GoldEnemy();

	virtual void Initialize()override;        //����������
	virtual void Update()override;            //�X�V����
	virtual void Draw()const override;        //�`�揈��
	virtual void Finalize() override;         //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();
};

