#include"../System/KdLibrary/MyLibrary.h"
#include"../Game/CTitle.h"
#include "CTitleScene.h"

CTitleScene::CTitleScene()
{


}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Init()
{
	title = std::make_shared<CTitle>();
	title->Init();
}

int CTitleScene::Update()
{
	title->Update();
	
	//ƒV[ƒ“Ø‚è‘Ö‚¦
	if (GetKey(VK_RETURN) & 0x8000)
	{
		FADE.Start(10);
		return GAME;
	}
	return TITLE;
}

void CTitleScene::Draw2D()
{
	title->Draw2D();
}

void CTitleScene::Draw3D()
{
}

void CTitleScene::End()
{
	title->End();
}
