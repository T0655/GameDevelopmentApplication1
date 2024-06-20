#pragma once

#include"../Objects/GameObjects.h"
#include<vector>


class Scene
{
private:
	std::vector<GameObject*>objects;    //オブジェクトリスト
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
	//当たり判定チェックt処理
	void HitCheckObject(GameObject* a, GameObject* b);
	
	//オブジェクト生成処理
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw("GameObjectが生成できませんでした\n");
		}

		//初期化処理
		new_object->Initialize();
		//位置情報の設定
		new_object->SetLocation(location);

		//オブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}

	// オブジェクト削除処理
	template<class T>
	T* DeleteObject(const Vector2D& location)
	{
		//指定したクラスを削除する
		T* delete_instance = delete T();
		//GameObjectクラスを継承しているか確認
		GameObject* delete_object = dynamic_cast<GameObject*>(delete_instance);

		//エラーチェック
		if (delete_object == nullptr)
		{
			delete delete_instance;
			throw("GameObjectが生成できませんでした\n");
		}

		//オブジェクトリストに追加
		objects.push_back(delete_object);

		//インスタンスのポインタを返却
		return delete_instance;
	}
};