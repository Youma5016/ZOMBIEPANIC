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

	mPos = { 0.0f, 0.0f, 0.0f };
	mPos2 = { 0.0f, 0.0f, 0.0f };

	mMatrix1.SetTrans(mPos);
	mMatrix2.SetTrans(mPos2);

}

void CTitle::Update()
{

	mPos = { 628, 150, 0 };
	mPos2 = { 628, 600, 0 };

	if (Alpha > 255) {
		Alpha -= 1;
		if (Alpha == 0) {
			Alpha = 0;
		}
	}
	else if (Alpha < 0) {
		Alpha += 1;
		if (Alpha == 255) {
			Alpha = 255;
		}
	}
	mMatrix1.SetTrans(mPos);
	mMatrix2.SetTrans(mPos2);

}

void CTitle::Draw2D()
{

	RECT rcRECT1 = { 0,0, 710,131 };
	SPRITE->SetTransform(&mMatrix1);
	SPRITE->Draw(*mpTexture1, &rcRECT1, &D3DXVECTOR3(710 / 2, 131 / 2, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

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



