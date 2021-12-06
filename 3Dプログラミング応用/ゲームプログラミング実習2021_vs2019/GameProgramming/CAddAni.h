#ifndef CADDANI_H
#define CFBXTOX_H

#include "CXCharacter.h"
#include "CCollider.h"

class CAddAnimation : public CXCharacter
{
	CCollider mColHit;
	static CModelX mModel;
public:
	CAddAnimation();

	void Update();

};

#endif

