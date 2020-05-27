#pragma once

//===============================================
//
// 基本
//
//===============================================
#pragma comment(lib,"winmm.lib")

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <commctrl.h>
#include <ctime>
#include<dsound.h>

//===============================================
//
// DirectX9
//
//===============================================
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dsound.lib")

#define DIRECTINPUT_VERSION 0x0800

#include "d3d9.h"
#include "d3dx9.h"
#include "dsound.h"
#include "dinput.h"


//===============================================
//
// STL
//
//===============================================
#include <map>
#include <unordered_map>
#include <map>
#include <string>
#include <array>
#include <vector>
#include <stack>
#include <list>
#include <iterator>
#include <queue>
#include <algorithm>
#include <memory>
#include <random>
#include <fstream>
#include <iostream>
#include <sstream>
#include <functional>
#include <thread>
#include <atomic>
#include <mutex>
#include <future>


//===============================================
//
// KdLibrary
//
//===============================================

// 便利汎用機能
#include "KdHelper.h"
// Direct3D
#include "KdDirect3D.h"
#include"KdResourceManager.h"

#include"KdMath.h"//優先度高い

#include"CCamera.h"//カメラ


#include "KdModel.h"
#include "../FrameBase/wavread.h"
#include"../FrameBase/Fade.h"

#define GetKey GetAsyncKeyState
#define MESH m_pModel->GetMesh()
enum Scene
{
	TITLE,
	GAME,
	RESULT
};

struct CLONEVERTEX
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR3 Normal;
	D3DXVECTOR2 Tex;
};

struct VERTEX
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};

using namespace std;