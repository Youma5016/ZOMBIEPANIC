#pragma once



class CSceneBase;
class CTitleScene;
class CMapScene;
class CGameScene;
class CShopScene;
class CResultScene;
class CCamera;

class CGameFrame
{
public:

	const bool Initialize(HINSTANCE aHInst, const int aCmdShow);
	void GameLoop();
	const HWND& GetHWND() { return mpHwnd; }

private:
	CGameFrame();
	~CGameFrame();
	const bool CreateWNDCLASS(HINSTANCE aHInst);
	const bool CreateHWND(HINSTANCE aHInst, const int aCmdShow);
	const bool CreateDirectX9();
	void SceneClear();

	HWND					mpHwnd;
	
	   
	WNDCLASS				mWndClass;


	shared_ptr<CSceneBase> nowScene;
	string str;
	bool              mIsFullScreen;
	const D3DXVECTOR2       mWindowSize;
	const string       mAppName;

	int nextscene,nowscene;

	DWORD NowTime, NT;
	DWORD PrevTime, PT;
	int cnt;
	int FPS;


public:
	static CGameFrame& GetInstance()
	{
		static CGameFrame instance;
		return instance;

	}
};
#define FRAME CGameFrame::GetInstance()
#define GETHWND FRAME.GetHWND()
