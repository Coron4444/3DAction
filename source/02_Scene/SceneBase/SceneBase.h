//================================================================================
//!	@file	 SceneBase.h
//!	@brief	 シーンBaseClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/02
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



//************************************************************														   
//! @brief   シーンBaseClass
//!
//! @details シーンのBaseClass
//************************************************************
class SceneBase
{
//****************************************														   
//! @brief   シーンステートBaseClass
//!
//! @details シーンステートのBaseClass
//****************************************
public:
	class StateBase
	{
	//====================
	// 変数
	//====================
	protected:
		SceneBase* scene_ = nullptr;		//!< シーン


	//====================
	// 関数
	//====================
	public:
		//----------------------------------------
		//! @brief 仮想デストラクタ
		//! @param void なし
		//----------------------------------------
		virtual ~StateBase() {}

		//----------------------------------------
		//! @brief 初期化関数
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Init() = 0;

		//----------------------------------------
		//! @brief 終了関数
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Uninit() = 0;

		//----------------------------------------
		//! @brief 更新関数
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Update() = 0;

		//----------------------------------------
		//! @brief リセット関数
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		virtual void Reset() = 0;

		// プロパティ
		void setScene(SceneBase* value) { scene_ = value; }
	};


//====================
// 変数
//====================
private:
	SceneManager* scene_manager_ = nullptr;		//!< シーンマネージャ
	StateBase* state_ = nullptr;				//!< ステート


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief コンストラクタ
	//! @param[in] state 最初のステート
	//----------------------------------------
	SceneBase(StateBase* state) 
	{
		state_ = state;
		state_->setScene(this);
	}

	//----------------------------------------
	//! @brief 仮想デストラクタ
	//! @param void なし
	//----------------------------------------
	virtual ~SceneBase() {}

	//----------------------------------------
	//! @brief 初期化関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Init();

	//----------------------------------------
	//! @brief 終了関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Uninit();

	//----------------------------------------
	//! @brief 更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Update();

	//----------------------------------------
	//! @brief リセット関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Reset();

	//----------------------------------------
	//! @brief ステート解放関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ReleaseState();

	// プロパティ
	SceneManager* getpSceneManager() { return scene_manager_; }
	void setSceneManager(SceneManager* value) { scene_manager_ = value; }
	StateBase* getpState() { return state_; }
	void setState(StateBase* value)
	{
		if (state_ != nullptr)
		{
			SafeRelease::PlusUninit(&state_);
		}

		state_ = value;

		if (state_ != nullptr)
		{
			state_->setScene(this);
			state_->Init();
		}
	}
};



#endif