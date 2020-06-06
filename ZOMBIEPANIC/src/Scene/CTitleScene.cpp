#include"../System/KdLibrary/MyLibrary.h"
#include"../Game/CTitle.h"
#include"../Game/CField.h"
#include "CTitleScene.h"

CTitleScene::CTitleScene()
{


}

CTitleScene::~CTitleScene()
{
}

void CTitleScene::Init()
{
	//field = std::make_shared<CField>();
	//field->Init();
	
	title = std::make_shared<CTitle>();
	title->Init();
	CAMERA.SetCameraPos(D3DXVECTOR3(0, 2, -5), {0,0,0});

}

int CTitleScene::Update()
{
	title->Update();
	//field->Update();
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
	//field->Draw3D();
}

void CTitleScene::End()
{
	//field->End();
	//field = nullptr;
	title->End();
	title = nullptr;
}
