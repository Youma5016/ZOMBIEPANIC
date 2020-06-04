#include "../KdLibrary/MyLibrary.h"
//#include<cassert>
#include"../FrameBase/CGameFrame.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "winmm.lib")

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev,
    LPSTR lpszCmdParam, int nCmdshow)
{
    MSG msg;

   // CGameFrame gameFrame;
    const bool result = FRAME.Initialize(hInst, nCmdshow);
    if( result == false )
    {
        _ASSERT_EXPR( 0 , L"CGameFrame Initialize Error " );
        return 0;
    }

     // メモリリークを知らせる
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    // COM初期化
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    

    while (1) {
        if (PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
        {
            if (!GetMessage(&msg, NULL, 0, 0))
                break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            FRAME.GameLoop();
        }
    }
    // COM解放
    CoUninitialize();
    return (int)msg.wParam;
}