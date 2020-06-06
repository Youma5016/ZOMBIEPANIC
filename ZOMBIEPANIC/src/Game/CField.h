#pragma once


//–Ú‚Ì‘O‚É‚ ‚é‚Ì‚ª‹C‚É‚È‚é
//‘O‚É”à,‘¼‚Ì‚Æ‚±‚ë‚ÉŒ®

class CField
{
public:
	CField();
	~CField();

	void Init();
	void Update();
	void Draw2D();
	void Draw3D();
	void End();

	D3DXMATRIX GetBuildMat(void) { return mMatrix; }
	std::shared_ptr < KdModel>      GetMesh(void) { return BuildMesh; }
private:

	D3DXMATRIX			mMatrix;
	D3DXMATRIX			mMatrixTrans1;
	D3DXVECTOR3			mPos;


	D3DXMATRIX              mSkyMat;
	D3DXMATRIX              mSkyTrans;
	D3DXVECTOR3				mSkyPos;


	std::shared_ptr < LPDIRECT3DTEXTURE9>		GroundTex;
	D3DXMATRIX              GroundMat, GroundTrans, GroundRot;

	std::shared_ptr<KdModel>               BuildMesh;
	std::shared_ptr<KdModel>               SkyMesh;

	VERTEX					v[4];

};