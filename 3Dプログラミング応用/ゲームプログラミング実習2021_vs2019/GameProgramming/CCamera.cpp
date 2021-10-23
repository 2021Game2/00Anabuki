#include "CCamera.h"
#include "glut.h"
#include "main.h"

//�J�����̊O���ϐ�
CCamera CCamera::sCamera;
CMatrix CCamera::sMatrixCamera;
CMatrix CCamera::sMatrixModelView;
CMatrix CCamera::sMatrixProjection;

CCamera& CCamera::Camera()
{
	return sCamera;
}

CMatrix& CCamera::CameraMatrix()
{
	return sMatrixCamera;
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
	//Z�͋t�x�N�g��
	z = (mEye - mCenter).Normalize();
	x = mUp.Cross(z).Normalize();
	y = z.Cross(x).Normalize();
	//�J�����s��̐ݒ�
	sMatrixCamera.Identity();
	sMatrixCamera.mM[0][0] = x.mX;
	sMatrixCamera.mM[0][1] = x.mY;
	sMatrixCamera.mM[0][2] = x.mZ;
	sMatrixCamera.mM[1][0] = y.mX;
	sMatrixCamera.mM[1][1] = y.mY;
	sMatrixCamera.mM[1][2] = y.mZ;
	sMatrixCamera.mM[2][0] = z.mX;
	sMatrixCamera.mM[2][1] = z.mY;
	sMatrixCamera.mM[2][2] = z.mZ;
	//���f���r���[�s��̐ݒ�
	//�J�����s��̋t�s��쐬
	sMatrixModelView = sMatrixCamera;
	sMatrixModelView.mM[0][1] = sMatrixCamera.mM[1][0];
	sMatrixModelView.mM[0][2] = sMatrixCamera.mM[2][0];
	sMatrixModelView.mM[1][0] = sMatrixCamera.mM[0][1];
	sMatrixModelView.mM[1][2] = sMatrixCamera.mM[2][1];
	sMatrixModelView.mM[2][0] = sMatrixCamera.mM[0][2];
	sMatrixModelView.mM[2][1] = sMatrixCamera.mM[1][2];
	CMatrix translate;
	translate.Translate(-mEye.mX, -mEye.mY, -mEye.mZ);
	sMatrixModelView = translate * sMatrixModelView;
}

void CCamera::Render() {
	//�s��̃��[�h�����f���r���[�ɂ���
	//gluLookAt(mEye.mX, mEye.mY, mEye.mZ,
	//	mCenter.mX, mCenter.mY, mCenter.mZ,
	//	mUp.mX, mUp.mY, mUp.mZ);

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(sMatrixModelView.mF);
	glGetFloatv(GL_MODELVIEW_MATRIX, sMatrixModelView.mF);
	glGetFloatv(GL_PROJECTION_MATRIX, sMatrixProjection.mF);
}

bool CCamera::WorldToScreen(CVector* pOut, const CVector& pos)
{
	//���W�ϊ�
//	CVector	screen_pos = mMatrix * pos;
	CMatrix matrix = sMatrixModelView * sMatrixProjection;
	CVector	screen_pos = pos * matrix;

	//��ʊO�Ȃ̂Ń��^�[��
	if (screen_pos.mZ <= 0.0f) {
		return false;
	}
	//���W����
	screen_pos = screen_pos * (1.0f / screen_pos.mZ);

	//	printf("%f,%f,%f\n", screen_pos.mX, screen_pos.mY, screen_pos.mZ);

	//�X�N���[���ϊ�
	pOut->mX = (1.0f + screen_pos.mX) * WINDOW_WIDTH * 0.5f;
	pOut->mY = (1.0f + screen_pos.mY) * WINDOW_HEIGHT * 0.5f;
	pOut->mZ = screen_pos.mZ;

	return true;
}
