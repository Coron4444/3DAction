//================================================================================
//
//    シーン基底クラス
//    Author : Araki Kai                                作成日 : 2018/11/02
//
//================================================================================

#ifndef	_SCENE_BASE_H_
#define _SCENE_BASE_H_



//****************************************
// インクルード文
//****************************************
#include <SafeRelease/SafeRelease.h>



//****************************************
// クラス宣言
//****************************************
class SceneManager;



/*********************************************************//**
* @brief
* シーン基底クラス
*
* シーンの基底クラス
*************************************************************/
class SceneBase
{
/***************************//**
* @brief
* シーンステート抽象クラス
*
* シーンステートの抽象クラス
*******************************/
public:
	class StateAbstract
	{
	//==============================
	// 非静的メンバ変数
	//==============================
	protected:
		SceneBase* scene_ = nullptr;		//!< シーン


	//==============================
	// 非静的メンバ関数
	//==============================
	public:
		/**
		* @brief
		* デストラクタ
		*/
		virtual ~StateAbstract() {}

		/**
		* @brief
		* 初期化関数
		*/
		virtual void Init() = 0;

		/**
		* @brief
		* 終了関数
		*/
		virtual void Uninit() = 0;

		/**
		* @brief
		* 更新関数
		*/
		virtual void Update() = 0;

		/**
		* @brief
		* リセット関数
		*/
		virtual void Reset() = 0;

		// プロパティ
		void SetScene(SceneBase* value) { scene_ = value; }
	};



//==============================
// 非静的メンバ変数
//==============================
private:
	SceneManager* scene_manager_ = nullptr;		//!< シーンマネージャ
	StateAbstract* state_ = nullptr;			//!< ステート



//==============================
// 非静的メンバ関数
//==============================
public:
	/**
	* @brief
	* コンストラクタ
	* @param
	* state : 最初のステート
	*/
	SceneBase(StateAbstract* state)
	{
		state_ = state;
		state_->SetScene(this);
	}

	/**
	* @brief
	* 仮想デストラクタ
	*/
	virtual ~SceneBase() {}

	/**
	* @brief
	* 初期化関数
	*/
	void Init();

	/**
	* @brief
	* 終了関数
	*/
	void Uninit();

	/**
	* @brief
	* 更新関数
	*/
	void Update();

	/**
	* @brief
	* リセット関数
	*/
	void Reset();

	/**
	* @brief
	* ステート解放関数
	*/
	void ReleaseState();

	// プロパティ
	SceneManager* GetSceneManager() { return scene_manager_; }
	void SetSceneManager(SceneManager* value) { scene_manager_ = value; }
	StateAbstract* GetState() { return state_; }
	void SetState(StateAbstract* value)
	{
		if (state_ != nullptr)
		{
			SafeRelease::PlusUninit(&state_);
		}

		state_ = value;

		if (state_ != nullptr)
		{
			state_->SetScene(this);
			state_->Init();
		}
	}
};



#endif