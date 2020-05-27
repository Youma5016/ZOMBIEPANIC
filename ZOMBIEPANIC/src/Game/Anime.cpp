#include"../System/KdLibrary/MyLibrary.h"
#include"Anime.h"




Anime::Anime()
{
}

Anime::~Anime()
{
}

D3DXMATRIX Anime::QuaProc(D3DXMATRIX StartMat, D3DXMATRIX EndMat, float AnimeFrame)
{
	D3DXQUATERNION StartQua, EndQua, NowQua;
	D3DXQuaternionRotationMatrix(&StartQua, &StartMat);
	D3DXQuaternionRotationMatrix(&EndQua, &EndMat);
	D3DXQuaternionSlerp(&NowQua, &StartQua, &EndQua, AnimeFrame);
	D3DXMatrixRotationQuaternion(&NowMat, &NowQua);
	D3DXVECTOR3 StartPos, EndPos, NowPos;
	StartPos = D3DXVECTOR3(StartMat._41, StartMat._42, StartMat._43);
	EndPos = D3DXVECTOR3(EndMat._41, EndMat._42, EndMat._43);
	D3DXVec3Lerp(&NowPos, &StartPos, &EndPos, AnimeFrame);
	NowMat._41 = NowPos.x;
	NowMat._42 = NowPos.y;
	NowMat._43 = NowPos.z;

	return NowMat;
	
}


