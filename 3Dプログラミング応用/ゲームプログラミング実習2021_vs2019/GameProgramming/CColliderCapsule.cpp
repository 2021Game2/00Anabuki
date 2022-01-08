#include "CColliderCapsule.h"
#include "CCollisionManager.h"

CColliderCapsule::CColliderCapsule(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, float radius)
{
	Set(parent, matrix, v0, v1, radius);
}

void CColliderCapsule::Set(CCharacter *parent, CMatrix *matrix
	, const CVector &v0, const CVector &v1, float radius) {
	mType = ECAPSUL;//�J�v�Z���R���C�_
	mpParent = parent;//�e�ݒ�
	if (matrix)
		mpMatrix = matrix;//�e�s�񂠂�ΐݒ�
	//�O�p�`���_�ݒ�
	mV[0] = v0;
	mV[1] = v1;
	mRadius = radius;
}

void CColliderCapsule::Render()
{
	//�A���t�@�u�����h��L���ɂ���
	glEnable(GL_BLEND);
	//�u�����h���@���w��
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//���C�g�I�t
	glDisable(GL_LIGHTING);
	//DIFFUSE�ԐF�ݒ�
	float c[] = { 1.0f, 0.0f, 0.0f, 0.4f };
	glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
	glColor4fv(c);

	//�s��ޔ�
	glPushMatrix();
	//�R���C�_�̍��W�����߂�
	CVector v0 = mV[0] * *mpMatrix;
	CVector v1 = mV[1] * *mpMatrix;

	//�s��ޔ�
	glPushMatrix();
	CVector center;
	center = v0 + (v1 - v0).Normalize() * mRadius;
	glTranslatef(center.mX, center.mY, center.mZ);
	//���`��
	glutSolidSphere(mRadius, 16, 16);
	glPopMatrix();

	//�s��ޔ�
	glPushMatrix();
	center = v1 - (v1 - v0).Normalize() * mRadius;
	glTranslatef(center.mX, center.mY, center.mZ);
	//���`��
	glutSolidSphere(mRadius, 16, 16);
	glPopMatrix();

	//�~���`��
	//gluCylinder�֐��@Z��0����Z���{�����֎w�肵�������̉~����`�悷��
	//1.�~���̒��S�����_�܂ňړ�
	//2.X���ŉ�]�i�t��]�j
	//3.Y���ŉ�]
	//4.�R���C�_�̈ʒu�ֈړ�������
	CVector line = (v1 - v0); //�J�v�Z���S�̂̐������߂�
	center = v0 + line * 0.5f; //�����̒��S�����߂�i�R���C�_�̈ʒu�j
	CVector lineXZ = line; //Y����]�p�f�[�^
	lineXZ.mY = 0.0f;
	if (lineXZ.Length() > 0.0)
	{
		lineXZ = lineXZ.Normalize();
	}
	//�����̒����P
	line = line.Normalize();
	float lineLength = (v1 - v0).Length() - mRadius * 2; //�J�v�Z���̒��������̒��������߂�
	//4.�R���C�_�̈ʒu�ֈړ�������
	glTranslatef(center.mX, center.mY, center.mZ);

	//rotate Y-axis
	CMatrix rot;
	//3.Y���ŉ�]
	if (lineXZ.Length() > 0.001)
	{
		rot.mM[0][0] = rot.mM[2][2] = lineXZ.mZ; //cos
		rot.mM[0][2] = -lineXZ.mX; //-sin
		rot.mM[2][0] = lineXZ.mX; //sin
	}
	glMultMatrixf(rot.mM[0]);

	//rotate X-axis
	rot.Identity();
	//2.X���ŉ�]�i�t��]�j
	float cos = sqrtf(line.mX * line.mX + line.mZ * line.mZ);
	rot.mM[1][1] = rot.mM[2][2] = cos;
	rot.mM[1][2] = -line.mY; //-sin
	rot.mM[2][1] = line.mY; //sin
	glMultMatrixf(rot.mM[0]);

	//1.�~���̒��S�����_�܂ňړ�
	glTranslatef(0.0f, 0.0f, -lineLength / 2.0f);
	GLUquadric* mesh;
	mesh = gluNewQuadric();
	//gluCylinder�֐��@Z��0����Z���{�����֎w�肵�������̉~����`�悷��
	gluCylinder(mesh, mRadius, mRadius, lineLength, 16, 16);

	//���C�g�I��
	glEnable(GL_LIGHTING);
	//�A���t�@�u�����h����
	glDisable(GL_ALPHA);
	//�s�񕜋A
	glPopMatrix();
}
//�D��x�̕ύX
void CColliderCapsule::ChangePriority()
{
	//mV[0]��mV[1]�̒��S�����߂�
	CVector pos = (mV[0] * *mpMatrix + mV[1] * *mpMatrix) * (0.5f);
	//�x�N�g���̒������D��x
	mPriority = pos.Length();
	CCollisionManager::Get()->Remove(this); //��U�폜
	CCollisionManager::Get()->Add(this); //�ǉ�
}
