#include"../System/KdLibrary/MyLibrary.h"
#include "CField.h"






#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


CField::CField()
	: mMatrix()
	,mMatrixTrans1()
	,mPos()
{
}

CField::~CField()
{

}

void CField::Init()
{
	BuildMesh = RESOURCE_MNG.GetModel("ZOMBIEPANIC/Resource/3DModelLowPolyCITY_8.x");
	SkyMesh = RESOURCE_MNG.GetModel("ZOMBIEPANIC/Resource/3DModel/Red_Sky.x");

	GroundTex = RESOURCE_MNG.GetTexture("Ground.png");
    //Œš•¨
	mPos = D3DXVECTOR3(0, 0, 0);
	D3DXMatrixTranslation(&mMatrix, 0, 0, 0);
	D3DXMatrixTranslation(&mMatrixTrans1, 0, 0, 0);
	//‹ó
	mSkyPos = D3DXVECTOR3(0, 0, 0);
	D3DXMatrixTranslation(&mSkyMat, 0, 0, 0);
	D3DXMatrixTranslation(&mSkyTrans, 0, 0, 0);
	D3DXMatrixTranslation(&GroundTrans, 0, 0, 0);
	D3DXMatrixTranslation(&GroundMat, 0, 0, 0);
	
}


void CField::Update()
{

	D3DXMatrixScaling(&mMatrixTrans1, 50, 50, 50);
	D3DXMatrixTranslation(&mMatrix, mPos.x, mPos.y, mPos.z);

	mMatrix = mMatrixTrans1*mMatrix;
	D3DXMatrixScaling(&mSkyTrans, 20, 20, 20);
	D3DXMatrixTranslation(&mSkyMat, mSkyPos.x, mSkyPos.y, mSkyPos.z);
	mSkyMat = mSkyTrans * mSkyMat;


}

void CField::Draw2D()
{

}

void CField::Draw3D() {


	D3DEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DEV->SetFVF(FVF_VERTEX);

	D3DEV->SetTexture(0, *GroundTex);
	//êŠ
	v[0].Pos = D3DXVECTOR3(-200.0f, 0, -200.0f);
	v[1].Pos = D3DXVECTOR3(-200.0f, 0, 200.0f);
	v[2].Pos = D3DXVECTOR3(200.0f, 0, 200.0f);
	v[3].Pos = D3DXVECTOR3(200.0f, 0, -200.0f);

	//–§“x
	v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	v[1].Tex = D3DXVECTOR2(100.0f, 0.0f);
	v[2].Tex = D3DXVECTOR2(100.0f, 100.0f);
	v[3].Tex = D3DXVECTOR2(0.0f, 100.0f);

	D3DXMatrixTranslation(&GroundMat, 0.0f, 0.0f, 0.0f);
	KD3D.SetWorldMatrix(&GroundMat);
	D3DEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));

	D3DEV->SetRenderState(D3DRS_LIGHTING, TRUE);

	KD3D.SetWorldMatrix(&mMatrix);
	BuildMesh->Draw();

	KD3D.SetWorldMatrix(&mSkyMat);
	SkyMesh->Draw();

	v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
}

void CField::End()
{
	GroundTex = nullptr;
}

