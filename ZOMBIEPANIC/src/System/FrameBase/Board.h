#pragma once
#define	FVF_VERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1)

// ���_���̒�`
struct VERTEX
{
	D3DXVECTOR3 Pos;
	D3DCOLOR Color;
	D3DXVECTOR2 Tex;
};



class Board
{
public:
	Board();
	~Board();
	void Update(const int *Side, const int *Virtical);
	virtual void Draw() = 0;
	void SafeRelease(LPDIRECT3DTEXTURE9& LoadTex);

	virtual void setTexParam(std::string Path, int W, int H, D3DCOLOR color) 
	{
		mPath = Path;
		mW = W;
		mH = H;
		mColor = color;
	}



protected:
	VERTEX v[4];
	D3DXMATRIX vMat;
	//�|���̃T�C�Y
	D3DXVECTOR3 mSize;

	//�e�N�X�`���֌W�̕ϐ�
	std::string mPath = "";
	int mW = 0, mH = 0;
	D3DCOLOR mColor = 0;

};

