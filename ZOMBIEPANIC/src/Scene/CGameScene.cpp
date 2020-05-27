#include"../System/KdLibrary/MyLibrary.h"
#include "../System/FrameBase/CGameFrame.h"

#include "CGameScene.h"

CGameScene::CGameScene()
{

}

CGameScene::~CGameScene()
{
}

void CGameScene::Init()
{
}

int CGameScene::Update()
{
	if (GetKey(VK_SPACE) & 0x8000) {
		FADE.Start(5);
		return TITLE;
	}

	return GAME;
}

void CGameScene::Draw2D()
{

}

void CGameScene::Draw3D()
{

}

void CGameScene::End()
{

}
