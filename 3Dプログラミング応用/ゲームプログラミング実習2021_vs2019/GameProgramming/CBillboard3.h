#ifndef CBILLBOARD3_H
#define CBILLBOARD3_H
#include "CCharacter.h"
/*
�r���{�[�h�N���X
��ɃJ�����̕��������l�p�`
*/
class CBillBoard3 : public CCharacter {
	CMatrix mMatrixModelView;
	CMatrix mCameraInverse;
public:
	//�O�p�`2��
	CTriangle mT[2];
	//�}�e���A��
	CMaterial mMaterial;
	//�R���X�g���N�^
	CBillBoard3();
	//CBillBoard(�ʒu, ��, ����)
	CBillBoard3(CVector pos, float w, float h);
	//�ʒu�Ƒ傫���̐ݒ�
	//Set(�ʒu, ��, ����)
	void Set(CVector pos, float w, float h);
	//�X�V
	void Update();
	//�`��
	void Render();
	void Render(CMaterial* mpMaterial);
};
#endif

