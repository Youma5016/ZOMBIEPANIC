#include"../KdLibrary/MyLibrary.h"
#include "CCamera.h"



CCamera::CCamera()

{
	KD3D.lpSPrimary->QueryInterface(IID_IDirectSound3DListener8, (LPVOID*)&lpSListener);

	lpSListener->SetRolloffFactor(0.5f/*音の弱まり具合 0～1*/, DS3D_IMMEDIATE);
}


CCamera::~CCamera()
{
	if(lpSListener!=nullptr)lpSListener->Release();

}

/*CMasterCamera * CGameCamera::GetCamera(void)
{
	return this;
}*/

//触らないで
void CCamera::Set(const D3DXVECTOR2& mWindowSize)
{
	
	D3DXMATRIX mView, mProj;

	D3DXVECTOR3 LookPos=Pos+LookVec;
	// 視点行列の設定
	D3DXMatrixLookAtLH(&mView,
		//&D3DXVECTOR3(0.0f, 0.0f, -10.0f),	// カメラの位置
		&Pos,
		//&D3DXVECTOR3(0.0f, 0.0f, 0.0f),	// カメラの視点
		&LookPos,
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f)	// カメラの頭の方向
	);

	// 投影行列の設定
	D3DXMatrixPerspectiveFovLH(&mProj, D3DXToRadian(60), mWindowSize.x / mWindowSize.y, 1.0f, 1000.0f);

	//行列設定
	 KD3D.GetDev()->SetTransform(D3DTS_VIEW, &mView);
	 KD3D.GetDev()->SetTransform(D3DTS_PROJECTION, &mProj);

	 lpSListener->SetPosition(Pos.x, Pos.y, Pos.z, DS3D_IMMEDIATE);
	 lpSListener->SetOrientation(LookVec.x, LookVec.y, LookVec.z, 0, 1, 0, DS3D_IMMEDIATE);

}

//カメラの位置と向いてほしい方向ベクトルを渡す
void CCamera::SetCameraPos(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _LookPos)
{
	Pos = _Pos;
	LookVec = _LookPos-_Pos;
	D3DXVec3Normalize(&LookVec, &LookVec);
}

void CCamera::SetCameraVec(const D3DXVECTOR3& _Pos, const D3DXVECTOR3& _LookVec)
{
	Pos = _Pos;
	LookVec = _LookVec;
	
}


