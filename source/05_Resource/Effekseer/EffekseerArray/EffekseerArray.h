//================================================================================
//
//    エフェクシア配列クラス
//    Author : Araki Kai                                作成日 : 2018/09/01
//
//================================================================================

#ifndef	_EFFEKSEER_ARRAY_H_
#define _EFFEKSEER_ARRAY_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>
#include <vector>
#include <list>

#include "../EffekseerObject/EffekseerObject.h"



//======================================================================
//
// クラス定義
//
//======================================================================

class EffekseerArray
{
//------------------------------------------------------------
private :
	static const unsigned DISPOSABLE_ARRAY_NUM;
	static const unsigned REFERENCE_ARRAY_NUM;



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// コンストラクタ
	EffekseerArray(const std::string* file_path);

	// デストラクタ
	~EffekseerArray();



//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	void Update(Effekseer::Matrix44* projection_matrix, Effekseer::Matrix44* view_matrix);
	void Draw();

	// 使い捨てエフェクシアオブジェクトの作成
	void CreateDisposableEffekseerObject(Vec3 position, Vec3 scale);
	
	// 参照オブジェクトの取得
	EffekseerObject* GetReferenceEffekseerObject();


//------------------------------------------------------------
private :
	void UpdateList();


//------------------------------------------------------------
private :
	// 使い捨てエフェクシアオブジェクト
	std::vector<EffekseerObject*> disposable_effekseer_array_;
	std::list<EffekseerObject*>   disposable_effekseer_list_;

	// 参照エフェクシアオブジェクト
	std::vector<EffekseerObject*> reference_effekseer_array_;
	unsigned next_reference_index_;
};



#endif