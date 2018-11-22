//================================================================================
//
//    �t�F�[�h�N���X
//    Author : Araki Kai                                �쐬�� : 2018/03/27
//
//================================================================================

#ifndef	_RENDER_TEXTURE_H_
#define _RENDER_TEXTURE_H_



//****************************************
// �C���N���[�h��
//****************************************
#include <string>

#include <Component/Draw/DrawNull/DrawNull.h>
#include <Transform\Transform.h>
#include <Polygon\PlanePolygon\PlanePolygon.h>
#include <Texture\TextureManager\TextureManager.h>



/*********************************************************//**
* @brief
* �t�F�[�h�N���X
*
* �t�F�[�h�̃N���X
*************************************************************/
class RenderTexture : public DrawNull
{
//==============================
// ��ÓI�����o�ϐ�
//==============================
private:
	PlanePolygon* plane_polygon_;		//!< �|���S��
	Transform transform_;				//!< ���

//==============================
// ��ÓI�����o�֐�
//==============================
public:
	/**
	* @brief
	* �������֐�
	*/
	void Init()
	{		
		plane_polygon_ = new PlanePolygon();
	}

	/**
	* @brief
	* �I���֐�
	*/
	void Uninit() override
	{
		SafeRelease::Normal(&plane_polygon_);
	}

	void Update(float x, float y, XColor4 color)
	{
		transform_.GetPosition()->x = -0.5f;
		transform_.GetPosition()->y = -0.5f;
		transform_.GetScale()->x = x;
		transform_.GetScale()->y = y;
		transform_.UpdateWorldMatrixSRT();

		plane_polygon_->SetColor(color);
	}

	/**
	* @brief
	* �`��֐�
	*/
	void Draw(unsigned object_index, unsigned mesh_index) override
	{
		object_index = object_index;
		mesh_index = mesh_index;

		// �|���S���`��
		plane_polygon_->Draw();
	}

	// �v���p�e�B
	const MATRIX* GetMatrix(unsigned object_index) override
	{
		object_index = object_index;
		return transform_.GetMatrixExtend()->GetWorldMatrix();
	}

	D3DMATERIAL9* GetMaterial()
	{
		return plane_polygon_->GetMaterial();
	}
};



#endif