#include "CXPlayer.h"
#include "CKey.h"
#include "CUtil.h"
#include "CCamera.h"

CXPlayer::CXPlayer()
	: mColSphereBody(this, nullptr, CVector(), 0.5f)
	, mColSphereHead(this, nullptr, CVector(0.0f, 5.0f, -3.0f), 0.5f)
	, mColSphereSword(this, nullptr, CVector(-10.0f, 10.0f, 50.0f), 0.3f)
	, mColCapsule(this,nullptr, CVector(0.0f, -100.5f, 0.0f), CVector(0.0f, 70.5f, 0.0f),0.7)
{
	//タグにプレイヤーを設定します
	mTag = EPLAYER;
	mColSphereSword.mTag = CCollider::ESWORD;
	mFont.LoadTexture("FontG.png", 1, 4096 / 64);
}

void CXPlayer::Init(CModelX* model)
{
	CXCharacter::Init(model);
	//合成行列の設定
	mColSphereBody.mpMatrix = &mpCombinedMatrix[9];
	//頭
	mColSphereHead.mpMatrix = &mpCombinedMatrix[12];
	//剣
	mColSphereSword.mpMatrix = &mpCombinedMatrix[22];
	//
	mColCapsule.mpMatrix = &mpCombinedMatrix[9];
}

void CXPlayer::Update()
{
	if (mAnimationIndex == 3)
	{
		if (mAnimationFrame >= mAnimationFrameSize)
		{
			ChangeAnimation(4, false, 30);
		}
	}
	else if (mAnimationIndex == 4)
	{
		if (mAnimationFrame >= mAnimationFrameSize)
		{
			ChangeAnimation(0, true, 60);
		}
	}
	else
	{
		if (CKey::Push('A'))
		{
			mRotation.mY += 2.0f;
		}
		if (CKey::Push('D'))
		{
			mRotation.mY -= 2.0f;
		}
		if (CKey::Push(' '))
		{
			ChangeAnimation(3, true, 30);
		}
		else if (CKey::Push('W'))
		{
			ChangeAnimation(1, true, 60);
			mPosition += CVector(0.0f, 0.0f, 0.1f) * mMatrixRotate;
		}
		else {
			ChangeAnimation(0, true, 60);
		}
	}
	CXCharacter::Update();
}

void CXPlayer::Render2D()
{
	CVector ret;

	CCamera::Camera().WorldToScreen(&ret, mPosition);

	//2D描画開始
	CUtil::Start2D(0, 800, 0, 600);

	//文字列の描画
	mFont.DrawString("TEST", ret.mX, ret.mY, 8, 16);


	//2Dの描画終了
	CUtil::End2D();
}
