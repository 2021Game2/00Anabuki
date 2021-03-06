#ifndef CCOLLIDER_H
#define CCOLLIDER_H
//キャラクタクラスのインクルード
#include "CCharacter.h"
//トランスフォームクラスのインクルード
#include "CTransform.h"
/*
コライダクラス
衝突判定データ
*/
class CCollider : public CTransform, public CTask {
public:
	enum ETag
	{
		EBODY,		//本体
		ESEARCH,	//サーチ用
		ESWORD,	//剣
	};
	ETag mTag;
	//コライダタイプ
	enum EType {
		ESPHERE,//球コライダ
		ETRIANGLE,//三角コライダ
		ELINE, //線分コライダ
		ECAPSUL, //カプセルコライダ
	};
	EType mType;//コライダタイプ
	//頂点
	CVector mV[3];

	CCharacter *mpParent;//親
	CMatrix *mpMatrix;//親行列
	float mRadius;	//半径

	//デフォルトコンストラクタ
	CCollider();

	//コンストラクタ
	//CCollider(親, 行列, 位置, 半径)
	CCollider(CCharacter *parent, CMatrix *matrix, CVector position, float radius);
	//描画
	void Render();
	~CCollider();
	//衝突判定
	//Collision(コライダ1, コライダ2)
	//retrun:true（衝突している）false(衝突していない)
	static bool Collision(CCollider *m, CCollider *o);
	//CollisionTriangleLine(三角コライダ, 線分コライダ, 調整値)
	//retrun:true（衝突している）false(衝突していない)
	//調整値:衝突しない位置まで戻す値
	static bool CollisionTriangleLine(CCollider *triangle, CCollider *line, CVector *adjust);
	//CollisionTriangleSphere(三角コライダ, 球コライダ, 調整値)
	//retrun:true（衝突している）false(衝突していない)
	//調整値:衝突しない位置まで戻す値
	static bool CollisionTriangleSphere(CCollider *triangle, CCollider *sphere, CVector *adjust);
	//優先度の変更
	virtual void ChangePriority();

	//カプセルコライダとカプセルコライダの衝突判定
	//CollisionCapsule(カプセルコライダ１, カプセルコライダ２, 調整値)
	//retrun:true（衝突している）false(衝突していない)
	//調整値:カプセルコライダ１が衝突しない位置まで戻す値
	static bool CollisionCapsule(CCollider* m, CCollider* o, CVector* adjust);
	//線と線との最短ベクトルを求める
	//VectorLineMinDist(線１開始, 線１終了, 線２開始, 線２終了)
	//return:線と線との最短ベクトル
	static CVector VectorLineMinDist(const CVector& Start1, const CVector& End1, const CVector& Start2, const CVector& End2);

};

#endif
