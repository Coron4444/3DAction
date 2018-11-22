//================================================================================
//
//    �����_���[�N���X
//    Author : Araki Kai                                �쐬�� : 2018/11/01
//
//================================================================================

#ifndef	_RENDERE_H_
#define _RENDERE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include "RendererInterface/RendererInterface.h"
#include "RendererFactory/RendererFactory.h"
#include "RendererDirectX9/RendererDirectX9.h"
#include <Vector3D.h>



/*********************************************************//**
* @brief
* �����_���[�N���X
*
* �����_���[�N���X
*************************************************************/
class Renderer
{
//==============================
// �񋓌^��`
//==============================
public:
	enum MODE
	{
		NONE = -1,
		DIRECTX9,
		DIRECTX11,
		OPEN_GL,
		MAX
	};


//==============================
// �ÓI�����o�ϐ�
//==============================
private:
	static Renderer* instance_;				//!< �C���X�^���X
	static RendererInterface* renderer_;	//!< �����_���[



//==============================
// �����o�ϐ�
//==============================
private:
	MODE mode_ = MODE::NONE;		//!< ���[�h



//==============================
// �ÓI�����o�֐�
//==============================
public:
	static Renderer* GetInstance();
	static void ReleaseInstance();



//==============================
// ��ÓI�����o�֐�
//==============================
private:
	/**
	* @brief
	* �R���X�g���N�^
	*/
	Renderer() {}
	Renderer(const Renderer& class_name) = delete;
	Renderer& operator = (const Renderer& class_name) = delete;


public:
	/**
	* @brief
	* �������֐�
	* @param
	* hInstance : �C���X�^���X�n���h��
	* hWnd : Windows�n���h��
	* is_full_screen : �t���X�N���[���t���O
	* window_width : Window��
	* window_height : Window����
	*/
	bool Init(HINSTANCE hInstance, HWND hWnd, BOOL is_full_screen,
			  int window_width, int window_height);

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit();

	/**
	* @brief
	* �`��J�n�֐�
	*/
	bool DrawBegin();

	/**
	* @brief
	* �`��I���֐�
	* @param
	* is_begin_scene : �`��J�n���������Ă��邩�t���O
	*/
	void DrawEnd(bool is_begin_scene);

	/**
	* @brief
	* �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɔ��f�֐�
	*/
	void Present();

	/**
	* @brief
	* �����_���[�ݒ�֐�
	* @param
	* factory : �����_���[�t�@�N�g���[
	* mode : ���[�h
	*/
	void SetRenderer(RendererFactory* factory, MODE mode);

	/**
	* @brief
	* �����_���[�擾�֐�
	*/
	RendererInterface* GetRenderer() { return renderer_; }

	/**
	* @brief
	* �C���^�[�t�F�[�X�擾�֐�
	*/
	template <class Type>
	void GetInterface(Type** pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*pointer = ((RendererDirectX9*)renderer_)->GetInterface();
				break;
			}
			case Renderer::DIRECTX11:
			{
				break;
			}
			case Renderer::OPEN_GL:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}

	/**
	* @brief
	* �f�o�C�X�擾�֐�
	*/
	template <class Type>
	void GetDevice(Type** pointer)
	{
		if (renderer_ == nullptr) return;
		switch (mode_)
		{
			case Renderer::DIRECTX9:
			{
				*pointer = ((RendererDirectX9*)renderer_)->GetDevice();
				break;
			}
			case Renderer::DIRECTX11:
			{
				break;
			}
			case Renderer::OPEN_GL:
			{
				break;
			}
			default:
			{
				break;
			}
		}
	}
};



#endif