#pragma once

#include "../GameObjects.h"

class Bomb : public GameObject
{
public:
	int bomb_hit_se;            //�q�b�gSE
	int bomb_image;             //���e�摜
	int ex_image;               //�G�t�F�N�g
	int effect_count;           //�G�t�F�N�g�J�E���g
	int bomb_effect[3];         //�G�t�F�N�g�摜
	Vector2D direction;         //�i�s����

public:
	Bomb();
	~Bomb();

	void Initialize();         //����������
	void Update();             //�X�V����
	void Draw() const;         //�`�揈��
	void Finalize();           //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

private:
	void Movement();           //�ړ�����
	void EffectControl();      //�G�t�F�N�g����
};

