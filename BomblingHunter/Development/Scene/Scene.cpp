#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Utility/InputControl.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Objects/Harpy/Harpy.h"
#include "../Objects/Enemy/GoldEnemy/GoldEnemy.h"
#include "../Objects/Enemy/FlyEnemy/FlyEnemy.h"
#include "../Objects/EnemyBullet/EnemyBullet.h"
#include "../Timer/Timer.h"
#include "DxLib.h"

//�R���X�g���N�^
Scene::Scene() :objects(),scene_images(),scene_bgm(),tm_images()
{
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	scene_images = LoadGraph("Resource/images/�w�i.png");
	tm_images= LoadGraph("Resource/images/�^�C�}�[.png");

	scene_bgm = LoadSoundMem("Resource/sounds/BGM_arrows.wav");
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 60.0f));
	//�n�R�e�L�𐶐�����
	CreateObject<Enemy>(Vector2D(100.0f, 500.0f));
}

//�X�V����
void Scene::Update()
{
	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���X�V����
	for (GameObject* obj : objects)
	{
		obj->Update();
	}
	

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i],objects[j]);
		}
	}
	//Q�L�[����������A�n�[�s�[�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_Q))
	{
		CreateObject<Harpy>(Vector2D(100.0f, 200.0f));
	}
	//Z�L�[����������A�n�R�e�L�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 500.0f));
	}
	//E�L�[����������A�n�l�e�L�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_E))
	{
		CreateObject<FlyEnemy>(Vector2D(100.0f, 200.0f));
	}
	//C�L�[����������A���̃e�L�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_C))
	{
		CreateObject<GoldEnemy>(Vector2D(100.0f, 510.0f));
	}
	//�X�y�[�X�L�[����������A�v���C���[�̈ʒu���甚�e�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		for (int i =0; i < objects.size(); i++)
		{
			if (!(dynamic_cast<Player*>(objects[i]) == nullptr))
			{
				CreateObject<Bomb>(objects[i]->GetLocation());
			}
		}
	}
	//G�L�[����������A�G�l�~�[�̈ʒu����G�e�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_G))
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (!(dynamic_cast<Enemy*>(objects[i]) == nullptr))
			{
				CreateObject<EnemyBullet>(objects[i]->GetLocation());
			}
		}
	}
}

//�`�揈��
void Scene::Draw()const
{
	//�w�i�̕`��
	DrawGraph(0,-120, scene_images, FALSE);
	DrawGraph(15, 542, tm_images, TRUE);

	
	

	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	StopSoundMem(scene_bgm);

	//���I�z��̊J��
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N����(��`�̒��S�œ����蔻������)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);

	}
}
#else

//�����蔻��`�F�b�N����(���㒸�_�̍��W���瓖���蔻��v�Z���s��)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->GetLocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->GetLocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) && (a->GetLocation().y < b_lower_right.y) && (a_lower_right.x > b->GetLocation().x) && (a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���Hit�����ʒm����
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}

#endif //D_PIVOT_CENTER