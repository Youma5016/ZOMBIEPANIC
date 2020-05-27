#pragma once
#include"Anime.h"

class Anime;

class CEnemy : Anime
{
public:
	CEnemy();
	~CEnemy();
	void End();
	void Init();
	void Update();
	void Draw3D();
	void EnemyKill(int No);

private:
	//‘Ì
	D3DXMATRIX		mMatrix;//Body
	std::shared_ptr<KdModel>		BodyMesh;
	//
	//“ª
	D3DXMATRIX		mHeadMatrix;
	std::shared_ptr<KdModel>		HeadMesh;
	//
	//¶˜r
	D3DXMATRIX		mLArmMatrix;
	std::shared_ptr<KdModel>		LArmMesh;
	//
	//‰E˜r
	D3DXMATRIX		mRArmMatrix;
	std::shared_ptr<KdModel>		RArmMesh;
	//
	//¶‘«
	D3DXMATRIX		mLLegMatrix;
	std::shared_ptr<KdModel>		LLegMesh;
	//
	//‰E‘«
	D3DXMATRIX		mRLegMatrix;
	std::shared_ptr<KdModel>		RLegMesh;
	//
	//‘S•”
	D3DXMATRIX		mMatrix1RotY;
	D3DXMATRIX      mScale;
	D3DXVECTOR3	    mPos;
	BOOL EnemyHit;
	bool mIsaLive, AtkFlg;
	//

};
