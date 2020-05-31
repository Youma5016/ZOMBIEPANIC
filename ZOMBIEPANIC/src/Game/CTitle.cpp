#include"../System/KdLibrary/MyLibrary.h"
#include"CTitle.h"

CTitle::CTitle()
	
{
	
}

CTitle::~CTitle()
{
	
}


void CTitle::Init()
{
	mpTexture1 = RESOURCE_MNG.GetTexture("Title.png");
	mpTexture2 = RESOURCE_MNG.GetTexture("PRESSENTER.png");


	D3DXMatrixTranslation(&mMatrix1, 0.0f, 0.0f, 0.0f);
	D3DXMatrixTranslation(&mMatrix2, 0.0f, 0.0f, 0.0f);
	
}

void CTitle::Update()
{
	    if (Alpha >= 200) {
			Alpha -= 3;
		}
		if (Alpha <= 150) {
			Alpha += 3;
		}
	D3DXMatrixTranslation(&mMatrix1, 1280 / 2, 720 / 3.0, 0);
	D3DXMatrixTranslation(&mMatrix2, 1280 / 1.9, 720/1.5, 0);
}

void CTitle::Draw2D()
{

	RECT rcRECT1 = { 0,0, 780,180 };
	SPRITE->SetTransform(&mMatrix1);
	SPRITE->Draw(*mpTexture1, &rcRECT1, &D3DXVECTOR3(669 / 2, 121 / 2, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

	RECT rcRECT2 = { 0,0, 580,64 };
	SPRITE->SetTransform(&mMatrix2);
	SPRITE->Draw(*mpTexture2, &rcRECT2, &D3DXVECTOR3(580 / 2, 64 / 2, 0), NULL, D3DCOLOR_ARGB(Alpha+200, 255, 255, 255));
	
}

void CTitle::Draw3D()
{
}

void CTitle::End()
{
	mpTexture1 = nullptr;
	mpTexture2 = nullptr;
}



