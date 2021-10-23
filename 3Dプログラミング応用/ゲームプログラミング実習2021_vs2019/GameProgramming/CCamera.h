#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
#include "CMatrix.h"
/*
�J�����N���X
*/
class CCamera {
	static CCamera CCamera::sCamera;
	static CMatrix sMatrixCamera;
	static CMatrix sMatrixModelView;
	static CMatrix sMatrixProjection;
	//���_
	CVector mEye;
	//�����_
	CVector mCenter;
	//�����
	CVector mUp;
public:
	static CCamera& Camera();
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
	bool CCamera::WorldToScreen(CVector* pOut, const CVector& pos);

};

//�J�����̊O���Q��
extern CCamera Camera;
#endif
