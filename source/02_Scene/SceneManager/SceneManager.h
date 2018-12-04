//================================================================================
//!	@file	 SceneManager.h
//!	@brief	 シーンマネージャClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_SCENE_MANAGER_H_
#define _SCENE_MANAGER_H_



//****************************************
// インクルード文
//****************************************
#include <GameObjectManager\GameObjectManager.h>

#include <Vector3D.h>



//****************************************
// クラス宣言
//****************************************
class SceneBase;



//************************************************************														   
//! @brief   シーンマネージャClass
//!
//! @details シーンのマネージャClass
//************************************************************
class SceneManager
{
//****************************************														   
//! @brief   シーン間共通データClass
//!
//! @details シーン間の共通データClass
//****************************************
public:
	class CommonData
	{
	//====================
	// 変数
	//====================
	private:
		bool is_update_;		//!< 全体を更新するかフラグ
		bool is_clear_;			//!< ゲームをクリアしたかフラグ


	//====================
	// 関数
	//====================
	public:
		//----------------------------------------
		//! @brief リセット関数
		//! @param void なし
		//! @retval void なし
		//----------------------------------------
		void Reset()
		{
			is_update_ = false;
			is_clear_ = false;
		}

		// プロパティ
		bool getIsUpdate() { return is_update_; }
		void setIsUpdate(bool value) { is_update_ = value; }
		bool getIsClear() { return is_clear_; }
		void setIsClear(bool value) { is_clear_ = value; }
	};


//====================
// 列挙型定義
//====================
public:
	// ステート
	enum State
	{
		NONE = -1,
		CHANGE_SCENE,
		RESET_SCENE,
		MAX
	};


//====================
// 定数
//====================
private:
	static const Fade::Type DEFAULT_FADE_TYPE;		//!< 初期フェードタイプ
	static const float      DEFAULT_FADE_SPEED;		//!< 初期フェード速度
	static const XColor4    DEFAULT_FADE_COLOR;		//!< 初期フェード色


//====================
// 変数
//====================
private:
	State state_ = State::NONE;				//!< シーンマネージャステート
	CommonData* common_data_ = nullptr;		//!< シーン間共通データ

	SceneBase* current_scene_ = nullptr;	//!< 現在のシーン
	SceneBase* next_scene_ = nullptr;		//!< 次のシーン

	Fade::Type fade_type_ = DEFAULT_FADE_TYPE;		//!< フェードの種類
	float fade_speed_ = DEFAULT_FADE_SPEED;			//!< フェード速度
	XColor4 fade_color_ = DEFAULT_FADE_COLOR;		//!< フェード色


//====================
// 非静的メンバ関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @param[in] scene 最初のシーン
	//! @retval void なし
	//----------------------------------------
	void Init(SceneBase* scene);

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
	//! @brief シーン更新関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void UpdateScene();

	//----------------------------------------
	//! @brief シーン描画関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void DrawScene();

	//----------------------------------------
	//! @brief シーンリセット関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ResetScene();

	// プロパティ
	void setNextScene(SceneBase* value);
	CommonData* getpCommonData() { return common_data_; }
	void setFadeType(Fade::Type value) { fade_type_ = value; }
	void setFadeSpeed(float value) { fade_speed_ = value; }
	void setFadeColor(XColor4 value) { fade_color_ = value; }

private:
	//----------------------------------------
	//! @brief シーン変更関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SceneChange();

	//----------------------------------------
	//! @brief シーンリセット関数
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void SceneReset();
};



#endif