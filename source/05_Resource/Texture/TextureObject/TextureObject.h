//================================================================================
//!	@file	 TextureObject.h
//!	@brief	 テクスチャオブジェクトClass
//! @details 
//!	@author  Kai Araki									@date 2018/11/01
//================================================================================
#ifndef	_TEXTURE_OBJECT_H_
#define _TEXTURE_OBJECT_H_



//****************************************
// インクルード文
//****************************************
#include <string>
#include <vector>

#include <Renderer\Renderer.h>
#include <Vector3D.h>



//************************************************************														   
//! @brief   テクスチャオブジェクトClass
//!
//! @details テクスチャのオブジェクトClass
//************************************************************
class TextureObject
{
//====================
// クラス定義
//====================
public:
	//****************************************											   
	//! @brief   UVClass
	//!
	//! @details UVのClass
	//****************************************
	class UV
	{
	//====================
	// 変数
	//====================
	private:
		Vec2 left_up_uv_;		//!< 左上UV
		Vec2 right_bottom_uv_;	//!< 右下UV


	//====================
	// プロパティ
	//====================
	public:
		//----------------------------------------
		//! @brief 左上U成分取得関数
		//! @details
		//! @param void なし
		//! @retval float* 左上U成分
		//----------------------------------------
		float* getpLeftUpU();

		//----------------------------------------
		//! @brief 左上V成分取得関数
		//! @details
		//! @param void なし
		//! @retval float* 左上V成分
		//----------------------------------------
		float* getpLeftUpV();

		//----------------------------------------
		//! @brief 右下U成分取得関数
		//! @details
		//! @param void なし
		//! @retval float* 右下U成分
		//----------------------------------------
		float* getpRightButtomU();

		//----------------------------------------
		//! @brief 右下V成分取得関数
		//! @details
		//! @param void なし
		//! @retval float* 右下V成分
		//----------------------------------------
		float* getpRightButtomV();
	};


//====================
// 変数
//====================
private:
	int width_;										//!< 幅
	int height_;									//!< 高さ
	int division_num_;								//!< 分割数
	std::vector<UV> uv_;							//!< UV配列
	LPDIRECT3DTEXTURE9 texture_handler_ = nullptr;	//!< テクスチャハンドラ
	std::string map_key_name_;						//!< マップ用キー名
	int reference_counter_ = 0;						//!< 参照カウンタ


//====================
// プロパティ
//====================
public:
	//----------------------------------------
	//! @brief 幅取得関数
	//! @details
	//! @param void なし 
	//! @retval int 幅
	//----------------------------------------
	int	getWidth();

	//----------------------------------------
	//! @brief 高さ取得関数
	//! @details
	//! @param void なし 
	//! @retval int 高さ
	//----------------------------------------
	int	getHeight();

	//----------------------------------------
	//! @brief 分割数取得関数
	//! @details
	//! @param void なし 
	//! @retval int 分割数
	//----------------------------------------
	int getDivisionNum();

	//----------------------------------------
	//! @brief 分割数設定関数
	//! @details
	//! @param division_num        分割数
	//! @param division_num_width  横の分割数
	//! @param division_num_height 縦の分割数
	//! @retval void なし
	//----------------------------------------
	void setDivisionNum(int division_num, int division_num_width,
						int division_num_height);

    //----------------------------------------
    //! @brief UV取得関数
    //! @details
    //! @param index インデックス 
    //! @retval UV* UV
    //----------------------------------------
	UV* getpUV(int index);

	//----------------------------------------
	//! @brief テクスチャハンドラ取得関数
	//! @details
	//! @param void なし 
	//! @retval LPDIRECT3DTEXTURE9 テクスチャハンドラ
	//----------------------------------------
	LPDIRECT3DTEXTURE9 getpHandler();

	//----------------------------------------
	//! @brief アニメーション数設定関数
	//! @details
	//! @param animation_count アニメーションカウンタ
	//! @param animation_speed アニメーション速度
	//! @retval int アニメーション数
	//----------------------------------------
	int getAnimationNum(int animation_count, int animation_speed);


//====================
// 関数
//====================
public:
	//----------------------------------------
	//! @brief 初期化関数
	//! @details
	//! @param *file_path    ファイルパス
	//! @param *map_key_name マップ用キー名
	//! @retval void なし
	//----------------------------------------
	void Init(std::string* file_path, const std::string* map_key_name);

	//----------------------------------------
	//! @brief 解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void Release();

	//----------------------------------------
	//! @brief 強制解放関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void ForcedRelease();

	//----------------------------------------
	//! @brief 参照カウンタ追加関数
	//! @details
	//! @param void なし
	//! @retval void なし
	//----------------------------------------
	void AddReferenceCounter();

private:
	//----------------------------------------
	//! @brief テクスチャハンドラ生成関数
	//! @details
	//! @param *file_path ファイルパス
	//! @retval void なし
	//----------------------------------------
	void CreateTextureHandler(std::string* file_path);

	//----------------------------------------
	//! @brief テクスチャ情報生成関数
	//! @details
	//! @param *file_path ファイルパス
	//! @retval void なし
	//----------------------------------------
	void CreateTextureInformation(std::string* file_path);
};



#endif