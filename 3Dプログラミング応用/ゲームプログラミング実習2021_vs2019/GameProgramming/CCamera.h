#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
#include "CMatrix.h"
/*
カメラクラス
*/
class CCamera {
	static CCamera CCamera::sCamera;
	static CMatrix sMatrixCamera;
	static CMatrix sMatrixModelView;
	static CMatrix sMatrixProjection;
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;
public:
	static CCamera& Camera();
	static CMatrix& CameraMatrix();

	CVector& Eye();

	//カメラの設定
	//Set(視点, 注視点, 上方向)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);
	//LookAt(視点, 注視点, 上方向)
	void LookAt(const CVector& eye, const CVector& center,
		const CVector& up);
	//カメラ適用
	void Render();
	bool CCamera::WorldToScreen(CVector* pOut, const CVector& pos);

};

//カメラの外部参照
extern CCamera Camera;
#endif
