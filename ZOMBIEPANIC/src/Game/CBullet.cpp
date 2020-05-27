#include"../System/KdLibrary/MyLibrary.h"
#include"CPlayer.h"
#include"CBullet.h"



#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)


CBullet::CBullet()
	:mpTexture()
	,mMatrix()
	,TexSize()
{
}

CBullet::~CBullet()
{
}

void CBullet::Init(LPDIRECT3DDEVICE9 lpD3DDevice,D3DXVECTOR3 HitPos)
{
	mpTexture = RESOURCE_MNG.GetTexture("data/BulletMarks.png");
	D3DXMatrixTranslation(&mMatrix, HitPos.x, HitPos.y, HitPos.z);
}

void CBullet::End() {
}

void CBullet::Update()
{

		
}



void CBullet::Draw3D()
{
	D3DEV->SetRenderState(D3DRS_LIGHTING, FALSE);
	D3DEV->SetFVF(FVF_VERTEX);

	D3DEV->SetTexture(0, *mpTexture);
	v[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);;
	v[1].Pos = D3DXVECTOR3(0.3f, 0.0f, 0.0f);
	v[2].Pos = D3DXVECTOR3(0.3f, 0.3f, 0.0f);
	v[3].Pos = D3DXVECTOR3(0.0f, 0.3f, 0.0f);

	v[0].Tex = D3DXVECTOR2(0.0f, 0.0f);
	v[1].Tex = D3DXVECTOR2(1.0f, 0.0f);
	v[2].Tex = D3DXVECTOR2(1.0f, 1.0f);
	v[3].Tex = D3DXVECTOR2(0.0f, 1.0f);

	v[0].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[1].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[2].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	v[3].Color = D3DCOLOR_ARGB(255, 255, 255, 255);
	KD3D.SetWorldMatrix (&mMatrix);
	D3DEV->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(VERTEX));
}


