#pragma once

#include "../GameObjects.h"

class EnemyBullet : public GameObject
{
public:
	int em_se;               //�T�E���h
	int em_effect[4];        //�G�t�F�N�g
	int effect_count;        //�G�t�F�N�g�J�E���g
	Vector2D direction;      //�i�s����

public:
	EnemyBullet();
	~EnemyBullet();

	void Initialize();       //����������
	void Update();           //�X�V����
	void Draw() const;       //�`�揈��
	void Finalize();         //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private: 
	void Movement();        //�ړ�����
	void EffectControl();   //�G�t�F�N�g����
};

