#include "CCamera.h"
#include "glut.h"

//�J�����̊O���ϐ�
CCamera Camera;
CMatrix CCamera::sCameraMatrix;

CMatrix& CCamera::CameraMatrix()
{
	return sCameraMatrix;
}

void CCamera::Set(const CVector &eye, const CVector &center,
	const CVector &up) {
	mEye = eye;
	mCenter = center;
	mUp = up;
}

void CCamera::Render() {
	gluLookAt(mEye.mX, mEye.mY, mEye.mZ,
		mCenter.mX, mCenter.mY, mCenter.mZ,
		mUp.mX, mUp.mY, mUp.mZ);
	//���f���r���[�s����擾
	glGetFloatv(GL_MODELVIEW_MATRIX, sCameraMatrix.mF);
	//�J�����s������߂�
	float t;
	t = sCameraMatrix.mM[0][1];
	sCameraMatrix.mM[0][1] = sCameraMatrix.mM[1][0];
	sCameraMatrix.mM[1][0] = t;
	t = sCameraMatrix.mM[0][2];
	sCameraMatrix.mM[0][2] = sCameraMatrix.mM[2][0];
	sCameraMatrix.mM[2][0] = t;
	t = sCameraMatrix.mM[1][2];
	sCameraMatrix.mM[1][2] = sCameraMatrix.mM[2][1];
	sCameraMatrix.mM[2][1] = t;
	sCameraMatrix.mM[3][0] = 0.0f;
	sCameraMatrix.mM[3][1] = 0.0f;
	sCameraMatrix.mM[3][2] = 0.0f;
}
