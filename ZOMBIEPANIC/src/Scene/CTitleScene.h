#pragma once
#include"../System/FrameBase/CSceneBase.h"
class CTitle;

class CTitleScene : public CSceneBase
{
public:
	CTitleScene();
	~CTitleScene();

	void Init()override;
	int Update()override;
	void Draw2D()override;
	void Draw3D()override;
	int GetID()override { return TITLE; };
	void End()override;
private:
	std::shared_ptr<CTitle>title = nullptr;
};