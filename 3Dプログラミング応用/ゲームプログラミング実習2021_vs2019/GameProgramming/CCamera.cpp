#include "CCamera.h"
#include "glut.h"

//カメラの外部変数
CCamera Camera;
CMatrix CCamera::sCameraMatrix;
CMatrix CCamera::sModelViewMatrix;

CMatrix& CCamera::CameraMatrix()
{
	return sCameraMatrix;
}

CVector& CCamera::Eye()
{
	return mEye;
}

void CCamera::Set(const CVector &eye, const CVector &center,
	const CVector &up) {
	LookAt(eye, center, up);
}

void CCamera::LookAt(const CVector& eye, const CVector& center, const CVector& up)
{
	mEye = eye;
	mCenter = center;
	mUp = up;
	CVector x, y, z;
	//Zは逆ベクトル
	z = (mEye - mCenter).Normalize();
	x = mUp.Cross(z).Normalize();
	y = z.Cross(x).Normalize();
	//カメラ行列の設定
	sCameraMatrix.Identity();
	sCameraMatrix.mM[0][0] = x.mX;
	sCameraMatrix.mM[0][1] = x.mY;
	sCameraMatrix.mM[0][2] = x.mZ;
	sCameraMatrix.mM[1][0] = y.mX;
	sCameraMatrix.mM[1][1] = y.mY;
	sCameraMatrix.mM[1][2] = y.mZ;
	sCameraMatrix.mM[2][0] = z.mX;
	sCameraMatrix.mM[2][1] = z.mY;
	sCameraMatrix.mM[2][2] = z.mZ;
	//モデルビュー行列の設定
	sModelViewMatrix = sCameraMatrix;
	sModelViewMatrix.mM[0][1] = sCameraMatrix.mM[1][0];
	sModelViewMatrix.mM[0][2] = sCameraMatrix.mM[2][0];
	sModelViewMatrix.mM[1][0] = sCameraMatrix.mM[0][1];
	sModelViewMatrix.mM[1][2] = sCameraMatrix.mM[2][1];
	sModelViewMatrix.mM[2][0] = sCameraMatrix.mM[0][2];
	sModelViewMatrix.mM[2][1] = sCameraMatrix.mM[1][2];
	CMatrix translate;
	translate.Translate(-mEye.mX, -mEye.mY, -mEye.mZ);
	sModelViewMatrix = translate * sModelViewMatrix;
}

void CCamera::Render() {
	//行列のモードをモデルビューにする
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(sModelViewMatrix.mF);
}
