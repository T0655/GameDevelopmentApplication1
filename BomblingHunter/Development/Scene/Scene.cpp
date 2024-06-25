#include "Scene.h"
#include "../Objects/Player/Player.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Utility/InputControl.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Objects/Harpy/Harpy.h"
#include "../Objects/Enemy/GoldEnemy/GoldEnemy.h"
#include "../Objects/Enemy/FlyEnemy/FlyEnemy.h"
#include "../Objects/EnemyBullet/EnemyBullet.h"
#include "../Time/Time.h"
#include "../Score/Score.h"
#include "DxLib.h"
#include <time.h>
#include <math.h>


//�R���X�g���N�^
Scene::Scene() :objects(),scene_images(),scene_bgm(),tm_images(),score(),score_image(),high_score_image(), result_image_bad(),result_image_ok(), result_image_good(),result_image_perfect()
{
	num_image[0] = NULL;
	num_image[1] = NULL;
	num_image[2] = NULL;
	num_image[3] = NULL;
	num_image[4] = NULL;
	num_image[5] = NULL;
	num_image[6] = NULL;
	num_image[7] = NULL;
	num_image[8] = NULL;
	num_image[9] = NULL;
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
	//�摜
	scene_images = LoadGraph("Resource/images/�w�i.png");
	tm_images= LoadGraph("Resource/images/�^�C�}�[.png");
	result_image_bad= LoadGraph("Resource/images/BAD.png");
	result_image_ok= LoadGraph("Resource/images/OK.png");
	result_image_good= LoadGraph("Resource/images/GOOD.png");
	result_image_perfect= LoadGraph("Resource/images/Perfect.png");
	score_image = LoadGraph("Resource/images/�X�R�A.png");
	high_score_image = LoadGraph("Resource/images/�n�C�X�R�A.png");
	num_image[0] = LoadGraph("Resource/images/�X�R�A0.png");
	num_image[1] = LoadGraph("Resource/images/�X�R�A1.png");
	num_image[2] = LoadGraph("Resource/images/�X�R�A2.png");
	num_image[3] = LoadGraph("Resource/images/�X�R�A3.png");
	num_image[4] = LoadGraph("Resource/images/�X�R�A4.png");
	num_image[5] = LoadGraph("Resource/images/�X�R�A5.png");
	num_image[6] = LoadGraph("Resource/images/�X�R�A6.png");
	num_image[7] = LoadGraph("Resource/images/�X�R�A7.png");
	num_image[8] = LoadGraph("Resource/images/�X�R�A8.png");
	num_image[9] = LoadGraph("Resource/images/�X�R�A9.png");
	//����
	scene_bgm = LoadSoundMem("Resource/sounds/BGM_arrows.wav");
	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 60.0f));

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
		CreateObject<Enemy>(Vector2D(100.0f, 485.0f));
	}
	//E�L�[����������A�n�l�e�L�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_E))
	{
		CreateObject<FlyEnemy>(Vector2D(100.0f, 200.0f));
	}
	//C�L�[����������A���̃e�L�𐶐�����
	if (InputControl::GetKeyDown(KEY_INPUT_C))
	{
		CreateObject<GoldEnemy>(Vector2D(100.0f, 500.0f));
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
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->DeleteObjectFinalize() == TRUE)
		{
			this->objects.erase(objects.begin() + i);
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
	Enemy::count;
	FlyEnemy::count;
	Harpy::count;
	int num1 = rand() % 100 + 1;
	int num2 = rand() % 3 + 1;
	
	flame_count++;
	//�n�R�e�L
	if (flame_count > 120)
	{
		if (Enemy::count < 2)
		{
			if (num1 < 20) {
				CreateObject<Enemy>(Vector2D(-70.0f, 485.0f));
				CreateObject<Enemy>(Vector2D(1000.0f, 485.0f));
				flame_count = 0;
			}
		}
	}
	//�n�[�s�[
	if (flame_count > 120)
	{
		if (Harpy::count < 2)
		{
			if (num1 < 40)
			{
				CreateObject<Harpy>(Vector2D(-70.0f, 200.0f));
				CreateObject<Harpy>(Vector2D(880.0f, 400.0f));
				flame_count = 0;
			}
		}
	}
	//�n�l�e�L
	if (flame_count > 300)
	{
		if (FlyEnemy::count < 5)
		{
			if (num1<50)
			{
				CreateObject<FlyEnemy>(Vector2D(-70.0f, 300.0f));
				FlyEnemy::count++;
				flame_count = 0;
			}
			if (FlyEnemy::count > 1)
			{
				CreateObject<FlyEnemy>(Vector2D(880.0f, 200.0f));
				flame_count = 0;
			}
			if (FlyEnemy::count > 3)
			{
				CreateObject<FlyEnemy>(Vector2D(-70.0f, 400.0f));
				flame_count = 0;
			}
			if (FlyEnemy::count > 4)
			{
				CreateObject<FlyEnemy>(Vector2D(1100.0f, 400.0f));
				FlyEnemy::count++;
				flame_count = 0;
			}

		}
	}
}

//�`�揈��
void Scene::Draw()const
{
	//�w�i�̕`��
	DrawGraph(0,-120, scene_images, FALSE);
	//�^�C�}�[�̕`��
	DrawGraph(15, 542, tm_images, TRUE);
	//�X�R�A�̕`��
	DrawGraph(200, 560, score_image, TRUE);
	//�n�C�X�R�A�̕`��
	DrawGraph(500, 560, high_score_image, TRUE);
	//���ʒ���
	ChangeVolumeSoundMem(255 * 30 / 100, scene_bgm);
	//BGM
	PlaySoundMem(scene_bgm, DX_PLAYTYPE_LOOP,FALSE);

	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��`�揈��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

void Scene::Score()
{
	Score::score;
	if (Score::score < 1000)
	{
		DrawGraph(0, -120, result_image_bad, FALSE);
	}
	if (Score::score > 1200)
	{
		DrawGraph(0, -120, result_image_ok, FALSE);
	}
	if (Score::score > 1500)
	{
		DrawGraph(0, -120, result_image_good, FALSE);
	}
	if (Score::score > 2000)
	{
		DrawGraph(0, -120, result_image_perfect, FALSE);
	}
}

void Scene::Time()
{
	Time::timer;
	Time::timer--;
	if (Time::timer == 0)
	{
		Result();
	}

}

void Scene::Result()
{
	Score();
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