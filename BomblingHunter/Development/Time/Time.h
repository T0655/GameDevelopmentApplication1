#pragma once

#include "../../Objects/GameObjects.h"

class Time : public GameObject
{
public:
	//�^�C�}�[
	static int timer;

public:
	Time();
	~Time();

	void Initialize();      //����������
	void Update();          //�X�V����
	void Draw();            //�`�揈��
	void Finalize();        //�I��������
};

