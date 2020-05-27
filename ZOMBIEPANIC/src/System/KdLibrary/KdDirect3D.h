#pragma once

//==========================================================================================================
//
// �Ȉ�Direct3D����N���X
//	Direct3D9�ɕK�v�ȕϐ���A�悭�s��������܂Ƃ߂Ă���B
//
//==========================================================================================================
class KdDirect3D {
public:
	//=============================================
	//
	// �擾�n
	//
	//=============================================
	// D3D�I�u�W�F�N�g�擾
	LPDIRECT3D9EX			GetD3D(){ return m_lpD3D; }
	// D3D�f�o�C�X�擾
	LPDIRECT3DDEVICE9	GetDev(){ return m_lpD3DDev;}
	// D3D�p�����[�^�擾
	D3DPRESENT_PARAMETERS*	GetD3DPP(){return &m_d3dpp;}

	// �f�o�C�X���擾
	D3DCAPS9*				GetCaps(){return &m_Caps;}

	// X�𑜓x�擾(��ʂ̕�)
	int						GetRezoW() const {return m_d3dpp.BackBufferWidth;}
	// Y�𑜓x�擾(��ʂ̍�)
	int						GetRezoH() const {return m_d3dpp.BackBufferHeight;}
	//�T�E���h�֘A�̃f�o�C�X����ϐ�
	LPDIRECTSOUND8 lpDSound;
	LPDIRECTSOUNDBUFFER lpSPrimary;

	LPD3DXSPRITE& GetSprite() { return mpSprite; } 	// �X�v���C�g
	LPD3DXFONT& GetFont() { return mpFont; }		// �t�H���g
	LPDIRECTSOUND8& GetlpDSound() { return lpDSound; }

	void LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string &Path, int W, int H, const D3DCOLOR Color);
	void LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string &Path, const D3DCOLOR Color);
	void LoadTexture(LPDIRECT3DTEXTURE9* lpTex, const std::string &Path);

	//=============================================
	// ������
	//=============================================
	bool Init(HWND hWnd, int width, int height, bool fullscreen, std::string& errorMsg);


	//=============================================
	// ���
	//=============================================
	void Release();

	//=============================================
	// �E�B���h�E/�t���X�N���[���؂�ւ�
	//=============================================
	bool ChangeFullScreenMode();

	//=============================================
	// �X�e�[�g�ݒ�
	//=============================================
	// ��{�I�ȃ����_�[�X�e�[�g���̐ݒ�
	void SetDefaultState();

	//=============================================
	// �s��Z�b�g
	//=============================================
	// ���[���h�ϊ��s����Z�b�g
	void SetWorldMatrix(const D3DXMATRIX* m) {
		m_lpD3DDev->SetTransform(D3DTS_WORLD, m);
	}
	// 
	~KdDirect3D() {
		Release();
	}

private:
	D3DLIGHT9					m_Light = {};//<-�\���̂̒��g�O�N���A��



	LPDIRECT3D9EX				m_lpD3D = nullptr;				// D3D�I�u�W�F�N�g
	LPDIRECT3DDEVICE9			m_lpD3DDev = nullptr;			// D3D�f�o�C�X
	D3DPRESENT_PARAMETERS		m_d3dpp;						// �ڍאݒ�
	D3DCAPS9					m_Caps;							// �f�o�C�X�̏��

	LPDIRECT3DSURFACE9			m_OrgRenderTarget = nullptr;	// �f�t�H���g�̃o�b�N�o�b�t�@
	LPDIRECT3DSURFACE9			m_OrgDepthStencil = nullptr;	// �f�t�H���g�̐[�x(Z)�o�b�t�@



	//�X�v���C�g�֌W
	LPD3DXSPRITE	mpSprite = nullptr;	// �X�v���C�g
	LPD3DXFONT		mpFont = nullptr;		// �t�H���g




//-------------------------------
// �V���O���g���p
//-------------------------------
private:

	KdDirect3D(){
	}

public:
	static KdDirect3D &GetInstance(){
		static KdDirect3D Instance;
		return Instance;
	}
	struct a {
		int a;
	};

};

// �ȒP�ɃA�N�Z�X�ł���悤�ɂ��邽�߂̃}�N��
#define KD3D KdDirect3D::GetInstance()
#define D3DEV  KdDirect3D::GetInstance().GetDev()
#define FONT KdDirect3D::GetInstance().GetFont()
#define SPRITE KdDirect3D::GetInstance().GetSprite()