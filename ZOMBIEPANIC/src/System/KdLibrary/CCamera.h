#pragma once


class CCamera {
private:
	CCamera();
	~CCamera();


public:
	//CMasterCamera* GetCamera(void)override ;

	 void Set( const D3DXVECTOR2& mWindowSize);
	 void SetCameraPos(const D3DXVECTOR3& Pos, const D3DXVECTOR3& LookPos);
	 
	 void SetCameraVec(const D3DXVECTOR3& Pos, const D3DXVECTOR3& LookVec);

public:
	static CCamera& GetInstance()
	{
		static CCamera instance;
		return instance;

	}

	LPDIRECTSOUND3DLISTENER8 lpSListener;

private:

	D3DXVECTOR3	Pos;

	D3DXVECTOR3	LookVec;

	D3DXVECTOR3	HeadPos;


	D3DXVECTOR3 m_1Rot;
	D3DXVECTOR3 m_2Rot;
	D3DXVECTOR3 m_3Rot;

	float		Ang;
	D3DXMATRIX Rot;


	bool type;


};
#define CAMERA CCamera::GetInstance()

