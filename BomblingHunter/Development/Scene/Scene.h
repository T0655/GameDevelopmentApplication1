#pragma once

#include"../Objects/GameObjects.h"
#include<vector>


class Scene
{
private:
	std::vector<GameObject*>objects;    //�I�u�W�F�N�g���X�g
	int scene_images;
	int scene_bgm;
	int tm_images;
	int score;
	int get_random;
	int DeleteObjFn;
	int flame_count;



public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Score();
	void Time();
	void Finalize();

private:
	//�����蔻��`�F�b�Nt����
	void HitCheckObject(GameObject* a, GameObject* b);
	
	//�I�u�W�F�N�g��������
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw("GameObject�������ł��܂���ł���\n");
		}

		//����������
		new_object->Initialize();
		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}

	// �I�u�W�F�N�g�폜����
	template<class T>
	T* DeleteObject(const Vector2D& location)
	{
		//�w�肵���N���X���폜����
		T* delete_instance = delete T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* delete_object = dynamic_cast<GameObject*>(delete_instance);

		//�G���[�`�F�b�N
		if (delete_object == nullptr)
		{
			delete delete_instance;
			throw("GameObject�������ł��܂���ł���\n");
		}

		//�I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(delete_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return delete_instance;
	}
};