//================================================================================
//
//    �e�N�X�`���I�u�W�F�N�g�N���X�w�b�_
//    Author : Araki Kai                                �쐬�� : 2017/12/18
//
//================================================================================

#ifndef	_TEXTURE_OBJECT_H_
#define _TEXTURE_OBJECT_H_



//======================================================================
//
// �C���N���[�h��
//
//======================================================================

#include <string>
#include <vector>

#include <Renderer\Renderer.h>



//======================================================================
//
// �N���X��`
//
//======================================================================

class TextureObject
{
//------------------------------------------------------------
private :
	// �e�N�X�`��UV
	struct TextureUV
	{
		float u0;
		float v0;
		float u1;
		float v1;
	};


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�t�H���g�R���X�g���N�^
	TextureObject(const std::string* file_path, int pattern_num_all = 1, int pattern_num_width = 1, 
				  int pattern_num_height = 1);


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// �f�X�g���N�^
	virtual ~TextureObject();

	
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
public :
	// ���J�����o�֐�
	int GetTexturePatternNum(const int animation_count, int animation_speed);

	int				   GetWidth()         const {return width_;           }
	int				   GetHeight()        const {return height_;          }
	int				   GetPatternNumAll() const {return pattern_num_all_; }
	TextureUV		   GetUV(int index)   const {return texture_uv[index];}
	LPDIRECT3DTEXTURE9 GetHandler()       const {return texture_handler_; }


//------------------------------------------------------------
private :
	// ����J�����o�֐�
	void InputTexture         (const std::string* file_path);
	void SetTextureInformation(const std::string* file_path, const int* pattern_num_width, 
							   const int* pattern_num_height);

	
//------------------------------------------------------------
private :
	// �����o�ϐ�
	int width_;
	int height_;
	int pattern_num_all_;

	std::vector<TextureUV> texture_uv;
	LPDIRECT3DTEXTURE9     texture_handler_;
};



#endif