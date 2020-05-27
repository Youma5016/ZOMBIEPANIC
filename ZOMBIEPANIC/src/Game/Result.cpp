#include"../System/KdLibrary/MyLibrary.h"
#include"Result.h"


Result::Result()
	:mpTexture(nullptr)
	, mpTexture1(nullptr)
	, mpTexture2(nullptr)
	, mpTexture3(nullptr)
	, mMatrix()
	, mMatrix1()
	, mMatrix2()
	, Mode()
{
}

Result::~Result()
{

}

void Result::Init()
{
	mpTexture  = RESOURCE_MNG.GetTexture("data/Clear.png");
	mpTexture1 = RESOURCE_MNG.GetTexture("data/GameOver.png");
	mpTexture2 = RESOURCE_MNG.GetTexture("data/Retry.png");
	mpTexture3 = RESOURCE_MNG.GetTexture("data/NEXT.png");
}

void Result::Update1()
{
	D3DXMatrixTranslation(&mMatrix, 1280.0f / 2.0f, 720.0f / 5.0f, 0.0f);
	D3DXMatrixTranslation(&mMatrix1, 1280.0f / 3.0f, 720.0f / 1.05f, 0.0f);
	D3DXMatrixTranslation(&mMatrix2, 1280.0f / 1.2f, 720.0f / 1.05f, 0.0f);
}
void Result::Update2()
{
	D3DXMatrixTranslation(&mMatrix, 1280.0f / 2.0f, 720.0f / 3.0f, 0.0f);
	D3DXMatrixTranslation(&mMatrix1, 1280.0f / 3.0f, 720.0f / 1.05f, 0.0f);
	D3DXMatrixTranslation(&mMatrix2, 1280.0f / 1.2f, 720.0f / 1.05f, 0.0f);
}

void Result::Draw2D1()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	RECT rcRECT = { 0,0,320,132 };
	SPRITE->SetTransform(&mMatrix);
	SPRITE->Draw(*mpTexture, &rcRECT, &D3DXVECTOR3(320 / 2, 132 / 2, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	SPRITE->SetTransform(&mMatrix1);
	SPRITE->Draw(*mpTexture3, &rcRECT, &D3DXVECTOR3(320 / 2, 132 / 2, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	SPRITE->End();
}
void Result::Draw2D2()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);

	RECT rcRECT1 = { 0,0,539,132 };
	SPRITE->SetTransform(&mMatrix);
	SPRITE->Draw(*mpTexture1, &rcRECT1, &D3DXVECTOR3(539 / 2, 132 / 2, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	
	RECT rcRECT2 = { 0,0,320,132 };
	SPRITE->SetTransform(&mMatrix1);
	SPRITE->Draw(*mpTexture2, &rcRECT2, &D3DXVECTOR3(320 / 2, 132 / 2, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	

	SPRITE->End();
}

void Result::End()
{
}
