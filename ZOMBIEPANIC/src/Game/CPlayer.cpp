#include"../System/KdLibrary/MyLibrary.h"
#include"CEnemy.h"
#include"CBullet.h"
#include "CPlayer.h"
#define   CT  0



CPlayer::CPlayer()
	: mpTexture1(nullptr)
	, mpTexture2(nullptr)
	, mMatrix()
	, mMatrix1RotX()
	, mMatrix1RotY()
	, mHeadMatrix()
	, mLArmMatrix()
	, mRArmMatrix()
	, mLLegMatrix()
	, mRLegMatrix()
	, mPos(0.0f, 47.6f, 0.0f)
	//, mPos(0.0f, 1.0f, -50.0f)
	, PlayerLookPos()
	, playerAngX()
	, playerAngY()
	, playerAngZ()
	//e
	, mGunMat()
	, mGunPos()
	, mGunRot()
	//Æ€
	, mRockOnPos()
	, mRockOnMat()
	, mEyeMat()
	, mEyePos()
	//ƒAƒjƒ[ƒVƒ‡ƒ“
	, GAStartMat()
	, GAEndMat()
	, GANowMat()
	,mREndMat()
	,mLEndMat()
	,WalkAnimeAng()
	{
}


void CPlayer::Init(LPDIRECT3DDEVICE9 lpD3DDevice,HWND hwnd)
{
	mpTexture1 = RESOURCE_MNG.GetTexture("data/Rockon.png");
	mpTexture2 = RESOURCE_MNG.GetTexture("data/Eye.png");
	mpTexture3 = RESOURCE_MNG.GetTexture("data/UI.png");
	mpTexture4 = RESOURCE_MNG.GetTexture("data/NUMBER.png");
	
	HeadMesh = RESOURCE_MNG.GetModel("data/anime_boy_Head.x");
	BodyMesh = RESOURCE_MNG.GetModel("data/anime_boy_Body.x");
	LArmMesh = RESOURCE_MNG.GetModel("data/anime_boy_LArm.x");
	RArmMesh = RESOURCE_MNG.GetModel("data/anime_boy_RArm.x");
	LLegMesh = RESOURCE_MNG.GetModel("data/anime_boy_LLeg.x");
	RLegMesh = RESOURCE_MNG.GetModel("data/anime_boy_RLeg.x");
	RLegMesh = RESOURCE_MNG.GetModel("data/PT320_1.x");


	
	BasePt.x = 1280 / 2;
	BasePt.y = 720/3+120;
	ClientToScreen(hwnd, &BasePt);
	SetCursorPos(BasePt.x, BasePt.y);
	D3DXMatrixTranslation(&mMatrix, 0, 0, -10);
	D3DXMatrixTranslation(&mHeadMatrix, 0, 0, -10);
	D3DXMatrixTranslation(&mLArmMatrix, 0, 0, -10);
	D3DXMatrixTranslation(&mRArmMatrix, 0, 0, -10);
	D3DXMatrixTranslation(&mLLegMatrix, 0, 0, -10);
	D3DXMatrixTranslation(&mLLegMatrix, 0, 0, -10);
	D3DXMatrixTranslation(&mGunMat, 0, 0, -10);
	D3DXMatrixTranslation(&mRockOnMat, 0, 0, 0.0f);
	D3DXMatrixTranslation(&mEyeMat, 0, 0, 0.0f);
	D3DXMatrixTranslation(&mBulletUIMat, 0, 0, 0.0f);
	D3DXMatrixTranslation(&mNumberMat, 0, 0, 0.0f);
	D3DXMatrixTranslation(&GAStartMat, 0, 0, 0.0f);
	D3DXMatrixTranslation(&mREndMat, 0, 0, -10);
	D3DXMatrixTranslation(&mLEndMat, 0, 0, -10);
	AnimeFrame = 0;
	p = Up;
	D3DXMatrixRotationYawPitchRoll(&GArmAngMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
	D3DXMatrixRotationYawPitchRoll(&GAngMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
}



CPlayer::~CPlayer()
{
}

void CPlayer::Update(void)
{



	POINT Pt;
	GetCursorPos(&Pt);
	playerAngY += (Pt.x - BasePt.x) / 4.0f;
	playerAngX += (Pt.y - BasePt.y) / 4.0f;
	SetCursorPos(BasePt.x, BasePt.y);
	if (playerAngX > 15)playerAngX = 15;
	if (playerAngX < -20)playerAngX = -20;
	/*if (playerAngX > 180)playerAngX = 180;
	if (playerAngX < -180)playerAngX = -180;
	*/
	
	if (GetAsyncKeyState('W') & 0x8000) {
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(playerAngY));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0.0f, 0.0f, 0.1f), &RotMat);
		mPos += Vec;
	}
	if (GetAsyncKeyState('S') & 0x8000) {
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(playerAngY));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0.0f, 0.0f, -0.1f), &RotMat);
		mPos += Vec;
	}
	if (GetAsyncKeyState('A') & 0x8000) {
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(playerAngY));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(-0.1f, 0.0f, 0.0f), &RotMat);
		mPos += Vec;
	}
	if (GetAsyncKeyState('D') & 0x8000) {
		D3DXMATRIX RotMat;
		D3DXMatrixRotationY(&RotMat, D3DXToRadian(playerAngY));
		D3DXVECTOR3 Vec;
		D3DXVec3TransformCoord(&Vec, &D3DXVECTOR3(0.1f, 0.0f, 0.0f), &RotMat);
		mPos += Vec;
	}

	if (GetAsyncKeyState('P') & 0x8000) {
		mPos.y += 1;
	}
	if (GetAsyncKeyState('L') & 0x8000) {
		mPos.y -= 1;
	}

	D3DXMatrixRotationY(&mMatrix1RotY, D3DXToRadian(playerAngY));
	D3DXMatrixRotationX(&mMatrix1RotX, D3DXToRadian(playerAngX));
	D3DXMatrixTranslation(&mMatrix, mPos.x, mPos.y, mPos.z);
	mMatrix = mMatrix1RotY * mMatrix;

	D3DXMatrixTranslation(&mHeadMatrix, 0.0f, 0.1f, 0.0f);
	mHeadMatrix = mHeadMatrix * mMatrix;

	D3DXMatrixTranslation(&mLArmMatrix, -0.2f, 0.05f, 0.0f);
	mLArmMatrix = mLArmMatrix * mMatrix;

	D3DXMatrixTranslation(&mRArmMatrix, 0.2f, 0.05f, 0.0f);
	mRArmMatrix = GArmAngMat * mRArmMatrix * mMatrix;

	D3DXMatrixTranslation(&mLLegMatrix, -0.09f, -0.27f, 0.0f);
	mLLegMatrix = mLLegMatrix * mMatrix;

	D3DXMatrixTranslation(&mRLegMatrix, 0.07f, -0.27f, 0.0f);
	mRLegMatrix = mRLegMatrix * mMatrix;

	D3DXMatrixRotationYawPitchRoll(&GAngMat, D3DXToRadian(0), D3DXToRadian(80), D3DXToRadian(0));
	D3DXMatrixTranslation(&mGunMat, 0.18f, -0.4f, 0.0f);
	mGunMat = GAngMat * mGunMat* mRArmMatrix;


	MoveFlg = false;
	if (GetAsyncKeyState('W') & 0x8000) {
		if (MoveFlg == false)
		{
			MoveFlg = true;
			if (!p == Right)
			{
				p = Right;
			}

		}
		D3DXMATRIX RLegMat;
		D3DXMATRIX LLegMat;
		switch (p)
		{
		case Right:
			D3DXMatrixRotationYawPitchRoll(&RLegMat, D3DXToRadian(-20), D3DXToRadian(-30), D3DXToRadian(0));
			D3DXMatrixRotationYawPitchRoll(&LLegMat, D3DXToRadian(-20), D3DXToRadian(30), D3DXToRadian(0));
			break;
		case Left:
			D3DXMatrixRotationYawPitchRoll(&RLegMat, D3DXToRadian(-20), D3DXToRadian(30), D3DXToRadian(0));
			D3DXMatrixRotationYawPitchRoll(&LLegMat, D3DXToRadian(-20), D3DXToRadian(-30), D3DXToRadian(0));
			break;
		}

		mREndMat = RLegMat * mRLegMatrix;
		mLEndMat = LLegMat * mLLegMatrix;

		AnimeFrame = sin(D3DXToRadian(WalkAnimeAng));
		WalkAnimeAng += 10;
		if (WalkAnimeAng >= 180)
		{
			WalkAnimeAng = 0;

			if (p == Right) {
				p = Left;
			}
			else {
				p = Right;
			}
		}
	}
	

	if (GetAsyncKeyState('S') & 0x8000) {
		if (MoveFlg == false)
		{
			MoveFlg = true;
			if (!p == Right)
			{
				p = Right;
			}

		}
		D3DXMATRIX RLegMat;
		D3DXMATRIX LLegMat;
		switch (p)
		{
		case Right:
			D3DXMatrixRotationYawPitchRoll(&RLegMat, D3DXToRadian(-20), D3DXToRadian(-30), D3DXToRadian(0));
			D3DXMatrixRotationYawPitchRoll(&LLegMat, D3DXToRadian(-20), D3DXToRadian(30), D3DXToRadian(0));
			break;
		case Left:
			D3DXMatrixRotationYawPitchRoll(&RLegMat, D3DXToRadian(-20), D3DXToRadian(30), D3DXToRadian(0));
			D3DXMatrixRotationYawPitchRoll(&LLegMat, D3DXToRadian(-20), D3DXToRadian(-30), D3DXToRadian(0));
			break;
		}

		mREndMat = RLegMat * mRLegMatrix;
		mLEndMat = LLegMat * mLLegMatrix;

		AnimeFrame = sin(D3DXToRadian(WalkAnimeAng));
		WalkAnimeAng -= 10;
		if (WalkAnimeAng <= 0)
		{
			WalkAnimeAng = 180;

			if (p == Right) {
				p = Left;
			}
			else {
				p = Right;
			}
		}
	}

	if (MoveFlg == false)
	{
		AnimeFrame -= 0.01f;
		if (AnimeFrame < 0) {
			AnimeFrame = 0;
		}

		D3DXMATRIX RLegMat;
		D3DXMatrixRotationYawPitchRoll(&RLegMat, D3DXToRadian(-20), D3DXToRadian(0), D3DXToRadian(0));
		mREndMat = RLegMat * mRLegMatrix;
		D3DXMATRIX LLegMat;
		D3DXMatrixRotationYawPitchRoll(&LLegMat, D3DXToRadian(-20), D3DXToRadian(0), D3DXToRadian(0));
		mLEndMat = LLegMat * mLLegMatrix;

	}

	mRLegMatrix = anime.QuaProc(mRLegMatrix, mREndMat, AnimeFrame);
	mLLegMatrix = anime.QuaProc(mLLegMatrix, mLEndMat, AnimeFrame);

	static bool RFlg = false;
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
    	if (RFlg == false)
		{
			GAnimeFrame = 0;
			RFlg = true;
		}
		GAStartMat = GArmAngMat;
		GunAngX = playerAngX - 80;
		D3DXMatrixRotationYawPitchRoll(&GAEndMat, D3DXToRadian(0), D3DXToRadian(GunAngX), D3DXToRadian(0));
		GAnimeFrame += 0.01f;
		if (GAnimeFrame > 1) {
			GAnimeFrame = 1;
		}
	}
	else {
		if (RFlg == true)
		{
			RFlg = false;
			D3DXMatrixRotationYawPitchRoll(&GAStartMat, D3DXToRadian(0), D3DXToRadian(0), D3DXToRadian(0));
			GAEndMat = GArmAngMat;
		}

		GAnimeFrame -= 0.03f;
		if (GAnimeFrame < 0) {
			GAnimeFrame = 0;
		}
	}
	if (RFlg) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			ShotFlg = true;
		}
	}
	

	GArmAngMat = anime.QuaProc(GAStartMat, GAEndMat, GAnimeFrame);


	D3DXMatrixTranslation(&mEyeMat, (float)BasePt.x - 100, (float)BasePt.y, 0.0f);
	D3DXMatrixTranslation(&mRockOnMat, (float)BasePt.x - 100, (float)BasePt.y, 0.0f);
	D3DXMatrixTranslation(&mBulletUIMat, 1280.0f/1.1f, 720.0f/1.2, 0.0f);
	D3DXMatrixTranslation(&mNumberMat, 1280.0f/1.1f, 720.0f/1.2, 0.0f);
}

