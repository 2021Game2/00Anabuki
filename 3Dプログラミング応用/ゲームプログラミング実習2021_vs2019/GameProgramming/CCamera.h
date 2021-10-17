#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
#include "CMatrix.h"
/*
�J�����N���X
*/
class CCamera {
	static CMatrix sCameraMatrix;
	static CMatrix sModelViewMatrix;
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
public:
	static CMatrix& CameraMatrix();

	CVector& Eye();

	//�J�����̐ݒ�
	//Set(���_, �����_, �����)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);
	//LookAt(���_, �����_, �����)
	void LookAt(const CVector& eye, const CVector& center,
		const CVector& up);
	//�J�����K�p
	void Render();
};

//�J�����̊O���Q��
extern CCamera Camera;
#endif
