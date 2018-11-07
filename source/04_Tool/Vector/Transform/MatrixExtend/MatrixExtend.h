//================================================================================
//
//    行列拡張クラス
//    Author : Araki Kai                                作成日 : 2018/08/16
//
//================================================================================

#ifndef	_MATRIX_EXTEND_H_
#define _MATRIX_EXTEND_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <d3dx9.h>
#include <Vector3D.h>



//======================================================================
//
// クラス定義
//
//======================================================================
/**
* @brief
* DirectX9の行列の拡張版クラス
*
* 各種行列が揃っています。
*/

class MatrixExtend
{
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	/** 
	* * @brief
	* デフォルトコンストラクタ
	*/
	MatrixExtend();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	/** デストラクタ */
	~MatrixExtend();


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	/**
	* @brief 平行移動行列の更新
	* @param position : 行列にしたい座標値
	*/ 
	void UpdateTranslationMatrix(const Vec3* position);
	
	/**
	* @brief  平行移動行列の取得
	* @return 行列のポインタを取得
	*/ 
	MATRIX* GetTranslationMatrix(){return &matrix_translation_;}
	
	/**
	* @brief 拡縮行列の更新
	* @param scale : 行列にしたい拡縮値
	*/
	void UpdateScaleMatrix(const Vec3* scale);

	/**
	* @brief  拡縮行列の取得
	* @return 行列のポインタを取得
	*/
	MATRIX* GetScaleMatrix(){return &matrix_scale_;}

	// 回転
	void UpdateRotationMatrix(const Quaternion* quaternion);
	MATRIX* GetRotationMatrix(){return &matrix_rotation_;}

	// 逆行列
	void UpdateInverseMatrix(const MATRIX* matrix);
	MATRIX* GetInverseMatrix(){return &matrix_inverse_;}
	
	// 転置行列
	void UpdateTransposeMatrix(const MATRIX* matrix);
	void TransposeMatrixTranslationOff();
	

	// ワールド行列
	void UpdateWorldMatrixSRT();
	void UpdateWorldMatrixISRT();
	MATRIX* GetWorldMatrix(){return &matrix_world_;}


	// 親のワールド行列を乗算
	void MultiplicationParentMatrix(const MATRIX* parent_matrix);


//------------------------------------------------------------
private :
	// リセット
	void ResetAllMatrix();
	void ResetTranslationMatrix();
	void ResetScaleMatrix();
	void ResetRotationMatrix();
	void ResetInverseMatrix();
	void ResetWorldMatrix();



//------------------------------------------------------------
private :
	// メンバ変数
	MATRIX matrix_translation_;
	MATRIX matrix_scale_;
	MATRIX matrix_rotation_;
	MATRIX matrix_inverse_;
	MATRIX matrix_world_;
};





//======================================================================
//
// 非静的メンバ関数定義( inline )
//
//======================================================================

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デフォルトコンストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline MatrixExtend::MatrixExtend() 
{
	ResetAllMatrix();
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ デストラクタ ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline MatrixExtend::~MatrixExtend() 
{

}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 平行行列更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateTranslationMatrix(const Vec3* position)
{
	D3DXMatrixTranslation(&matrix_translation_, position->x, position->y, position->z);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 拡縮行列更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateScaleMatrix(const Vec3* scale)
{
	D3DXMatrixScaling(&matrix_scale_, scale->x, scale->y, scale->z);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 回転行列更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateRotationMatrix(const Quaternion* quaternion)
{
	D3DXMatrixRotationQuaternion(&matrix_rotation_, quaternion);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 逆行列更新関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateInverseMatrix(const MATRIX* matrix)
{
	D3DXMatrixInverse(&matrix_inverse_, NULL, matrix);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 転置行列関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateTransposeMatrix(const MATRIX* matrix)
{
	D3DXMatrixTranspose(&matrix_inverse_, matrix);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ 転置行列の平行移動をOFFにする関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::TransposeMatrixTranslationOff()
{
	matrix_inverse_._14 = 0.0f;
	matrix_inverse_._24 = 0.0f;
	matrix_inverse_._34 = 0.0f;
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ワールド行列作成関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateWorldMatrixSRT()
{
	D3DXMatrixMultiply(&matrix_world_, &matrix_scale_, &matrix_rotation_);
	D3DXMatrixMultiply(&matrix_world_, &matrix_world_, &matrix_translation_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ワールド行列作成( 逆行列を含む )関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::UpdateWorldMatrixISRT()
{
	D3DXMatrixMultiply(&matrix_world_, &matrix_scale_, &matrix_rotation_);
	D3DXMatrixMultiply(&matrix_world_, &matrix_world_, &matrix_translation_);

	D3DXMatrixMultiply(&matrix_world_, &matrix_inverse_, &matrix_world_);
}



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// [ ワールド行列に親の行列を乗算する関数 ]
//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

inline void MatrixExtend::MultiplicationParentMatrix(const MATRIX* parent_matrix)
{
	D3DXMatrixMultiply(&matrix_world_, &matrix_world_, parent_matrix);
}



//--------------------------------------------------------------------------------
//
// [ 全ての行列のリセット関数 ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetAllMatrix()
{
	ResetTranslationMatrix();
	ResetScaleMatrix();
	ResetRotationMatrix();
	ResetInverseMatrix();
	ResetWorldMatrix();
}



//--------------------------------------------------------------------------------
//
// [ 平行行列リセット関数 ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetTranslationMatrix()
{
	D3DXMatrixIdentity(&matrix_translation_);
}



//--------------------------------------------------------------------------------
//
// [ 拡縮行列リセット関数 ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetScaleMatrix()
{
	D3DXMatrixIdentity(&matrix_scale_);
}



//--------------------------------------------------------------------------------
//
// [ 回転行列リセット関数 ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetRotationMatrix()
{
	D3DXMatrixIdentity(&matrix_rotation_);
}




//--------------------------------------------------------------------------------
//
// [ 逆行列リセット関数 ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetInverseMatrix()
{
	D3DXMatrixIdentity(&matrix_inverse_);
}



//--------------------------------------------------------------------------------
//
// [ ワールド行列リセット関数 ]
//
//--------------------------------------------------------------------------------

inline void MatrixExtend::ResetWorldMatrix()
{
	D3DXMatrixIdentity(&matrix_world_);
}



#endif