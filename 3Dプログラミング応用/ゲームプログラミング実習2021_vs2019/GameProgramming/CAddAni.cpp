#include "CAddAni.h"

CModelX CAddAnimation::mModel;

#define MODEL "mutant\\mutant.x"
#define ANI_ATTACK "mutant\\mutant@WalkingBackwards.fbx.x"

CAddAnimation::CAddAnimation()
	:mColHit(this,nullptr,CVector(0.0f, 0.0f, 0.0f), 0.8f)
{
	if (mModel.mFrame.size() == 0)
	{
		mModel.Load(MODEL);
		mModel.AddAnimationSet(ANI_ATTACK);
	}
	mPosition = CVector(-5.0f, 0.0f, 1.0f);
	mRotation.mY = 0.0f;
	mScale = CVector(3.0f, 3.0f, 3.0f);
	Init(&mModel);
	ChangeAnimation(1, true, 250);
	//çáê¨çsóÒÇÃê›íË
	mColHit.mpMatrix = &mpCombinedMatrix[4];
}

void CAddAnimation::Update()
{
	CXCharacter::Update();
}
