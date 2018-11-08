//================================================================================
//
//    シーンマネージャクラスヘッダ
//    Author : Araki Kai                                作成日 : 2018/11/02
//
//================================================================================

#ifndef	_SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <Vector3D.h>

#include <ComponentManager\UpdateComponentManager\UpdateComponentManager.h>
#include <ComponentManager\DrawComponentManager\DrawComponentManager.h>
#include <ComponentManager\CollisionComponentManager\CollisionComponentManager.h>



//****************************************
// クラス宣言
//****************************************
class SceneBase;



/*********************************************************//**
* @brief
* シーンマネージャクラス
*
* シーンの管理をするクラス
*************************************************************/
class SceneManager
{
/***************************//**
* @brief
* シーン間共通データクラス
*
* シーン間での共通データを管理するクラス
*******************************/
public:
	class CommonData
	{
	//==============================
	// 非静的メンバ変数
	//==============================
	private:
		bool is_update_;		//!< 全体を更新するかフラグ
		bool is_clear_;			//!< ゲームをクリアしたかフラグ


	
	//==============================
	// 非静的メンバ関数
	//==============================
	public:
		/**
		* @brief
		* リセット関数
		*/
		void Reset()
		{
			is_update_ = false;
			is_clear_ = false;
		}

		// プロパティ
		bool GetIsUpdate() { return is_update_; }
		void SetIsUpdate(bool value) { is_update_ = value; }
		bool GetIsClear() { return is_clear_; }
		void SetIsClear(bool value) { is_clear_ = value; }
	};



//==============================
// 列挙型定義
//==============================
public:
	// ステート
	enum State
	{
		NONE = -1,
		CHANGE_SCENE,
		RESET_SCENE,
		MAX
	};



//==============================
// 定数
//==============================
private:
	static const Fade::Type DEFAULT_FADE_TYPE;
	static const float      DEFAULT_FADE_SPEED;
	static const XColor4    DEFAULT_FADE_COLOR;



//==============================
// 非静的メンバ変数
//==============================
private:
	State state_;					//!< シーンマネージャステート
	CommonData* common_data_;		//!< シーン間共通データ

	SceneBase* current_scene_;		//!< 現在のシーン
	SceneBase* next_scene_;			//!< 次のシーン

	Fade::Type fade_type_;			//!< フェードの種類
	float      fade_speed_;			//!< フェード速度
	XColor4    fade_color_;			//!< フェード色



//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* コンストラクタ
	* @param
	* scene : 最初のシーン
	*/
	SceneManager(SceneBase* scene);

	/**
	* @brief
	* デストラクタ
	*/
	~SceneManager();

	/**
	* @brief
	* 更新関数
	*/
	void Update();

	/**
	* @brief
	* シーンの更新関数
	*/
	void UpdateScene();

	/**
	* @brief
	* シーンの描画関数
	*/
	void DrawScene();

	/**
	* @brief
	* シーンのリセット関数
	*/
	void ResetScene();

	// プロパティ
	void SetNextScene(SceneBase* value);
	CommonData* GetCommonData() { return common_data_; }
	void SetFadeType(Fade::Type value) { fade_type_ = value; }
	void SetFadeSpeed(float value) { fade_speed_ = value; }
	void SetFadeColor(XColor4 value) { fade_color_ = value; }

private:
	void SceneChange();
	void SceneReset();
};



#endif