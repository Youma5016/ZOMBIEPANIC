#pragma once

class CGameScene;



class CBullet
{
public:
	CBullet();
	~CBullet();
	void Init(LPDIRECT3DDEVICE9 lpD3DDevice,D3DXVECTOR3 HitPos);
	void End();
	void Update();
	void Draw3D();
private:
	
	float TexSize;
	D3DXMATRIX mMatrix;
	std::shared_ptr<LPDIRECT3DTEXTURE9>	mpTexture;

	VERTEX v[4];
};

