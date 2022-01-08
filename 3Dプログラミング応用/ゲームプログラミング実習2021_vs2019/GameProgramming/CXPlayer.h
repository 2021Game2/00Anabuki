#ifndef CXPLAYER_H
#define CXPLAYER_H

#include "CXCharacter.h"
#include "CCollider.h"
#include "CText.h"
#include "CColliderCapsule.h"

class CXPlayer : public CXCharacter
{
	CText mFont;
	CColliderCapsule mColCapsule;
public:
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
	CCollider mColSphereSword;	//��


	CXPlayer();

	/*
	������(X���f���N���X�̃|�C���^)
	*/
	void Init(CModelX* model);

	void Update();

	void CXPlayer::Render2D();
};

#endif
