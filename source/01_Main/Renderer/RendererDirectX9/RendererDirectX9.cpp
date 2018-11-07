//================================================================================
//
//    �����_���[DirectX9�N���X
//    Author : Araki Kai                                �쐬�� : 2018/05/08
//
//================================================================================



//****************************************
// �C���N���[�h��
//****************************************
#include "RendererDirectX9.h"
#include <SafeRelease/SafeRelease.h>



//****************************************
// �萔��`
//****************************************
const DWORD	RendererDirectX9::FVF_VERTEX_3D = (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1);



//****************************************
// ��ÓI�����o�֐���`
//****************************************
//--------------------------------------------------
// +�������֐�
//--------------------------------------------------
bool RendererDirectX9::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow,
							int nWindowWidth, int nWindowHeight)
{
	// �g���Ă��Ȃ������̏���
	hInstance = hInstance;

	// �_�C���N�g3D�C���^�t�F�[�X�̎擾
	direct3d_interface_ = Direct3DCreate9(D3D_SDK_VERSION);

	if (direct3d_interface_ == nullptr) return false;

	// ���݂̃f�B�X�v���C���[�h���擾
	D3DDISPLAYMODE direct3d_display_mode;
	HRESULT h_result = direct3d_interface_->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,		// �f�B�X�v���C�E�A�_�v�^���w�肷��(����̎w��͏����̃f�B�X�v���C�E�A�_�v�^)
																  &direct3d_display_mode);	// ���݂̃f�B�X�v���C�E�A�_�v�^�̏����󂯎��ϐ��̐擪�A�h���X

	if (FAILED(h_result)) return false;

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^(�f�o�C�X���쐬���邽�߂̃f�[�^)
	D3DPRESENT_PARAMETERS direct3d_present_parameters;
	ZeroMemory(&direct3d_present_parameters, sizeof(direct3d_present_parameters));
	direct3d_present_parameters.BackBufferWidth = nWindowWidth;							//�@�����(�o�b�N�o�b�t�@)�̕�
	direct3d_present_parameters.BackBufferHeight = nWindowHeight;						//	�����(�o�b�N�o�b�t�@)�̍���
	direct3d_present_parameters.BackBufferFormat = direct3d_display_mode.Format;		//	�F��( �o�b�N�o�b�t�@�̃t�H�[�}�b�g )
	direct3d_present_parameters.BackBufferCount = 1;									//	�o�b�N�o�b�t�@�̐�
	direct3d_present_parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;						//	�f���M���̓���(DISCARD�͐����������C�ɂ���)
	direct3d_present_parameters.EnableAutoDepthStencil = TRUE;							//	TRUE�ŗǂ�
	direct3d_present_parameters.AutoDepthStencilFormat = D3DFMT_D16;					//	���͂���ŗǂ���̃t�H�[�}�b�g
	direct3d_present_parameters.Windowed = bWindow;										//	TRUE�ŃE�B���h�E���[�h,FALSE�Ńt���X�N���[�����[�h
	direct3d_present_parameters.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	//	�t���X�N���[�����[�h�̎��̃��t���b�V�����[�g��Hz����ύX
	direct3d_present_parameters.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;		//	���j�^�[��Hz���ɍ��킹�ĕ`�悳���(IMMEDIATE���Ɛ���������҂����ɕ`�悷��)( D3DPRESENT_INTERVAL_ONE�@�ɂ���ƃw���c�œ��� )

	// �f�o�C�X�I�u�W�F�N�g�̐���( ��`�棂Ƣ���_��������n�[�h�E�F�A�ōs��
	h_result = direct3d_interface_->CreateDevice(D3DADAPTER_DEFAULT,					// �f�B�X�v���C�E�A�_�v�^���w�肷��( ����̎w��͏����̃f�B�X�v���C�E�A�_�v�^ )
												 D3DDEVTYPE_HAL,						// �f�o�C�X�^�C�v( ����̎w��̓n�[�h�E�F�A�ɂ�鏈�����s�� )
												 hWnd,									// ���̃f�o�C�X�Ńt�H�[�J�X��ݒ肷��E�B���h�E�n���h��
												 D3DCREATE_HARDWARE_VERTEXPROCESSING,	// �f�o�C�X�̍쐬�𐧌䂷��t���O�̑g�ݍ��킹( ����̎w��̓n�[�h�E�F�A�ɂ�钸�_�������w�� )
												 &direct3d_present_parameters,			// �f�o�C�X�̐ݒ���w�肵���ϐ��̐擪�A�h���X
												 &direct3d_device_);					// �쐬�����f�o�C�X���󂯎��ϐ��̐擪�A�h���X

	if (FAILED(h_result))
	{
		MessageBox(hWnd, "�_�C���N�g3D�f�o�C�X��\n�쐬�Ɏ��s���܂���!!", "Error", MB_OK);
		return false;
	}

	/*

	

	*/

	return true;
}



//--------------------------------------------------
// +�I�������֐�
//--------------------------------------------------
void RendererDirectX9::Uninit()
{
	// �f�o�C�X�̉��
	SafeRelease::PlusRelease(&direct3d_device_);

	// Direct3D�C���^�[�t�F�[�X�̉��
	SafeRelease::PlusRelease(&direct3d_interface_);
}



//--------------------------------------------------
// +�`��J�n�֐�
//--------------------------------------------------
bool RendererDirectX9::DrawBegin()
{
	// ��ʃN���A
	direct3d_device_->Clear(0,										// RECT�\���̔z��̋�`�̐�
							NULL,									// RECT�\���̂̐擪�A�h���X(��ʑS�̂�NULL)
							(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER),	// TARGET�͐F�̃N���A�AZBUFFER��Z�o�b�t�@�̃N���A
							D3DCOLOR_RGBA(32, 64, 192, 255),		// �N���A�J���\(TARGET������Ƃ�)
							1.0f,									// Z�o�b�t�@�̃N���A�l
							0);										// �X�e���V���l�̃N���A�l

	// �`��̊J�n
	if (SUCCEEDED(direct3d_device_->BeginScene())) return true;

	return false;
}



//--------------------------------------------------
// +�`��I���֐�
//--------------------------------------------------
void RendererDirectX9::DrawEnd(bool is_begin_scene)
{
	// �`��̏I��
	if (is_begin_scene) direct3d_device_->EndScene();

	// �o�b�N�o�b�t�@���t�����g�o�b�t�@�ɕ`��
	direct3d_device_->Present(NULL, NULL, NULL, NULL);
}



//--------------------------------------------------
// +�C���^�t�F�[�X�擾�֐�
//--------------------------------------------------
LPDIRECT3D9 RendererDirectX9::GetInterface()
{
	return direct3d_interface_;
}



//--------------------------------------------------
// +�_�C���N�g3D�f�o�C�X�擾�֐�
//--------------------------------------------------
LPDIRECT3DDEVICE9 RendererDirectX9::GetDevice()
{
	return direct3d_device_;
}
