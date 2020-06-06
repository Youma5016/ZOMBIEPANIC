#pragma once
#include"../System/FrameBase/GameObject.h"

class  CTitle:GameObject
{
public:
	 CTitle();
	~ CTitle();

	void Init()override;
	void Update()override;
	void Draw2D() override;
	void Draw3D() override;
	void End()override;

private:
	std::shared_ptr<LPDIRECT3DTEXTURE9>	mpTexture1, mpTexture2;
	KdMatrix mMatrix1,mMatrix2;
	KdVec3 mPos;
	KdVec3 mPos2;

	int Alpha;
};

