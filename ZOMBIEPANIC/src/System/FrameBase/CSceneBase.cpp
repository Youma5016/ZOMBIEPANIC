#include"../KdLibrary/MyLibrary.h"
#include "CSceneBase.h"
#include"wavread.h"





CSceneBase::CSceneBase()

{





}


CSceneBase::~CSceneBase()
{

}

void CSceneBase::Init()
{
}

int CSceneBase::Update()
{
	return 0;

}

void CSceneBase::Draw2D()
{
	SPRITE->Begin(D3DXSPRITE_ALPHABLEND);


	SPRITE->End();
}

void CSceneBase::Draw3D()
{
}



