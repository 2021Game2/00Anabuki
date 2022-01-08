#ifndef CXENEMY_H
#define CXENEMY_H

#include "CXCharacter.h"
#include "CColliderCapsule.h"
#include "CText.h"

class CXEnemy : public CXCharacter
{
	CText mFont;
	CCollider mColSphereSword0;	//��
	CCollider mColSphereSword1;	//��
	CCollider mColSphereSword2;	//��
	CColliderCapsule mColCapsule;
public:
	//�R���C�_�̐錾
	CCollider mColSphereBody;	//��
	CCollider mColSphereHead;	//��
//	CCollider mColSphereSword;	//��

	CXEnemy();
	/*
	������(X���f���N���X�̃|�C���^)
	*/
	void Init(CModelX* model);

	//�Փˏ���
	//m:�����̃R���C�_ o:����̃R���C�_
	void Collision(CCollider* m, CCollider* o);
	void CXEnemy::Render2D();
};

#endif
