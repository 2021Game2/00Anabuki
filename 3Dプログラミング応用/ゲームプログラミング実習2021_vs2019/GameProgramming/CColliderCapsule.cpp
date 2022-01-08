#include "CColliderCapsule.h"
#include "CCollisionManager.h"

CColliderCapsule::CColliderCapsule(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, float radius)
{
	Set(parent, matrix, v0, v1, radius);
}

void CColliderCapsule::Set(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, float radius) {
	mType = ECAPSUL;//カプセルコライダ
	mpParent = parent;//親設定
	if (matrix)
		mpMatrix = matrix;//親行列あれば設定
	//三角形頂点設定
	mV[0] = v0;
	mV[1] = v1;
	mRadius = radius;
}

void CColliderCapsule::Render()
{
	//アルファブレンドを有効にする
	glEnable(GL_BLEND);
	//ブレンド方法を指定
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//ライトオフ
	glDisable(GL_LIGHTING);
	//DIFFUSE赤色設定
	float c[] = { 1.0f, 0.0f, 0.0f, 0.4f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//行列退避
	glPushMatrix();
	//コライダの座標を求める
	CVector v0 = mV[0] * *mpMatrix;
	CVector v1 = mV[1] * *mpMatrix;

	//行列退避
	glPushMatrix();
	CVector center;
	center = v0 + (v1 - v0).Normalize() * mRadius;
	glTranslatef(center.mX, center.mY, center.mZ);
	//球描画
	glutSolidSphere(mRadius, 16, 16);
	glPopMatrix();

	//行列退避
	glPushMatrix();
	center = v1 - (v1 - v0).Normalize() * mRadius;
	glTranslatef(center.mX, center.mY, center.mZ);
	//球描画
	glutSolidSphere(mRadius, 16, 16);
	glPopMatrix();

	//円柱描画
	//gluCylinder関数　Z軸0からZ軸＋方向へ指定した長さの円柱を描画する
	//1.円柱の中心を原点まで移動
	//2.X軸で回転（逆回転）
	//3.Y軸で回転
	//4.コライダの位置へ移動させる
	CVector line = (v1 - v0); //カプセル全体の線分求める
	center = v0 + line * 0.5f; //線分の中心を求める（コライダの位置）
	CVector lineXZ = line; //Y軸回転用データ
	lineXZ.mY = 0.0f;
	if (lineXZ.Length() > 0.0)
	{
		lineXZ = lineXZ.Normalize();
	}
	//線分の長さ１
	line = line.Normalize();
	float lineLength = (v1 - v0).Length() - mRadius * 2; //カプセルの直線部分の長さを求める
	//4.コライダの位置へ移動させる
	glTranslatef(center.mX, center.mY, center.mZ);

	//rotate Y-axis
	CMatrix rot;
	//3.Y軸で回転
	if (lineXZ.Length() > 0.001)
	{
		rot.mM[0][0] = rot.mM[2][2] = lineXZ.mZ; //cos
		rot.mM[0][2] = -lineXZ.mX; //-sin
		rot.mM[2][0] = lineXZ.mX; //sin
	}
	glMultMatrixf(rot.mM[0]);

	//rotate X-axis
	rot.Identity();
	//2.X軸で回転（逆回転）
	float cos = sqrtf(line.mX * line.mX + line.mZ * line.mZ);
	rot.mM[1][1] = rot.mM[2][2] = cos;
	rot.mM[1][2] = -line.mY; //-sin
	rot.mM[2][1] = line.mY; //sin
	glMultMatrixf(rot.mM[0]);

	//1.円柱の中心を原点まで移動
	glTranslatef(0.0f, 0.0f, -lineLength / 2.0f);
	GLUquadric* mesh;
	mesh = gluNewQuadric();
	//gluCylinder関数　Z軸0からZ軸＋方向へ指定した長さの円柱を描画する
	gluCylinder(mesh, mRadius, mRadius, lineLength, 16, 16);

	//ライトオン
	glEnable(GL_LIGHTING);
	//アルファブレンド無効
	glDisable(GL_ALPHA);
	//行列復帰
	glPopMatrix();
}
//優先度の変更
void CColliderCapsule::ChangePriority()
{
	//mV[0]とmV[1]の中心を求める
	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix) * (0.5f);
	//ベクトルの長さが優先度
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this); //一旦削除
	CCollisionManager::Get()->Add(this); //追加
}
