#include "CBillBoard3.h"
#include "CCamera.h"
#define _USE_MATH_DEFINES
#include <math.h>

CBillBoard3::CBillBoard3()
{
}

CBillBoard3::CBillBoard3(CVector pos, float w, float h)
{
	Set(pos, w, h);
}

void CBillBoard3::Set(CVector pos, float w, float h) {
	//位置
	mPosition = pos;
	//大きさの設定
	mScale.mX = w;
	mScale.mY = h;
	//三角形の頂点座標設定
	mT[0].SetVertex(CVector(1.0f, 1.0f, 0.0f),
		CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, -1.0f, 0.0f));
	mT[1].SetVertex(CVector(-1.0f, 1.0f, 0.0f),
		CVector(-1.0f, -1.0f, 0.0f), CVector(1.0f, 1.0f, 0.0f));
	//法線をZ軸方向
	mT[0].SetNormal(CVector(0.0f, 0.0f, 1.0f));
	mT[1].SetNormal(CVector(0.0f, 0.0f, 1.0f));
	//色を白色を設定
	mMaterial.mDiffuse[0] = mMaterial.mDiffuse[1] =
		mMaterial.mDiffuse[2] = mMaterial.mDiffuse[3] = 1.0f;
}


void CBillBoard3::Update() {
	CMatrix scale;
	mMatrix.Identity();
	mMatrix.Translate(mPosition.mX, mPosition.mY, mPosition.mZ);
	scale.Scale(mScale.mX, mScale.mY, mScale.mZ);
	mMatrix = scale * CCamera::CameraMatrix() * mMatrix;
}

void CBillBoard3::Render()
{
	Render(&mMaterial);
}
//Render(マテリアルのポインタ)
void CBillBoard3::Render(CMaterial* mpMaterial) {
	//行列の保存
	glPushMatrix();
	//拡縮、回転、移動させる
	glMultMatrixf(mMatrix.mM[0]);
	//ライトオフ
	glDisable(GL_LIGHTING);
	//描画色の設定
	glColor4fv(mpMaterial->mDiffuse);
	//マテリアル適用
	mpMaterial->Enabled();
	//三角形の描画
	mT[0].Render();
	mT[1].Render();
	//マテリアル解除
	mpMaterial->Disabled();
	//ライトオン
	glEnable(GL_LIGHTING);
	//行列を戻す
	glPopMatrix();
}
