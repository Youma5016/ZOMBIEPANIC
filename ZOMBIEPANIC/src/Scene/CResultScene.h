#pragma once
#include"../System/FrameBase/CSceneBase.h"
class CGameProc;
class Result;


class CResultScene : public CSceneBase
{
public:
	CResultScene();
	~CResultScene();

	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override;
	int GetID()override { return RESULT; };
	void End()override;

private:
	std::shared_ptr<LPDIRECT3DTEXTURE9>ResultTex=nullptr;
	KdMatrix mResultMat;
};

