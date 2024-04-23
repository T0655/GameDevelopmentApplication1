#pragma once

#include"../Objects/GameObject.h"
#include<vector>

class Scene
{
private:
	std::vector<GameObject*>objects;      //オブジェクトリスト
	
public:
	//コンストラクタ
	Scene();
	//デストラクタ
	~Scene();

	//初期化処理
	void Initialize();
	//更新処理
	void Update();
	//描画処理
	void Draw()const;
	//終了時処理
	void Finalize();
private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);

	//オブジェクト生成処理
	template<class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定されたクラスのオブジェクトを生成する
		T* new_instance = new T();
		//GameObjectが継承されているか確認する
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw("GameObjectが生成できませんでした。\n");
		}

		//初期化処理
		new_object->Initialize();

		//位置情報の設定
		new_object->SetLocation(location);

		//シーン内に存在するオブジェクトリストに追加
		objects.push_back(new_object);

		//生成したオブジェクトのポインタを返却
		return new_instance;
	}
};

