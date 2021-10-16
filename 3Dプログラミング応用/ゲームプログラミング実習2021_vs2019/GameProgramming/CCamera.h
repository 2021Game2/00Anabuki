#ifndef CCAMERA_H
#define CCAMERA_H
#include "CVector.h"
#include "CMatrix.h"
/*
カメラクラス
*/
class CCamera {
	static CMatrix sCameraMatrix;
public:
	static CMatrix& CameraMatrix();
	//視点
	CVector mEye;
	//注視点
	CVector mCenter;
	//上方向
	CVector mUp;
	//カメラの設定
	//Set(視点, 注視点, 上方向)
	void Set(const CVector &eye, const CVector &center,
		const CVector &up);
	//カメラ適用
	void Render();
};

//カメラの外部参照
extern CCamera Camera;
#endif
