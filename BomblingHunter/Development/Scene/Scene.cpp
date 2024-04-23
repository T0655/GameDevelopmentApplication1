#include "Scene.h"
#include"../Objects/Player/Player.h"
#include"../Objects/Enemy/Enemy.h"
#include"../Utility/InputControl.h"
#include"DxLib.h"

#define D_PIVOT_CENTER

Scene::Scene() : objects()
{
}

Scene::~Scene()
{
	//����Y��h�~
	Finalize();
}

void Scene::Initialize()
{
	//�v���C���[����ʒ���������ɐ�������
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
}

void Scene::Initialize()
{
	//�v���C���[����ʒ���������ɐ�������
	CreateObject<Player>(Vector2D(320.0f, 240.0f));
}

void Scene::Update()
{
	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
}
