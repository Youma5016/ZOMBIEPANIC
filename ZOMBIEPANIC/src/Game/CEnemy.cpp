#include"../System/KdLibrary/MyLibrary.h"
#include"CPlayer.h"
#include"CEnemy.h"



CEnemy::CEnemy()
	:mMatrix()
	,mHeadMatrix()
	,mLArmMatrix()
	,mRArmMatrix()
	,mRLegMatrix()
	,mLLegMatrix()
{
}
CEnemy::~CEnemy()
{
}

void CEnemy::Init()
{
	BodyMesh = RESOURCE_MNG.GetModel("data/zombie_body.x");
	HeadMesh = RESOURCE_MNG.GetModel("data/zombie_Head.x");
	LArmMesh = RESOURCE_MNG.GetModel("data/zombie_LArm.x");
	RArmMesh = RESOURCE_MNG.GetModel("data/zombie_RArm.x");
	LLegMesh = RESOURCE_MNG.GetModel("data/zombie_LLeg.x");
	RLegMesh = RESOURCE_MNG.GetModel("data/zombie_RLeg.x");

	mPos = D3DXVECTOR3(0.0f, 47.6f, 0.0f);

	EnemyHit = 0;
	AtkFlg = false;
	D3DXMatrixTranslation(&mMatrix1RotY, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&mScale, 1.0f, 1.0f, 1.0f);

	D3DXMatrixTranslation(&mMatrix,0.0f,0.0f,0.0f);
	mMatrix = mScale * mMatrix1RotY * mMatrix;
	D3DXMatrixTranslation(&mHeadMatrix, 0.0f, 0.0f, 0.0f);
	mHeadMatrix = mHeadMatrix * mMatrix;
	D3DXMatrixTranslation(&mLArmMatrix, 0.0f, 0.0f, 0.0f);
	mLArmMatrix = mLArmMatrix * mMatrix;
	D3DXMatrixTranslation(&mRArmMatrix, 0.0f, 0.0f, 0.0f);
	mRArmMatrix = mRArmMatrix * mMatrix;
	D3DXMatrixTranslation(&mLLegMatrix, 0.0f, 0.0f, 0.0f);
	mLLegMatrix = mLLegMatrix * mMatrix;
	D3DXMatrixTranslation(&mRLegMatrix, 0.0f, 0.0f, 0.0f);
	mRLegMatrix = mRLegMatrix * mMatrix;
}

	
	


void CEnemy::End()
{
}

void CEnemy::Update()
{
	D3DXMatrixTranslation(&mMatrix, mPos.x, mPos.y, mPos.z);
	mMatrix = mScale * mMatrix1RotY * mMatrix;
	D3DXMatrixTranslation(&mHeadMatrix, -0.1f, 0.08f, 0.65f);
	mHeadMatrix = mHeadMatrix * mMatrix;
	D3DXMatrixTranslation(&mLArmMatrix, -0.35f, 0.25f, 0.15f);
	mLArmMatrix = mLArmMatrix * mMatrix;
	D3DXMatrixTranslation(&mRArmMatrix, 0.25f, 0.25f, 0.15f);
	mRArmMatrix = mRArmMatrix * mMatrix;
	D3DXMatrixTranslation(&mLLegMatrix, -0.2f, -0.4f, 0.0f);
	mLLegMatrix = mLLegMatrix * mMatrix;
	D3DXMatrixTranslation(&mRLegMatrix, 0.2f, -0.4f, 0.0f);
	mRLegMatrix = mRLegMatrix * mMatrix;
}
	



void CEnemy::Draw3D()
{
	if (mIsaLive) {
		//‘Ì
		KD3D.SetWorldMatrix(&mMatrix);
		BodyMesh->Draw();
		KD3D.SetWorldMatrix(&mHeadMatrix);
		HeadMesh->Draw();
		KD3D.SetWorldMatrix(&mLArmMatrix);
		LArmMesh->Draw();
		KD3D.SetWorldMatrix(&mRArmMatrix);
		RArmMesh->Draw();
		KD3D.SetWorldMatrix(&mLLegMatrix);
		LLegMesh->Draw();
		KD3D.SetWorldMatrix(&mRLegMatrix);
		RLegMesh->Draw();
	}
}

void CEnemy::EnemyKill(int No)
{
    mIsaLive = false;
}
