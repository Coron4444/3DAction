//================================================================================
//
//    FBXモデルマネージャクラスヘッダ
//    Author : Araki Kai                                作成日 : 2018/01/21
//
//================================================================================

#ifndef	_MODEL_FBX_MANAGER_H_
#define _MODEL_FBX_MANAGER_H_



//**********************************************************************
//
// インクルード文
//
//**********************************************************************

#include <string>
#include <vector>
#include <unordered_map>



//**********************************************************************
//
// クラス定義
//
//**********************************************************************

class ModelFBXObject;
class TextureManager;



//**********************************************************************
//
// クラス定義
//
//**********************************************************************

class ModelFBXManager
{
// ============================================================
public :
	// コンストラクタ
	ModelFBXManager(TextureManager* texture_manager);


// ============================================================
public :
	// デストラクタ
	virtual ~ModelFBXManager();


// ============================================================
public :
	// メンバ変数
	void RegistrationModelFBXObject(const std::string* key_name, const std::string* file_path = nullptr);

	ModelFBXObject* GetModelFBXObject(const std::string* key_name);
	void SetModelFBXObject(const std::string* key_name);
	
	
// ============================================================
private :
	// メンバ変数
	std::unordered_map<std::string, ModelFBXObject*> model_map_;
	TextureManager*									 texture_manager_;
};



#endif