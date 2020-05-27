#pragma once

class Result
{
public:
	Result();
	~Result();

	void Init();
	void Update1();
	void Update2();
	void Draw2D1();
	void Draw2D2();
	void End();

private:
	std::shared_ptr<LPDIRECT3DTEXTURE9> mpTexture, mpTexture1, mpTexture2, mpTexture3;
	D3DXMATRIX mMatrix, mMatrix1, mMatrix2;
	int Mode;
};

