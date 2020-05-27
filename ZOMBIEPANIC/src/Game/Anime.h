#pragma once
class Anime
{
public:
	Anime();
	~Anime();

	D3DXMATRIX QuaProc(D3DXMATRIX StartMat, D3DXMATRIX EndMat,float AnimeFrame);
	
private:
	D3DXMATRIX StartMat, EndMat, NowMat;
	float AnimeFrame;
};


