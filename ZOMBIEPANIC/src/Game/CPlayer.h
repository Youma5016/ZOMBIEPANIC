#pragma once
#include"Anime.h"

enum Pause
{
	Up,
	Right,
	Left
};

class CPlayer : Anime
{

public://公開

	CPlayer();//コンストラクタ
	//生成（メモリの確保）時に呼び出される関数｛Init関数と類似｝

	~CPlayer();//デストラクタ

	void Update(void);
	void Init(LPDIRECT3DDEVICE9 lpD3DDevice, HWND hwnd);
	void Draw3D();
	void Draw2D();
	D3DXMATRIX GetGunMat();
	D3DXMATRIX GetPlayerMat();
	D3DXVECTOR3 GetPlayerPos();
	D3DXVECTOR3 GetPlayerLookPos();
	float GetAngX();
	float GetAngY();
	float GetGunAngX();
	BOOL GetShotFlg() {
		return ShotFlg;
	}
	
	void Release();
	
private://非公開
	//主人公

	LPD3DXMESH          mpMesh;
	D3DXMATRIX			mMatrix;//Body
	D3DXMATRIX			mHeadMatrix;
	D3DXMATRIX			mLArmMatrix;
	D3DXMATRIX			mRArmMatrix;
	D3DXMATRIX			mLLegMatrix;
	D3DXMATRIX			mRLegMatrix;
	D3DXMATRIX			mMatrix1RotX;
	D3DXMATRIX			mMatrix1RotY;
	D3DXVECTOR3			mPos;
	D3DXVECTOR3         PlayerLookPos;
	float				playerAngX,playerAngY,playerAngZ;
	POINT				BasePt;
	//銃
	D3DXMATRIX mGunMat;
	D3DXMATRIX mGunRot;
	D3DXVECTOR3 mGunPos;

	//2D
	std::shared_ptr<LPDIRECT3DTEXTURE9>	mpTexture1;
	D3DXMATRIX          mRockOnMat;
	D3DXVECTOR3			mRockOnPos;
	
	std::shared_ptr<LPDIRECT3DTEXTURE9>	mpTexture2;
	D3DXMATRIX          mEyeMat;
	D3DXVECTOR3			mEyePos;
	
	std::shared_ptr<LPDIRECT3DTEXTURE9>	mpTexture3;
	D3DXMATRIX          mBulletUIMat;
	D3DXMATRIX          mBulletUIPos;

	std::shared_ptr<LPDIRECT3DTEXTURE9>	mpTexture4;
	D3DXMATRIX          mNumberMat;
	D3DXVECTOR3			mNumberPos;

	//アニメーション
	D3DXMATRIX GAStartMat, GAEndMat ,GANowMat;
	
	D3DXMATRIX mREndMat, mLEndMat;
	
	
	float AnimeFrame,GAnimeFrame;
	float WalkAnimeAng;
	//メッシュ
	std::shared_ptr<KdModel>				BodyMesh;
	std::shared_ptr<KdModel>				HeadMesh;
	std::shared_ptr<KdModel>				LArmMesh;
	std::shared_ptr<KdModel>				RArmMesh;
	std::shared_ptr<KdModel>				LLegMesh;
	std::shared_ptr<KdModel>				RLegMesh;


	std::shared_ptr<KdModel>                GunMesh;
	 

	BOOL MoveFlg,ShotFlg,StopFlg;
	Pause p;
	Anime anime;
	float GunAngX;
	
	D3DXMATRIX GArmAngMat,GAngMat;

};