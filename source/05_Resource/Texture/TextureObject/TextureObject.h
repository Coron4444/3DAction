//================================================================================
//
//    テクスチャオブジェクトクラスヘッダ
//    Author : Araki Kai                                作成日 : 2017/12/18
//
//================================================================================

#ifndef	_TEXTURE_OBJECT_H_
#define _TEXTURE_OBJECT_H_



//======================================================================
//
// インクルード文
//
//======================================================================

#include <string>
#include <vector>

#include <Renderer\Renderer.h>



//======================================================================
//
// クラス定義
//
//======================================================================

class TextureObject
{
//------------------------------------------------------------
private :
	// テクスチャUV
	struct TextureUV
	{
		float u0;
		float v0;
		float u1;
		float v1;
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デフォルトコンストラクタ
	TextureObject(const std::string* file_path, int pattern_num_all = 1, int pattern_num_width = 1, 
				  int pattern_num_height = 1);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// デストラクタ
	virtual ~TextureObject();

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// 公開メンバ関数
	int GetTexturePatternNum(const int animation_count, int animation_speed);

	int				   GetWidth()         const {return width_;           }
	int				   GetHeight()        const {return height_;          }
	int				   GetPatternNumAll() const {return pattern_num_all_; }
	TextureUV		   GetUV(int index)   const {return texture_uv[index];}
	LPDIRECT3DTEXTURE9 GetHandler()       const {return texture_handler_; }


//------------------------------------------------------------
private :
	// 非公開メンバ関数
	void InputTexture         (const std::string* file_path);
	void SetTextureInformation(const std::string* file_path, const int* pattern_num_width, 
							   const int* pattern_num_height);

	
//------------------------------------------------------------
private :
	// メンバ変数
	int width_;
	int height_;
	int pattern_num_all_;

	std::vector<TextureUV> texture_uv;
	LPDIRECT3DTEXTURE9     texture_handler_;
};



#endif