void CPlayer::Draw3D()
{
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
	//e
	KD3D.SetWorldMatrix(&mGunMat);
	GunMesh->Draw();
}

void CPlayer::Draw2D()
{

	RECT rcRECT1 = { 0,0, 64,64 };
	RECT rcRECT2 = { 0,0, 32,32 };
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000) {
	    SPRITE->SetTransform(&mRockOnMat);
		SPRITE->Draw(*mpTexture1, &rcRECT1, &D3DXVECTOR3(64 / 2, 64 / 2, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}else
	{
	    SPRITE->SetTransform(&mEyeMat);
		SPRITE->Draw(*mpTexture2, &rcRECT2, &D3DXVECTOR3(32 / 2, 32 / 2, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	RECT rcRECT3 = { 0,0, 300,300 };
	SPRITE->SetTransform(&mBulletUIMat);
	SPRITE->Draw(*mpTexture3, &rcRECT3, &D3DXVECTOR3(300 / 2, 300 / 2, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));
	RECT rcRECT4 = { 0,0, 35,95 };
	SPRITE->SetTransform(&mNumberMat);
	SPRITE->Draw(*mpTexture4, &rcRECT4, &D3DXVECTOR3(35 / 2, 95/ 2, 0), NULL, D3DCOLOR_ARGB(255, 255, 255, 255));

}

D3DXMATRIX CPlayer::GetGunMat()
{
	return mGunMat;
}

D3DXMATRIX CPlayer::GetPlayerMat()
{
	return mMatrix;
}

float CPlayer::GetAngX()
{
	return playerAngX;
}

 
float CPlayer::GetAngY()
{
	return playerAngY;
}

float CPlayer::GetGunAngX()
{
	return GunAngX;
}


D3DXVECTOR3 CPlayer::GetPlayerPos()
{
	return mPos;
}

D3DXVECTOR3 CPlayer::GetPlayerLookPos()
{
	return PlayerLookPos;
}


void CPlayer::Release()
{
}



